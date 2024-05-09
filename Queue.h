#include "Array.h"
#include "DLinkedList.h"

template<class DataType>
class LQueue : public DLinkedList<DataType>
{
public:
	size_t Count() { return  DLinkedList::mCount; }

	DataType Front() { return DLinkedList::mHead; }

	void Enqueue(DataType data) { Append(data); }
	void Dequeue() { DLinkedList::RemoveHead(); }
};

template<class DataType>
class AQueue : public Array<DataType>
{
public:
	size_t mFront;
	size_t mCount;

public:
	AQueue(size_t size) : Array<DataType>(size)
	{
		mFront = 0;
		mCount = 0;
	}

	DataType& operator[] (size_t index)
	{
		return Array::mArray[(index + mFront) % Array::mSize];
	}

	DataType Front() { return Array::mArray[mFront]; }

	bool Enqueue(DataType data)
	{
		if (Array::mSize != mCount)
		{
			Array::mArray[(mCount + mFront) % Array::mSize] = data;
			mCount++;
			return true;
		}

		return false;
	}
	void Dequeue()
	{
		if (mCount > 0)
		{
			mCount--;
			mFront++;
			if (mFront == Array::mSize) mFront = 0;
		}
	}
};