#include <iostream>
#include <string.h>
#include <signal.h>
#include <sys/ucontext.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

void sigusr1(int sig, siginfo_t* info, void* ptr){
    ucontext_t* context = (ucontext_t*)ptr;

    pid_t pid = info->si_pid;

    uid_t uid = info->si_uid;

    struct passwd *result = getpwuid(uid);
    char* username = result->pw_name;

    unsigned long eip = context->uc_mcontext.gregs[REG_RIP];
    unsigned long eax = context->uc_mcontext.gregs[REG_RAX];
    unsigned long ebx = context->uc_mcontext.gregs[REG_RBX];

    std::cout << "Received a SIGUSR1 signal from process " << info->si_pid << " executed by " << uid << std::endl;
    std::cout << "State of the context: EIP = " << eip << ", EAX = " << eax << ", EBX = " << ebx << "." << std::endl;
}

int main(){
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = sigusr1;
    action.sa_flags = SA_SIGINFO;
    int result = sigaction(SIGUSR1, &action, NULL);

    if(result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    pid_t pid = getpid();
    std::cout << "The PID is " << pid << std::endl;

    while(true){
        sleep(5);
    }

    return 0;
}