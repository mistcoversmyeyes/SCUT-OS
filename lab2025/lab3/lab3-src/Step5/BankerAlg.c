#include <stdio.h>
#include <stdbool.h>

#define PROCESS_NUM 5    // 进程数量
#define RESOURCE_TYPE 3  // 资源类型数量

// 全局变量
int available[RESOURCE_TYPE];                     // 可用资源向量
int max[PROCESS_NUM][RESOURCE_TYPE];              // 最大需求矩阵
int allocation[PROCESS_NUM][RESOURCE_TYPE];       // 已分配矩阵
int need[PROCESS_NUM][RESOURCE_TYPE];             // 需求矩阵
char resource_name[RESOURCE_TYPE] = {'A', 'B', 'C'};

// 函数声明
void init_system();
void display_status();
bool is_safe(int process_seq[]);
void print_safe_sequence();
bool request_resource(int pid, int request[]);
void release_resource(int pid, int release[]);

// 系统初始化
void init_system() {
    // 初始化可用资源
    available[0] = 10;  // 资源A总量为10
    available[1] = 5;   // 资源B总量为5
    available[2] = 7;   // 资源C总量为7
    
    // 初始化最大需求矩阵（示例值）
    max[0][0] = 7; max[0][1] = 5; max[0][2] = 3;
    max[1][0] = 3; max[1][1] = 2; max[1][2] = 2;
    max[2][0] = 9; max[2][1] = 0; max[2][2] = 2;
    max[3][0] = 2; max[3][1] = 2; max[3][2] = 2;
    max[4][0] = 4; max[4][1] = 3; max[4][2] = 3;
    
    // 初始化已分配矩阵为0
    for (int i = 0; i < PROCESS_NUM; i++) {
        for (int j = 0; j < RESOURCE_TYPE; j++) {
            allocation[i][j] = 0;
            // 计算需求矩阵
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// 打印当前系统状态
void display_status() {
    printf("\n=================== 当前系统状态 ===================\n");
    printf("进程  |    最大需求    |    已分配    |    需求    \n");
    printf("    |   A   B   C   |   A   B   C   |   A   B   C   \n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < PROCESS_NUM; i++) {
        printf("P%d  |", i + 1);
        
        // 打印最大需求
        for (int j = 0; j < RESOURCE_TYPE; j++) {
            printf("   %d", max[i][j]);
        }
        printf("   |");
        
        // 打印已分配
        for (int j = 0; j < RESOURCE_TYPE; j++) {
            printf("   %d", allocation[i][j]);
        }
        printf("   |");
        
        // 打印需求
        for (int j = 0; j < RESOURCE_TYPE; j++) {
            printf("   %d", need[i][j]);
        }
        printf("\n");
    }
    
    printf("\n可用资源: ");
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        printf("%c:%d  ", resource_name[i], available[i]);
    }
    printf("\n");
}

// 安全性检查
bool is_safe(int process_seq[]) {
    bool finish[PROCESS_NUM] = {false};
    int work[RESOURCE_TYPE];
    int count = 0;
    
    // 复制当前可用资源到工作向量
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        work[i] = available[i];
    }
    
    // 尝试找到一个安全序列
    while (count < PROCESS_NUM) {
        bool found = false;
        
        for (int i = 0; i < PROCESS_NUM; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                
                // 检查是否可以满足进程i的所有需求
                for (int j = 0; j < RESOURCE_TYPE; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // 如果可以分配，模拟分配并回收资源
                    for (int j = 0; j < RESOURCE_TYPE; j++) {
                        work[j] += allocation[i][j];
                    }
                    
                    finish[i] = true;
                    process_seq[count++] = i;
                    found = true;
                }
            }
        }
        
        if (!found) {
            return false; // 找不到可以满足的进程，系统不安全
        }
    }
    
    return true; // 找到了一个安全序列
}

// 打印安全序列
void print_safe_sequence() {
    int process_seq[PROCESS_NUM];
    
    if (is_safe(process_seq)) {
        printf("\n系统状态安全，安全序列为: ");
        for (int i = 0; i < PROCESS_NUM; i++) {
            printf("P%d", process_seq[i] + 1);
            if (i < PROCESS_NUM - 1) {
                printf(" → ");
            }
        }
        printf("\n");
    } else {
        printf("\n当前系统状态不安全，无安全序列\n");
    }
}

// 资源请求处理
bool request_resource(int pid, int request[]) {
    // 检查请求是否超过需求
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        if (request[i] > need[pid][i]) {
            printf("错误：P%d请求的资源超过了最大需求\n", pid + 1);
            return false;
        }
        
        if (request[i] > available[i]) {
            printf("错误：P%d请求的资源超过了可用资源\n", pid + 1);
            return false;
        }
    }
    
    // 尝试分配资源（先保存当前状态以便回滚）
    int temp_available[RESOURCE_TYPE];
    int temp_allocation[PROCESS_NUM][RESOURCE_TYPE];
    int temp_need[PROCESS_NUM][RESOURCE_TYPE];
    
    // 保存当前状态
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        temp_available[i] = available[i];
        available[i] -= request[i];
    }
    
    for (int i = 0; i < PROCESS_NUM; i++) {
        for (int j = 0; j < RESOURCE_TYPE; j++) {
            temp_allocation[i][j] = allocation[i][j];
            temp_need[i][j] = need[i][j];
        }
    }
    
    // 更新分配
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }
    
    // 检查安全性
    int process_seq[PROCESS_NUM];
    if (is_safe(process_seq)) {
        printf("资源分配成功！\n");
        return true;
    } else {
        // 不安全，恢复之前的状态
        printf("分配后系统将处于不安全状态，拒绝分配\n");
        
        for (int i = 0; i < RESOURCE_TYPE; i++) {
            available[i] = temp_available[i];
        }
        
        for (int i = 0; i < PROCESS_NUM; i++) {
            for (int j = 0; j < RESOURCE_TYPE; j++) {
                allocation[i][j] = temp_allocation[i][j];
                need[i][j] = temp_need[i][j];
            }
        }
        return false;
    }
}

// 资源释放
void release_resource(int pid, int release[]) {
    // 检查是否尝试释放过多资源
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        if (release[i] > allocation[pid][i]) {
            printf("错误：P%d尝试释放的资源数量超过了已分配的数量\n", pid + 1);
            return;
        }
    }
    
    // 更新资源
    for (int i = 0; i < RESOURCE_TYPE; i++) {
        available[i] += release[i];
        allocation[pid][i] -= release[i];
        need[pid][i] += release[i];
    }
    
    printf("资源释放成功！\n");
}

// 主函数
int main() {
    int choice, pid;
    int request[RESOURCE_TYPE], release[RESOURCE_TYPE];
    
    // 初始化系统
    init_system();
    
    while (1) {
        printf("\n========== 银行家算法资源分配模拟 ==========\n");
        printf("1. 显示系统当前状态\n");
        printf("2. 检查并打印安全序列\n");
        printf("3. 申请资源\n");
        printf("4. 释放资源\n");
        printf("0. 退出系统\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 0:
                printf("系统已退出\n");
                return 0;
                
            case 1:
                display_status();
                break;
                
            case 2:
                print_safe_sequence();
                break;
                
            case 3:
                printf("请输入进程号(1-5): ");
                scanf("%d", &pid);
                pid--; // 转换为0-4索引
                
                if (pid < 0 || pid >= PROCESS_NUM) {
                    printf("无效的进程号！\n");
                    break;
                }
                
                printf("请输入请求资源数量(资源A B C): ");
                for (int i = 0; i < RESOURCE_TYPE; i++) {
                    scanf("%d", &request[i]);
                }
                
                if (request_resource(pid, request)) {
                    display_status();
                    print_safe_sequence();
                }
                break;
                
            case 4:
                printf("请输入进程号(1-5): ");
                scanf("%d", &pid);
                pid--; // 转换为0-4索引
                
                if (pid < 0 || pid >= PROCESS_NUM) {
                    printf("无效的进程号！\n");
                    break;
                }
                
                printf("请输入释放资源数量(资源A B C): ");
                for (int i = 0; i < RESOURCE_TYPE; i++) {
                    scanf("%d", &release[i]);
                }
                
                release_resource(pid, release);
                display_status();
                break;
                
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
    
    return 0;
}