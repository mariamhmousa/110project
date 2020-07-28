#ifndef TERASORT_H
#define TERASORT_H

#include "defines.h"
#include "includes.h"
#include "Mapper.cpp"
#include "Reducer.cpp"
#include "Partitioner.cpp"


template <class T, typename S>
class TeraSort
{
    private:
        FILE * input;
        FILE * output;
        uint64_t file_byte_size;
        uint64_t file_record_size;
        char input_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];
        char output_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];
        uint16_t mappers;
        uint16_t reducers;
        uint64_t sample_size;
        Mapper <T,S> ** map_engines;
        Reducer <T,S> ** reduce_engines;
        Partitioner <T,S> * partitioner;
    public:
        TeraSort (char * p_input_file_name,char * p_output_file_name,uint16_t p_mappers, uint16_t p_reducers,uint64_t p_sample_size);
        void execute();
        ~TeraSort();
};
#endif