#ifndef PARTITION_CPP_
#define PARTITION_CPP_

#include "Partition.h"
#include "QuickSort.cpp"

template <class T, typename S>
bool Partition<T,S>::resize ()
{
    if ( current == partition_size)
    {
        partition_size += increment;//increases the partition size
        data = (S *) realloc (data,partition_size*sizeof(S));//increasing the memory allocated for this partition's data
        dataWrapper = (T **) realloc (dataWrapper,partition_size*sizeof(T *));//increasing the memory allocated for this partition's data
        memset (((char*) data)+(current*sizeof(S)),0,increment*sizeof(S));//setting the incremented bytes to 0 (NULL)
        memset (((char*) dataWrapper)+(current*sizeof(T*)),0,increment*sizeof(T*));//setting the incremented bytes to 0 (NULL)
        return true;
    }
    return false;
}
template <class T, typename S>
Partition<T,S>::Partition (FILE * f,uint64_t p_partition_size,uint64_t p_increment)//constructor
{
    partition_size = p_partition_size;
    increment = p_increment;
    current = 0;
    output = f;
    data = (S *) calloc (partition_size,sizeof(S));
    dataWrapper = (T **) calloc (partition_size,sizeof(T *));
}
template <class T, typename S>
void Partition<T,S>::addItem(S * s)
{
	//Do your implementation here
    
    mtx.lock();

    bool resizing = resize();//resizing the partition before adding the new data

    //adding the new data element to the array

    data[partition_size-1].key = s->key;
    data[partition_size-1].b1 = s->b1;
    data[partition_size-1].rowid = s->rowid;
    data[partition_size-1].b2 = s->b2;
    data[partition_size-1].filler = s->filler;
    data[partition_size-1].b3 = s->b3;

    mtx.unlock();
  
}
template <class T, typename S>
void Partition<T,S>::sort()
{
    for ( uint64_t i = 0  ; i < partition_size ; i ++)
        dataWrapper[i] = new T (&data[i]);
    QuickSort <T> quickSort (dataWrapper);
    quickSort.quickSort(0,current-1);
}
template <class T, typename S>
void Partition<T,S>::dump()
{
    fwrite(data,sizeof(S),current,output);
}

//added function...gets the last element (record) in the partition
template <class T, typename S>
T * Partition<T,S>::getLast()
{
    return dataWrapper[partition_size-1];
}

template <class T, typename S>
Partition<T,S>::~Partition ()//destructor
{
    if ( data != NULL ) free(data);
    for ( uint64_t i = 0  ; i < partition_size ; i ++) delete (dataWrapper[i]);
    free(dataWrapper);
}
#endif