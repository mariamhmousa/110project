#include "CommandLineArguments.h"


CommandLineArguments::CommandLineArguments()
{
    memset(input_file_name,0,COMMAND_LINE_ARGUMENT_MAX_SIZE);
    memset(output_file_name,0,COMMAND_LINE_ARGUMENT_MAX_SIZE);
    memset(error_string,0,ERROR_STRING_MAX_SIZE);
    mappers = 0;
    reducers = 0;
    sample_size = 0;    
}
bool CommandLineArguments::parser(int argc,char ** argv)
{
    if ( argc %2 == 0 || argc < 2) return false;//validating number of inputs (arguments)
    else
    {
        for ( uint8_t i = 1 ; i < argc ; i +=2)//unit8_t??
        {//parsing inputs and assigning them to mappers, reducers, sample size, input_file_name, output_file_name 
            if ( strcmp(argv[i],"--input-file") == 0)
                strncpy(input_file_name,argv[i+1],COMMAND_LINE_ARGUMENT_MAX_SIZE-1);
            else if ( strcmp(argv[i],"--output-file") == 0)
                strncpy(output_file_name,argv[i+1],COMMAND_LINE_ARGUMENT_MAX_SIZE-1);
            else if ( strcmp(argv[i],"--mappers") == 0)
            {
                mappers =atoi(argv[i+1]);
            }
            else if ( strcmp(argv[i],"--reducers") == 0)
            {
                reducers =atoi(argv[i+1]);
            }
            else if ( strcmp(argv[i],"--sample-size") == 0)
            {
                sample_size =atoi(argv[i+1]);
            }
            else//if not any of the above then return false
            {
                sprintf(error_string,"undefined parameter: %s\n",argv[i]);
                return false;
            }
        }
        if ( strcmp (input_file_name,"") == 0 || strcmp (output_file_name,"") == 0 || 
                mappers == 0 || reducers == 0 || sample_size == 0 ) return false;//if any of the inputs is empty or 0 return false
        else return true;
    }
}
bool CommandLineArguments::execute()
{
    TeraSort <TeraSortItem,teraitem_r> * teraSort = 
            new TeraSort <TeraSortItem,teraitem_r> (input_file_name,output_file_name,mappers,reducers,sample_size);
    teraSort->execute();
    delete(teraSort);//destructor invoked
    return true;
}
char * CommandLineArguments::getErrorString()
{
    return error_string;
}
CommandLineArguments::~CommandLineArguments()
{
    
}
