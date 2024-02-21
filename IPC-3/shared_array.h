#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>
#include <unistd.h>

class shared_array{
private:
    int size;
    std::string name;
    int* data;
    int fd;
    std::string newArrayName;

public:
    shared_array(const std::string& name, int size);
    int& operator[](int i);
    ~shared_array();
};

#endif //SHARED_ARRAY_H

