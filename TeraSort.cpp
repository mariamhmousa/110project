#ifndef TERASORT_CPP
#define TERASORT_CPP

#include "TeraSort.h"

template <class T, typename S>
TeraSort<T,S>::TeraSort (char * p_input_file_name,char * p_output_file_name,
                            uint16_t p_mappers, uint16_t p_reducers,uint64_t p_sample_size)
{
    input = fopen (p_input_file_name,"rb");//opening file for reading
    output = fopen (p_output_file_name,"wb");//opening file for writing
    file_byte_size = 0 ;
    file_record_size = 0 ;
    mappers = p_mappers;
    reducers = p_reducers;
    sample_size = p_sample_size;
    map_engines = NULL;
    reduce_engines = NULL;
    //partitioner = NULL;
    if ( input != NULL && output != NULL)//if files opened successfully
    {
        //Do your implementation here
        //getting the file size in bytes
        fseek(input, 0, SEEK_END);
        file_byte_size = ftell(input);
        //getting number of records each mapper has
        file_record_size = (file_byte_size/100)/mappers;
        //partitioner
        Partitioner<T,S> * partitioner = new Partitioner<T,S>(input, reducers, file_record_size);
    	//map_engines array
        for(uint16_t i = 0; i<mappers; i++)
        {
            uint64_t start_from = (file_byte_size/mappers)*(i*100);//the position where the mapper should start reading
            map_engines[i] = new Mapper<T,S>(input, start_from, file_record_size,sample_size, partitioner);//creating the mappers of the array
        }
    }
}

template <class T, typename S>
void TeraSort<T,S>::execute()
{
    printf ("Terasort Start Execute\n");
    for ( uint16_t i = 0 ; i  < mappers; i++)
    {	//creating threads for the mappers
        std::thread * th = new std::thread(Mapper<T,S>::start, map_engines[i]);
        map_engines[i]->setThread(th);
    }

	//Do your implementation here
    
    for(uint16_t i = 0; i<mappers; i++)
    {
        map_engines[i]->waitForRunToFinish();//joining the threads
    }
    uint16_t SR = sample_size/reducers;


    for(uint16_t j = 1; j<reducers; j++)
        {
            for(uint16_t i = 0; i<mappers; i++)
            {
                T * cutpoint = map_engines[i]->getSample(SR*j);//choosing the cutpoints from the samples
                partitioner->addCutpoint(j, cutpoint);//adding the cutpoint together
            }
            partitioner->calcCutpointsAverage(mappers);
        }

    //creating reducer bins (engines) and loading data into it
    
    for(uint16_t i = 0; i<reducers; i++)
    	{
    		reduce_engines[i] = new Reducer<T,S>(partitioner->getPartition(i));//creating the reducer bins
    	}

    //sorting data in every reducer
    for ( uint16_t i = 0 ; i  < reducers; i++)
    {	//creating threads for the reducers
        std::thread * th = new std::thread(Reducer<T,S>::start, reduce_engines[i]);
        reduce_engines[i]->setThread(th);
    }

    //joining the threads

    for(uint16_t i = 0; i<reducers; i++)
    {
        reduce_engines[i]->waitForRunToFinish();//joining the threads
    }

    //concatenating partitions in order

    for(uint16_t i = 0; i<reducers; i++)
    {
    	if (partitioner->getPartition(i)->getLast() > partitioner->getPartition(i+1)->getLast())
    		{
    			Partition<T,S> * temp = partitioner->getPartition(i);
                Partition<T,S> * part1 = partitioner->getPartition(i);
                Partition<T,S> * part2 = partitioner->getPartition(i+1);                
    			part1 = partitioner->getPartition(i+1);
    			part2 = temp;
    		}
    }


    for ( uint16_t i = 0 ; i  < reducers; i++)
        partitioner->getPartition(i)->dump();//writes sorted records to the output file

}

template <class T, typename S>
TeraSort<T,S>::~TeraSort()
{
    if ( input != NULL) fclose (input);
    if ( output != NULL) fclose (output);
    if ( map_engines != NULL)
    {
        for ( uint16_t i = 0 ; i  < mappers; i++)
            delete (map_engines[i]);
        free(map_engines);
    }
    if ( partitioner != NULL ) delete(partitioner);
}

#endif
