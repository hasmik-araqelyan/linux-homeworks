#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define bufferSize 10

int main(int argc, char** argv){
    // File path check
    if(argc < 2){
        std::cerr << "Error: Please provide a file path" << std::endl;
        exit(1);
    }

    char* sourceFile = argv[1];

    // Open file
    int fd = open(sourceFile, O_RDONLY);

    // Checking to open the file correctly
    if(fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char buffer[bufferSize + 1];
    while(true){
        // Read the file content
        size_t readBytes = read(fd, buffer, bufferSize);

        if(readBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        if(readBytes == 0){
            break;
        }

        // Print the file content
        buffer[readBytes] = '\0';
        std::cout << buffer;
    }

    // Close the file
    int closeFile = close(fd);

    // Checking to close file correctly
    if(closeFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    return 0;

}