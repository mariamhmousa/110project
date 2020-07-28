#ifndef COMMANDLINEARGUMENTS_H
#define COMMANDLINEARGUMENTS_H

#include "TeraSort.cpp"
#include "TeraSortItem.h"


class CommandLineArguments
{
    private:
        char input_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];
        char output_file_name [COMMAND_LINE_ARGUMENT_MAX_SIZE];
        uint16_t mappers;
        uint16_t reducers;
        uint64_t sample_size;
        char error_string[ERROR_STRING_MAX_SIZE];
    public:
        CommandLineArguments();
        bool parser(int argc,char ** argv);
        bool execute();
        char * getErrorString();
        ~CommandLineArguments();
};

#endif