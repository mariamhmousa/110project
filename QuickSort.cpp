#ifndef QUICKSORT_CPP_
#define QUICKSORT_CPP_

#include "QuickSort.h"

template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;
}
template <class T>
int64_t QuickSort<T>::partition( int64_t l, int64_t r) {
	//Do your implementation here

	int center = (l + r)/2;
	//sorting the three records to take a paartition
	if(teraSortItem[center] < teraSortItem[l])
		{//swapping the center and the left if the center is smaller
			T * temp = teraSortItem[center];
			teraSortItem[center] = teraSortItem[l];
			teraSortItem[l] = temp;
		}

	if(teraSortItem[r] < teraSortItem[l])
		{//swapping the left and the right if the right is smaller
			T * temp = teraSortItem[r];
			teraSortItem[r] = teraSortItem[l];
			teraSortItem[l] = temp;
		}

	if(teraSortItem[r] < teraSortItem[center])
		{//swapping the center and the right if the right is smaller
			T * temp = teraSortItem[r];
			teraSortItem[r] = teraSortItem[center];
			teraSortItem[center] = temp;
		}
		//putting the partition at the end of the array
		T * temp = teraSortItem[r];
			teraSortItem[r] = teraSortItem[center];
			teraSortItem[center] = temp;

		return center;//returning the index of the partition

}
template <class T>
void QuickSort<T>::quickSort( int64_t l, int64_t r)
{
	//Do your implementation here

	//if(l+30 <= r)//if the items are less than 30, we use insertion sort
	//{
		T * pivot = teraSortItem[partition(l, r)];

		for(;;)
		{
			while(teraSortItem[++l] < pivot);
			while(pivot < teraSortItem[--r]);
			if(l < r)
			{
				T * temp = teraSortItem[l];
				teraSortItem[l] = teraSortItem[r];
				teraSortItem[r] = temp;
			}
			else
				break;
		}
		
		quickSort(l, l-1);
		quickSort(r+1,r);
	//}
	//else
		//insertsort()//add the code
}
template <class T>
QuickSort<T>::~QuickSort()
{
    
}

#endif