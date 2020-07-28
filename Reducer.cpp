#ifndef REDUCER_CPP_
#define REDUCER_CPP_

#include "Reducer.h"

template <class T, typename S>
Reducer<T,S>::Reducer (Partition<T,S> * p_partition)
{
    partition = p_partition;
}
template <class T, typename S>
void  Reducer<T,S>::execute ()
{
    printf ("Launching Reducer Sort Engine...\n");
    partition->sort();
    printf ("Reducer Sort Engine Terminated...\n");
}
template <class T, typename S>
void Reducer<T,S>::start (Reducer<T,S> * me)
{
    me->execute();
}

template <class T, typename S>
void Reducer<T,S>::setThread(std::thread * p_th)
{
    th = p_th;
}

template <class T, typename S>
void Reducer<T,S>::waitForRunToFinish()
{
    th->join();
}
template <class T, typename S>
Reducer<T,S>::~Reducer ()
{
    delete(th);
}

#endif