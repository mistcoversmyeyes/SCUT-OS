#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>  // 添加 fcntl.h 头文件用于文件操作

#define LOCKFILE "lock.txt"
#define SLEEP_TIME 1

int main(void) {
    // 创建锁文件
    int fd = open(LOCKFILE, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open lock file failed");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // 子进程1的代码
        while(1) {
            lockf(fd, F_LOCK, 0);  // 加锁
            printf("son .........\n");
            sleep(SLEEP_TIME);     // 让输出更容易观察
            lockf(fd, F_ULOCK, 0); // 解锁
            sleep(SLEEP_TIME);     // 给其他进程机会
        }
    }
    else if (pid1 > 0) {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            // 子进程2的代码
            while(1) {
                lockf(fd, F_LOCK, 0);  // 加锁
                printf("daughter ........\n");
                sleep(SLEEP_TIME);     // 让输出更容易观察
                lockf(fd, F_ULOCK, 0); // 解锁
                sleep(SLEEP_TIME);     // 给其他进程机会
            }
        }
        else if (pid2 > 0) {
            // 父进程的代码
            while(1) {
                lockf(fd, F_LOCK, 0);  // 加锁
                printf("Parent ......\n");
                sleep(SLEEP_TIME);     // 让输出更容易观察
                lockf(fd, F_ULOCK, 0); // 解锁
                sleep(SLEEP_TIME);     // 给其他进程机会
            }
        }
        else {
            printf("Fork Fail!");
            exit(1);
        }
    }
    
    return 0;
}