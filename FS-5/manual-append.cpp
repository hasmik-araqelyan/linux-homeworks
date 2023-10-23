#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <cstring>


int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Error:" << std::endl;
        exit(1);
    }

    char* file = argv[1];

    int openFile = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(openFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int resultFile = dup(openFile);

    if(resultFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char line1[] = "first line";
    char line2 []= "second line";

    ssize_t writeBytes = write(openFile, line1, strlen(line1));

    if(writeBytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    writeBytes = write(openFile, "\n", 1);

    if(writeBytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    writeBytes = write(openFile, line2, strlen(line2));

    if(writeBytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int closeFile1 = close(openFile);

    if(closeFile1 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int closeFile2 = close(resultFile);

    if(resultFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    return 0;
}