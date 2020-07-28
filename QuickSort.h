#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "TeraSortItem.h"
template <class T>
class QuickSort{
    private:
        T ** teraSortItem;
        int64_t partition( int64_t l, int64_t r);
    public:
        QuickSort(T ** p_teraSortItem);
        void quickSort( int64_t l, int64_t r);
        ~QuickSort();
};

#endif