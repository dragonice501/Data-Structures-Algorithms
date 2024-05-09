#include "Array.h"

template<class DataType>
class Heap : public Array<DataType>
{
private:
	using Array<DataType>::mArray;
	using Array<DataType>::mSize;

public:
	size_t mCount;
	int(*mCompare)(DataType, DataType);

public:
	Heap(size_t size, int(*compare)(DataType, DataType)) : Array<DataType>(size + 1)
	{
		mCount = 0;
		mCompare = compare;
	}

	DataType& Item()
	{
		return mArray[1];
	}

	void Enqueue(DataType data)
	{
		mCount++;
		if (mCount >= mSize) this->Resize(mSize * 2);

		mArray[mCount] = data;

		WalkUp(mCount);
	}
	void WalkUp(size_t index)
	{
		size_t parent = index / 2;
		size_t child = index;
		DataType temp = mArray[child];

		while (parent > 0)
		{
			if (mCompare(temp, mArray[parent]) > 0)
			{
				mArray[child] = mArray[parent];
				child = parent;
				parent /= 2;
			}
			else break;
		}

		mArray[child] = temp;
	}

	void Dequeue()
	{
		if (mCount >= 1)
		{
			mArray[1] = mArray[mCount];
			WalkDown(1);
			mCount--;
		}
	}
	void WalkDown(size_t index)
	{
		size_t parent = index;
		size_t child = index * 2;
		DataType temp = mArray[parent];
		while (child < mCount)
		{
			if (child < mCount - 1)
			{
				if (mCompare(mArray[child], mArray[child + 1]) < 0) child++;
			}

			if (mCompare(temp, mArray[child]) < 0)
			{
				mArray[parent] = mArray[child];
				parent = child;
				child *= 2;
			}
			else break;
		}

		mArray[parent] = temp;
	}

	void Foo();
};