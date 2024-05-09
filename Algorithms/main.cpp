#include <iostream>
#include <random>

#include "../Array.h"

int CompareInt(int a, int b)
{
	return a - b;
}

int CompareFloat(float a, float b)
{
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

template<class DataType>
void Swap(DataType& a, DataType& b)
{
	DataType temp = a;
	a = b;
	b = temp;
}

template<class DataType>
void BubbleSort(Array<DataType>& array, int(*compare)(const DataType, const DataType))
{
	size_t top = array.Size();
	size_t swaps = 1;

	while (top != 0 && swaps != 0)
	{
		swaps = 0;
		for (size_t i = 0; i < top - 1; i++)
		{
			if (compare(array[i], array[i + 1]) > 0)
			{
				Swap(array[i], array[i + 1]);
				swaps++;
			}
		}

		top--;
	}
}

template<class DataType>
void HeapWalkDown(Array<DataType>& array, size_t index, size_t maxIndex, int(*compare)(DataType, DataType))
{
	size_t parent = index;
	size_t child = index * 2;
	DataType temp = array[parent - 1];

	while (child <= maxIndex)
	{
		if (child < maxIndex)
		{
			if (compare(array[child - 1], array[child]) < 0)
			{
				child++;
			}
		}

		if (compare(temp, array[child - 1]) < 0)
		{
			array[parent - 1] = array[child - 1];
			parent = child;
			child *= 2;
		}
		else break;

		array[parent - 1] = temp;
	}
}

template<class DataType>
void HeapSort(Array<DataType>& array, int(*compare)(DataType, DataType))
{
	size_t maxIndex = array.Size();
	size_t rightIndex = maxIndex / 2;

	for (size_t i = rightIndex; i > 0; i--)
	{
		HeapWalkDown(array, i, maxIndex, compare);
	}

	while (maxIndex > 0)
	{
		Swap(array[0], array[maxIndex - 1]);
		maxIndex--;
		HeapWalkDown(array, 1, maxIndex, compare);
	}
}

template<class DataType>
size_t FindMedianOfThree(Array<DataType>& array, size_t first, size_t size, int(*compare)(DataType, DataType))
{
	size_t last = first + size - 1;
	size_t mid = first + (size / 2);

	if(compare(array[first], array[mid]) < 0 && compare(array[first], array[last]) < 0)
	{
		if (compare(array[mid], array[last]) < 0) return mid;
		else return last;
	}

	if(compare(array[mid], array[first]) < 0 && compare(array[mid], array[last]) < 0)
	{
		if (compare(array[first], array[last]) < 0) return first;
		else return last;
	}

	if (compare(array[mid], array[first]) < 0) return mid;
	else return first;
}

template<class DataType>
void Quicksort(Array<DataType>& array, size_t first, size_t size, int(*compare)(DataType, DataType))
{
	DataType pivot;
	size_t last = first + size - 1;
	size_t mid;
	size_t lower = first;
	size_t higher = last;

	if (size > 1)
	{
		mid = FindMedianOfThree(array, first, size, compare);
		pivot = array[mid];
		array[mid] = array[first];

		while (lower < higher)
		{
			while (compare(pivot, array[higher]) < 0 && lower < higher)
			{
				higher--;
			}

			if (higher != lower)
			{
				array[lower] = array[higher];
				lower++;
			}

			while (compare(pivot, array[lower]) > 0 && lower < higher)
			{
				lower++;
			}

			if (higher != lower)
			{
				array[higher] = array[lower];
				higher--;
			}

			array[lower] = pivot;
			Quicksort(array, first, lower - first, compare);
			Quicksort(array, lower + 1, last - lower, compare);
		}
	}
}

template<class DataType>
void PrintArray(Array<DataType>& array)
{
	for (size_t i = 0; i < array.Size(); i++)
	{
		std::cout << array[i] << ' ';
	}
	std::cout << std::endl;
}

const size_t RADIX_BIN_SIZE = 1024;

void RadixSort2(Array<int>& array, size_t passes)
{
	if (array.Size() > RADIX_BIN_SIZE) return;

	static int bins[2][RADIX_BIN_SIZE];
	int binCount[2];
	size_t radix = 1;
	size_t shift = 0;
	size_t index;
	size_t binIndex;
	size_t currentBin;

	while (passes != 0)
	{
		passes--;

		binCount[0] = binCount[1] = 0;
		for (index = 0; index < array.Size(); index++)
		{
			binIndex = (array[index] & radix) >> shift;
			bins[binIndex][binCount[binIndex]] = array[index];
			binCount[binIndex]++;
		}

		index = 0;
		for (currentBin = 0; currentBin < 2; currentBin++)
		{
			binIndex = 0;
			while (binCount[currentBin] > 0)
			{
				array[index] = bins[currentBin][binIndex];
				binIndex++;
				binCount[currentBin]--;
				index++;
			}
		}

		radix <<= 1;
		shift += 1;
	}
}

void RadixSort4(Array<int>& array, size_t passes)
{
	if (array.Size() > RADIX_BIN_SIZE) return;

	static int bins[4][RADIX_BIN_SIZE];
	int binCount[4];
	int radix = 3;
	size_t shift = 0;
	size_t index;
	size_t binIndex;
	size_t currentBin;

	while (passes != 0)
	{
		passes--;

		binCount[0] = binCount[1] = 0;
		for (index = 0; index < array.Size(); index++)
		{
			binIndex = (array[index] & radix) >> shift;
			bins[binIndex][binCount[binIndex]] = array[index];
			binCount[binIndex]++;
		}

		index = 0;
		for (currentBin = 0; currentBin < 2; currentBin++)
		{
			binIndex = 0;
			while (binCount[currentBin] > 0)
			{
				array[index] = bins[currentBin][binIndex];
				binIndex++;
				binCount[currentBin]--;
				index++;
			}
		}

		radix <<= 2;
		shift += 2;
	}
}

void RadixSort16(Array<int>& array, size_t passes)
{
	if (array.Size() > RADIX_BIN_SIZE) return;

	static int bins[16][RADIX_BIN_SIZE];
	int binCount[16];
	int radix = 15;
	size_t shift = 0;
	size_t index;
	size_t binIndex;
	size_t currentBin;

	while (passes != 0)
	{
		passes--;

		binCount[0] = binCount[1] = 0;
		for (index = 0; index < array.Size(); index++)
		{
			binIndex = (array[index] & radix) >> shift;
			bins[binIndex][binCount[binIndex]] = array[index];
			binCount[binIndex]++;
		}

		index = 0;
		for (currentBin = 0; currentBin < 2; currentBin++)
		{
			binIndex = 0;
			while (binCount[currentBin] > 0)
			{
				array[index] = bins[currentBin][binIndex];
				binIndex++;
				binCount[currentBin]--;
				index++;
			}
		}

		radix <<= 4;
		shift += 4;
	}
}

int main()
{
	srand(time(NULL));

	Array<int> iArray(16);
	Array<float> fArray(16);

	for (size_t i = 0; i < 16; i++)
	{
		iArray[i] = rand() % 256;
		fArray[i] = (float)(rand() % 256) / 256.0f;
	}

	PrintArray(iArray);
	//PrintArray(fArray);

	RadixSort4(iArray, 4);
	//Quicksort(fArray, 0, 16, CompareFloat);

	PrintArray(iArray);
	//PrintArray(fArray);

	return 0;
}