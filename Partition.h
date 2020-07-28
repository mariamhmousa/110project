#ifndef PARTITION_H
#define PARTITION_H

#include <mutex>
#include <thread>
#include "defines.h"
#include "includes.h"

template <class T, typename S>
class Partition
{
    private:
        S * data;
        T ** dataWrapper;
        FILE * output;
        uint64_t partition_size;
        uint64_t current;
        uint64_t increment;
        std::mutex mtx;
        bool resize ();
    public:
        Partition (FILE * f,uint64_t p_partition_size,uint64_t p_increment);
        void addItem(S * s);
        void sort();
        void dump();
        T * getLast();//added function
        ~Partition ();
};

#endif