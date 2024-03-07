#include <iostream>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

// function that checks for prime numbers
bool isPrime(int n){
    if(n <= 1){
        return false;
    }

    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0){
            return false;
        }
    }

    return true;
}

// function that calculates m-th prime number
int mthPrimeNum(int m){
    if(m <= 0){
        return 0;
    }

    int n = 2;
    int count = 0;

    while(count < m){
        if(isPrime(n)){
            ++count;

            if(count == m){
                return n;
            }
        }
        ++n;
    }
    return 0;
}

int main(){
    int pipefd1[2];
    int pipefd2[2];

    int result1 = pipe(pipefd1);

    if(result1 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int result2 = pipe(pipefd2);

    if(result2 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // to create child process
    pid_t pid = fork();

    if(pid < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // parent process
    if(pid > 0){
        int close1 = close(pipefd1[0]);

        if(close1 < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        int close2 = close(pipefd2[1]);

        if(close2 < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        std::string str;
        int num;

        while(true){
            std::cout << "Please enter the number: ";
            std::cin >> str;

            if(str == "exit"){
                break;
            }

            num = std::stoi(str);

            std::cout << "Sending " << num << " to the child process..." << std::endl;

            int writeResult = write(pipefd1[1], &num, sizeof(int));

            if(writeResult < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            std::cout << "Waiting for the response from the child process... " << std::endl;

            int temp;

            int readResult = read(pipefd2[0], &temp, sizeof(int));

            if(readResult < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            std::cout << "Reseived calculation result of prime (" << num  << ") " << " = " << temp << std::endl;
        }
    }

    // child process
    if(pid == 0){
        int close1 = close(pipefd1[1]);

        if(close1 < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        int close2 = close(pipefd2[0]);

        if(close2 < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        int num;

        while(true){
            int readResult = read(pipefd1[0], &num, sizeof(int));

            if(readResult < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            int primeNum = mthPrimeNum(num);

            if(primeNum == 0){
                std::cerr << "Invalid input" << std::endl;
            }

            int writeResult = write(pipefd2[1], &primeNum, sizeof(int));

            if(writeResult < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }
        }
    }

    return 0;
}