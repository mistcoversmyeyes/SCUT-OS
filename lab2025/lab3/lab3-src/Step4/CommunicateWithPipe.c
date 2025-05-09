#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main (){
    int fd[2];
    pipe(fd);

    // 父进程创建子进程
    __pid_t pid1 = fork();
    if (pid1 == 0){
        // 子进程1
        dup2(fd[1], STDOUT_FILENO);
        printf("Child 1 is sending a message!\n");
        return 0;
    } else {
        __pid_t pid2 = fork();
        if (pid2 == 0){
            // 子进程2
            dup2(fd[1], STDOUT_FILENO);
            printf("Child 2 is sending a message!\n");
            return 0;
        }
        else{
            // 父进程
            close(fd[1]); // 关闭写端
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            while (1) {
                char buf[128];
                if (fgets(buf, sizeof(buf), stdin) != NULL) {
                    printf("Parent received: %s", buf);
                } else {
                    break;
                }
            }
        }
    }
}