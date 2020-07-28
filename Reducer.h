#ifndef REDUCER_H
#define REDUCER_H

#include "defines.h"
#include "includes.h"
#include "Partitioner.cpp"

template <class T,typename S>
class Reducer
{
    private:
        Partition<T,S> * partition;
        std::thread * th;
    public:
        Reducer (Partition<T,S> * p_partition);
        void execute ();
        static void start(Reducer<T,S> * me);//why static?
        void setThread(std::thread * p_th);
        void waitForRunToFinish();
        ~Reducer ();

};
#endif