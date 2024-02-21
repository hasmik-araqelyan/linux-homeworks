#include "shared_array.h"

shared_array :: shared_array(const std::string& name, int size) : name(name), size(size){
    std::string sizeStr = std::to_string(size);
    newArrayName = name + "_" + sizeStr;
    fd = shm_open(newArrayName.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if(fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int newSize = ftruncate(fd, size * sizeof(int));
    data = (int*)mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        
}

int& shared_array :: operator[](int i){
    return data[i];
}

shared_array :: ~shared_array(){
    int unmap = munmap(data, size * sizeof(int));
    int unlink = shm_unlink(newArrayName.c_str());
    int closeFile = close(fd);

    if(closeFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
}
