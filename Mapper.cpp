#ifndef MAPPER_CPP
#define MAPPER_CPP

#include "Mapper.h"
#include "QuickSort.cpp"


template <class T, typename S>
void Mapper<T,S>::phase1()
{
    dataWrapper = (T **) calloc (read_count,sizeof(T *));//allocating memory for the datawrapper array (records)
    sample = (T **) calloc (sample_size,sizeof(T *));//allocating memory for the samples
    for ( uint64_t i = 0  ; i < read_count ; i ++)
        dataWrapper[i] = new T (&data[i]);//creating datawrapper objects (records)
    //Do your implementation here

//-choosing samples
        //generate random index. if it is not already chosen, choose it.
    for(int i = 0; i<sample_size; i++)
        {
            T * ran = dataWrapper[rand()%read_count];//taking random samples through generating random indexes
            if(ran->getTeraItem()->b1[0] == 0 && ran->getTeraItem()->b1[1] == 0)//if the barrier of the sample is empty, this means that it was not chosen before so we take it
            {
                sample[i] = ran;
                sample[i]->getTeraItem()->b1[0] = 1;//marking the sample through setting its b1 to a value
                sample[i]->getTeraItem()->b1[1] = 2;
            }
        }
    for(int i = 0; i<sample_size; i++)
    {
        sample[i]->getTeraItem()->b1[0] = 0;//resetting the barriers to their original NULL values
        sample[i]->getTeraItem()->b1[1] = 0;
    }
//-sorting the samples
    QuickSort<T> * qs = new QuickSort<T>(sample);
    qs->quickSort(0,sample_size-1);//sorting the samples using Quicksort
}
template <class T, typename S>
void Mapper<T,S>::phase2()
{
    printf ("Start Shuffling .....\n");//indicates the start of phase 2
    for ( uint64_t i = 0 ; i  < read_count ; i ++)//loop to add each item to its partition
        partitioner->addItem(dataWrapper[i]);    
    printf ("Finished Shuffling .....\n");
}



template <class T, typename S>
Mapper<T,S>::Mapper (FILE * f, 
                uint64_t p_start,
                uint64_t p_count,
                uint64_t p_sample_size,
                Partitioner<T,S> * p_partitioner)
{
    input = f;
    read_count = p_count;
    read_start = p_start;//because each mapper starts reading from a specific location
    sample_size = p_sample_size;
    dataWrapper = NULL;//array that has records in it
    data = (S *) calloc (read_count,sizeof(S));
    fseek(input,read_start*sizeof(S),SEEK_SET);
    uint64_t read_items = fread(data,sizeof(S),read_count,f);//reading the records into the data array and storing the number of records read in the variable read_items
    partitioner = p_partitioner;
    phase = PHASE1;
}


template <class T, typename S>
void Mapper<T,S>::execute ()
{
    if ( phase == PHASE1) 
    {
        phase1();
        phase = PHASE2;
    }
    else if(phase == PHASE2) phase2();
}

template <class T, typename S>
void Mapper<T,S>::start (Mapper<T,S> * me)
{
    me->execute();
}

template <class T, typename S>
void Mapper<T,S>::setThread(std::thread * p_th)
{
    th = p_th;
}

template <class T, typename S>
void Mapper<T,S>::waitForRunToFinish()
{
    th->join();
}

template <class T, typename S>
T * Mapper<T,S>::getSample(uint16_t index)
{
	return sample[index];
}
template <class T, typename S>
Mapper<T,S>::~Mapper()
{
    if (dataWrapper != NULL)
    {
        for ( uint64_t i = 0  ; i < read_count ; i ++) delete (dataWrapper[i]);
        free(dataWrapper);
    }
    free(data);
    delete(th);
}

#endif