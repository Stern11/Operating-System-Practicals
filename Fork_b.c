
// Aryan Pratap Singh Arya
// 21513

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(){

    pid_t pid ;
    pid=fork();


    if(pid<0){
        printf("Child process was not created!!!\n");
    }

    else if(pid==0){
        printf("Inside child Process with pid=%d",getpid);
        //terminate the current process and execute the mentioned process
        execlp("./copyFiles.exe","copyFiles.exe",NULL);
        printf("This line wouldn't be executed")
    }

    else{
        printf("Inside Parent process\n");
        // parent process will wait till child process execute
        Wait(NULL);
        printf("parent process terminated!!!");

    }
    return 0;
}