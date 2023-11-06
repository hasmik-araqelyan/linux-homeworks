#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define bufferSize 10

int main(int argc, char** argv){
    // file path check
    if(argc < 3){
        std::cerr << "Error: Provide the file path" << std::endl;
        exit(1);
    }

    char* sourceFile = argv[1];
    char* destinationFile = argv[2];

    // open source file
    int sourceFd = open(sourceFile, O_RDWR);

    // checking to open the source file correctly
    if(sourceFd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // open destination file
    int destinationFd = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // checking to open the destination file correctly
    if(destinationFd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    char buffer[bufferSize];

    while(true){
        // read the source file
        ssize_t readBytes = read(sourceFd, buffer, bufferSize);

        if(readBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        if(readBytes == 0){
            break;
        }

        // copy the file content
        ssize_t writeBytes = write(destinationFd, buffer, readBytes);

        if(writeBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    int dataBytes = 0;
    int holeBytes = 0;
    int countData = 0;
    int countHole = 0;

    // find the first possition
    off_t position = lseek(sourceFd, 0, SEEK_SET);

    if(position < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // find the size of file
    off_t end = lseek(sourceFd, 0, SEEK_END);

    if(end < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    while(end > position){
        // go to the start of the closest hole
        countData = lseek(sourceFd, position, SEEK_HOLE);

        if(countData < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        dataBytes = dataBytes + countData - position;

        // go to the start of the closest data
        countHole = lseek(sourceFd, position, SEEK_DATA);

        if(countHole < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        holeBytes = holeBytes + countHole - position;

        // update position
        position = lseek(sourceFd, bufferSize, SEEK_CUR);

        if(position < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    // count the total number of bytes
    int total = dataBytes + holeBytes;

   // close the source file
   int closeSourceFile = close(sourceFd);

   // checking to close the source file correctly
   if(closeSourceFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
   } 

   // close the destination file
   int closeDestinationFile = close(destinationFd);

   //checking to close the destination file correctly
   if(closeDestinationFile < 0){
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
   }

   std::cout << "Succesfully copied " << total << " bytes (data: " << dataBytes << ", hole: " << holeBytes << ")." << std::endl;

    return 0;
}