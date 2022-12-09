
// Aryan Pratap Singh Arya
// Copy Content of a file to other file.

#include <stdio.h>
#include <dir.h>
#include <dos.h>
#include <stdlib.h>

int main(){

// Generating a file pointer which would keep track of the file during 
// the process.
    FILE *file1, *file2;
    char ch;

    char inputFile[20];
    char outputFile[20];

// Input Name of Source file and Destination File names
    printf("Enter file from which you wanna copy content from : ");
    scanf("%s", inputFile);
    printf("Enter file to which you wanna copy content to : ");
    scanf("%s", outputFile);

// Bringing files into main memory and getting read and write access.
   file1= fopen(inputFile , "r");
   file2= fopen(outputFile , "w");

//Generating an interrupt in case input file doesn't exist and thus 
//terminating the process with exit code '-1' 
    if(file1==NULL){
         printf("Input File doesn't exist");
         exit(-1);
    }

//ch would read character by character from file while the End of File
// is reached.
// putc would print the readed characters into destination file.  
    else{
        while((ch=getc(file1))!=EOF){
            putc(ch,file2);
        }
// Generate a final interrupt to close the file.
        fclose(file1);
        fclose(file2);
    }

    return 0;
}