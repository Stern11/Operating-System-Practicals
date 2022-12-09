
// Aryan Pratap Singh Arya
// 21513

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

// Create a child process identical to parent process
   fork();
// These line of code would be printed twice
    printf("this is Aryan Pratap!!\n");
    printf("This line of code would be printed twice : Once with child process another by parent process\n");

    return 0;
}