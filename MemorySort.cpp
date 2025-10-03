#include "MemorySort.h"


int range(int* array, int length, int* min, int* max) {
	*min = array[0], *max = array[0];
	for (int i = 1; i < length; i++) {
		int val = array[i];
		if (val < *min) {
			*min = val;
		}
		else if (val > *max) {
			*max = val;
		}
	}
	return *max - *min;
}

void swap(int* array, int A, int B) {
	int temp = array[A];
	array[A] = array[B];
	array[B] = temp;
}

void sorter::MemorySort::sort(int* array, int length)
{
	int min, max;
	int size = range(array, length, &min, &max);
	int* memoryMap = new int[size];
	for (int i = 0; i < size; i++) {
		memoryMap[i] = -1;
	}
	for (int i = 0; i < length; i++) {
		memoryMap[array[i] - min] = i;
	}
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (memoryMap[i] != -1) {
			swap(array, index, memoryMap[i]);
			index++;
		}
	}
}
