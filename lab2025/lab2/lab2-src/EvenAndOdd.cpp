#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (){
    pid_t pid1 = fork();
    if (pid1 == 0){
        printf ("1,3,5,7,9\n");
    }
    else {
        printf("2,4,6,8,10\n");
    }
}