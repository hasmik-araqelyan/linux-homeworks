#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


void initialize(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Error: Provide the file path" << std::endl;
        exit(1);
    }

        char* openFile = argv[1];

        int openFd = open(openFile, O_RDWR);

        if(openFd < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        ssize_t insteadOfCin = dup2(openFd,0);

        ssize_t closeFile = close(openFd);

        if(closeFile < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
}

int main(int argc, char** argv){
    //
    
    initialize(argc, argv);

    //

    std::string input;
    std::cin >> input;
    //ssize_t size = input.size();

    //
    std::string reversed;

    for(int i = input.length(); i >= 0; --i){
        reversed = reversed + input[i];
    }

    std::cout << reversed << std::endl;

    return 0;
}