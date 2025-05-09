#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

static pid_t child1_pid ,child2_pid;

void parent_handler(int sigNum){
    printf("父进程接收到中断信号SIGINT\n");
    printf("父进程向子进程1发送信号SIGUSR1/2\n");
    kill(child1_pid,SIGUSR1);
    printf("父进程向子进程2发送信号SIGUSR1/2\n");
    kill(child2_pid,SIGUSR2);

    wait(NULL); //等待其中一个子进程发送死亡信号消耗掉这个
    wait(NULL); //等待另外一个子进程死亡后发送信号消耗掉这个

    printf("两个子进程均被kill，父进程退出\n");
    printf("Parent process is killed!\n");
    exit(0);
}

void child1_handler (int sigNum){
    printf("Child process1 is killed by parent!\n");
    exit(0);
}


void child2_handler(int sigNum){
    printf("Child process2 is killed by parent!\n");
    exit(0);
}

int main(){
    // 设置父进程中断处理
    if (signal(SIGINT,parent_handler) == SIG_ERR){
        perror("父进程中断处理函数设置失败\n");
        exit(1);
    }



    // 父进程创建两个子进程
    child1_pid = fork();
    if (child1_pid < 0){
        // 进程创建失败
        perror("子进程1创建失败\n");
        exit(1);
    }
    else if (child1_pid ==0){
        // 当前在子进程1中
        if (signal(SIGUSR1,child1_handler) == SIG_ERR){
            printf("设置子进程1对SIGUSR2的处理函数失败，子进程1退出\n");
        }
         while (1){
            printf("子进程2正在运行\n");
            sleep(1);
        }
    }
    else {
        // 当前在父进程中
        child2_pid = fork();
        if (child2_pid < 0 ){
            perror("子进程2创建失败\n");
            exit(1);
        }
        else if (child2_pid == 0){
            // 当前在子进程2中
            
            // 设置子进程2 对于信号 SIGUSR2的处理函数
            if (signal(SIGUSR2,child2_handler) == SIG_ERR){
                printf("设置子进程2对SIGUSR2的处理函数失败，子进程2退出\n");
                exit(1);
            }

            while (1){
                printf("子进程1正在运行\n");
                sleep(1);
            }
        }
        else {
            // 当前在父进程中
            while(1){
                sleep(1);
            }
        }
    }
}