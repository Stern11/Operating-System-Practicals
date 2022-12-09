

// AryanPratap
// Copy Content of a file to another 

#include <iostream>
#include <fstream>
using namespace std;

int main(){

    // string temp ="";
    char A;
    ifstream inputFile;
    inputFile.open("File1.txt"); 
    ofstream writeFile;
    writeFile.open("File2.txt");
    

    while(inputFile.eof()==NULL){
        inputFile>>A;
        writeFile<<A;
    }

    inputFile.close();
    writeFile.close();
    return 0;
}