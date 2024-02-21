#include <semaphore.h>
#include "shared_array.h"

int main(){
    std::string name = "array-name";
    int size = 10;

    shared_array arr(name, size);

    std::string sizeStr = std::to_string(size);
    std::string newArrayName = name + "_" + sizeStr;

    sem_t* semaphore = sem_open(newArrayName.c_str(), O_CREAT, S_IRUSR | S_IWUSR, 1);

    while(true){
        int wait = sem_wait(semaphore);

        for(int i = 0; i < size; ++i){
            arr[i] = i;
        }

        int post = sem_post(semaphore);
        sleep(1);
    }

    return 0;
}
