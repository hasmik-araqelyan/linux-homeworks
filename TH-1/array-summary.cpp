#include <iostream>
#include <pthread.h>
#include <chrono>
#include <string>
#include <string.h>
#include <algorithm>

// structure to hold the information for each therad
struct ThreadInfo{
    int* array;
    int start;
    int end;
};

// function to calculate the partial sum
void* PartialSum(void* arg){
    ThreadInfo* part = (ThreadInfo*)arg;
    int sum = 0;

    for(int i = part->start; i < part->end; ++i){
        sum += part->array[i];
    }

    return new int(sum);
}

// function to create an array with random values
int* ArrayWithRandomValue(int size){
    int* array = new int[size];

    for(int i = 0; i < size; ++i){
        array[i] = rand();
    }

    return array;
}

int main(int argc, char** argv){
    // check if command line arguments are provided correctly
    if(argc < 3){
        std::cerr << "Error." << std::endl;
        return -1;
    }

    int size = std::stoi(argv[1]);
    int threadsCount = std::stoi(argv[2]);

    // create an array with random values
    int* array = ArrayWithRandomValue(size);

    // calculate the sum sequentially without using threads
    auto startTime = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for(int i = 0 ; i < size; ++i){
        sum += array[i];
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    double timeWithoutThread = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();

    // calculate the sum using multiple threads
    startTime = std::chrono::high_resolution_clock::now();
    pthread_t* threads = new pthread_t[threadsCount];
    ThreadInfo** argsArray = new ThreadInfo*[threadsCount];

    // create threads
    for(int i = 0; i < threadsCount; ++i){
        argsArray[i] = new ThreadInfo;
        argsArray[i]->array = array;
        argsArray[i]->start = i * size / threadsCount;
        argsArray[i]->end = std::min(argsArray[i]->start + (size / threadsCount), size);

        int result = pthread_create(&threads[i], NULL, PartialSum, argsArray[i]);

        if(result != 0){
            std::cerr << strerror(result) << std::endl;
            exit(result);
        }
    }

    // wait for all threads
    for(int i = 0; i < threadsCount; ++i){
        void* returnValue;
        int result = pthread_join(threads[i], &returnValue);
        int* partialSumResult = (int*)returnValue;
        sum += *partialSumResult;
        delete partialSumResult;
        delete argsArray[i];
    }

    // calculate the time taken with threads
    endTime = std::chrono::high_resolution_clock::now();
    double timeWithThread = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();

    std::cout << "Time spent without threads: " << timeWithoutThread << " seconds." << std::endl;
    std::cout << "Time spent with " << threadsCount << " threads "<< timeWithThread << " seconds." << std::endl;

    // clean up dynamically allocated memory
    delete [] argsArray;
    delete [] array;

    return 0;
}