# include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main (void){
    pid_t pid1 = fork();     // 如果是父进程就返回子进程的pid，如果是子进程就返回0.
    if (pid1 == 0){
        // 现在这一块是子进程1的代码
        while(true){
            printf("son .........\n");
        }
    }
    else if (pid1 > 0){
        // 这一块是父进程的代码
        pid_t pid2 = fork();
        if (pid2 == 0){
            // 这一块是子进程2的代码。
            while (true){
                printf("daughter ........\n");
            }
        }
        else if (pid2 > 0){
            // 这里是父进程的代码。
            while (true){
                printf("Parent ......\n");
            }
        }
        else {
            // 这里也是父进程的代码，但是子进程创建失败了。
            printf("Fork Fail!");
        }
        
    }
}