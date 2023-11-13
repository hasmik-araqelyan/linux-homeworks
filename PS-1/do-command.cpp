#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


void do_command(char** argv){
    int status;

    // start time
    clock_t startTime = clock();

    // to create a new child process
    pid_t pid = fork();

    if(pid < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    if(pid == 0){
        // child process
        execvp(argv[0], argv);
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    if(pid > 0){
        // parent process
        waitpid(pid, &status, 0);

        // end time
        clock_t endTime = clock();

        // to count the time
        double time = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    }

    std::cout << "Command complected with " << WIFEXITED(status) << " exit code and took "<< time << " seconds." << std::endl;
    
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Error." << std::endl;
        exit(1);
    }

    do_command(argv + 1);

    return 0;
}