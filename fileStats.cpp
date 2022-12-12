#include <iostream>
#include <unistd.h> //for open()
#include <sys/types.h>
#include <sys/stat.h> //for stat struct
#include <fcntl.h>    // for O_RDONLY
using namespace std;
int main(int argc, char **argv)
{
    if (argc != 2) // check for valid number of arguments
    {
        cout << "Invalid arguments!" << endl;
        return 0;
    }
    struct stat buffer;               // creating stat
    int fd = open(argv[1], O_RDONLY); // storing the file descriptor
    if (fd == -1)
    {
        cout << "Error opening file!" << endl;
        close(fd);
        return 0;
    }
    if (fstat(fd, &buffer) == -1) // fstat() function links the file with file descriptor 'fd' and the buffer passes as the argument
    {                             // after successful call, buffer will contain the information of the file.
        cout << "Error in calling fstat()!" << endl;
        close(fd);
        return 0;
    }
    int permission = buffer.st_mode & 0700; 
 
    // the least significant 9 bits of st_mode field contain the permission bits of the file.
    // To retrieve owner access permission, an octal bit mask of 0700(111 000 000) is applied because out of the 9 permission bits
    //  3 most sigificant bits represent owner access permissions.
    if ((permission & 0400) == 0400) // if the owner has read permission, then the bit pattern will have 1 in the 9th position.
    {
        cout << "Owner has read permision." << endl;
    } // So, octal bit mask of 0400(100 000 000) will retrieve owner read permission
    else
    {
        cout << "Owner does not have read permission." << endl;
    }
    if ((permission & 0200) == 0200) // similarly, if the owner has write permisiion, then the bit pattern will have 1 in the 8th positi
    {
        cout << "Owner has write permission." << endl;
    } // 0200->010 000 000 (1 in the 8th position)
    else
    {
        cout << "Owner does not have write permission." << endl;
    }
    if ((permission & 0100) == 0100) // same explanation for execute permission
    {
        cout << "Owner has execute permission." << endl;
    } // 0100->001 000 000 (1 in the 7th position)
    else
    {
        cout << "Owner does not have execute permission." << endl;
    }
    cout << "Last file access time : " << buffer.st_atime << endl;
    // st_atime will give the time of last access with respect to 00:00 1st January 1970 in seconds
    close(fd);
    return 0;
}