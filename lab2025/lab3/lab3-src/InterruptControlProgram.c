#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 全局变量，用于跟踪中断次数
volatile int interrupt_count = 0;

// 信号处理函数
void handle_sigint(int sig) {
    interrupt_count++;
    
    if (interrupt_count < 3) {
        printf("\n切换到下一条消息...\n");
    } else {
        printf("\n程序结束！\n");
        exit(0);  // 第三次按下Ctrl+C后退出
    }
}

int main() {
    // 设置SIGINT信号处理函数
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("无法设置信号处理函数");
        return 1;
    }
    
    printf("程序启动: 按Ctrl+C切换消息, 第三次按Ctrl+C结束程序\n");
    
    while (1) {
        if (interrupt_count == 0) {
            printf("Hello！\n");
        } else if (interrupt_count == 1) {
            printf("How are you?\n");
        } else if (interrupt_count == 2) {
            printf("I am fine！\n");
        }
        
        sleep(1);  // 控制输出速度
    }
    
    return 0;
}