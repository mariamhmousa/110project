
#include "CommandLineArguments.h"

int main(int argc, char **argv)
{    
    time_t start = time(NULL);
    CommandLineArguments cmlarg;
    if (cmlarg.parser(argc,argv))//takes inputs and parse them
    {
        if (!cmlarg.execute())
        {
            if ( strcmp(cmlarg.getErrorString(),"") != 0 )//showing error message
                printf ("%s\n",cmlarg.getErrorString());
        }        
    }
    else
    {
        if ( strcmp(cmlarg.getErrorString(),"") != 0 )//showing error message
            printf ("%s",cmlarg.getErrorString());
        printf ("usage: %s --input-file <file-name> --output-file <file-name> --mappers <# of mappers> --reducers <# of reducers> --sample-size <# of records in sample>\n",argv[0]);//validating input and showing usage
        exit(1);
   }
    time_t end = time(NULL);
    printf ("Total time: %lu\n",end-start);//printing total time taken
    
 
    return 0;
}