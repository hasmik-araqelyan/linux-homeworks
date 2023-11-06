#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define bufferSize 10
int main(int argc, char** argv){
    // File path check
    if(argc < 2){
        std::cerr << "Error: Please provide the file path" << std::endl;
        exit(1);
    }

    char* openFile = argv[1];

    // Open file
    int openFd = open(openFile, O_RDWR);

    // Checking to open the file correctly
    if(openFd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buffer[bufferSize];

    int temp;

    while(temp < bufferSize){
        buffer[temp++] = '\0';
    }

    struct stat fileStat;
    ssize_t openFileInf = stat(openFile, &fileStat);
    ssize_t length = fileStat.st_size;
    int cur = 0;

    while(cur < length){
        ssize_t writeBytes = write(openFd, buffer, bufferSize);

        if(writeBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        cur = cur + writeBytes;
    }

    // Remove the file
    ssize_t del = unlink(openFile);
    if(del < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    return 0;
}