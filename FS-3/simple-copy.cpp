#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define bufferSize 10

int main(int argc, char** argv){
    // Check the file path
    if(argc < 3){
        std::cerr << "Error: Please provide the file path" << std::endl;
        exit(1);
    }

    char* sourceFile = argv[1];
    char* copyFile = argv[2];

    // Open file
    int sourceFd = open(sourceFile, O_RDONLY);

    // Check to open the file correctly
    if(sourceFd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Open new file
    int copyFd = open(copyFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    // Check to open the file correctly
    if(copyFd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buffer[bufferSize + 1];

    while(true){
        // Read the file content
        ssize_t readBytes = read(sourceFd, buffer, bufferSize);

        if(readBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        if(readBytes == 0){
            break;
        }

        // Copy the file content
        ssize_t writeBytes = write(copyFd, buffer, readBytes);

        if(writeBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    // Close source file
    int closeFd1 = close(sourceFd);

    // Check to close the file correctly
    if(closeFd1 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Close copy file
    int closeFd2 = close(copyFd);

    // Check to close the file correctly
    if(closeFd2 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    return 0;
}