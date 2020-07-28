#ifndef PARTITIONER_H
#define PARTITIONER_H

#include "defines.h"
#include "includes.h"
#include "Partition.cpp"

template <class T, typename S>
class Partitioner
{
    private:
        Partition <T,S> ** partitions;
        uint16_t partitions_count;
        T ** cutpoints;
    public:
        Partitioner (FILE * f,uint16_t p_partitions_count,uint64_t p_partition_expected_size);
        void addCutpoint(uint16_t index,T * t);
        void calcCutpointsAverage(uint16_t p_mappers_count);
        void addItem(T * t);
        uint16_t getPartitionsCount();
        Partition <T,S> * getPartition (uint16_t index);
        ~Partitioner ();
};

#endif