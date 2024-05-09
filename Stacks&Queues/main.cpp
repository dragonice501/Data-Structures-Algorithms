#include <iostream>

template<class DataType>
class Array
{
public:
	DataType* mArray;
	size_t mSize;

public:
	Array(const size_t size)
	{
		mArray = new DataType[size];
		mSize = size;
	}

	~Array()
	{
		if (mArray) delete[] mArray;

		mArray = nullptr;
	}

	operator DataType* ()
	{
		return mArray;
	}
	DataType& operator[] (const size_t index)
	{
		return mArray[index];
	}

	size_t Size() { return mSize; }

	void Resize(const size_t size)
	{
		DataType* newArray = new DataType[size];
		if (!newArray) return;

		size_t min;
		if (size < mSize) min = size;
		else min = mSize;

		for (size_t i = 0; i < min; i++)
		{
			newArray[i] = mArray[i];
		}

		mSize = size;

		if (mArray) delete[] mArray;

		mArray = newArray;
	}
	void Insert(const DataType& item, const size_t index)
	{
		for (size_t i = mSize - 1; i > index; i--)
		{
			mArray[i] = mArray[i - 1];
		}

		mArray[index] = item;
	}
	void Remove(const size_t index)
	{
		for (size_t i = index + 1; i < mSize; i++)
		{
			mArray[i - 1] = mArray[index];
		}
	}
};

template<class DataType>
class DListNode
{
public:
	DataType mData;
	DListNode<DataType>* mNext = nullptr;
	DListNode<DataType>* mPrevious = nullptr;

public:
	void InsertAfter(DataType data)
	{
		DListNode<DataType>* newNode = new DListNode<DataType>;

		newNode->mData = data;
		if (mNext)
		{
			newNode->mNext = mNext;
			mNext->mPrevious = newNode;
		}
		newNode->mPrevious = this;

		mNext = newNode;
	}
};

template<class DataType>
class DListIterator;

template<class DataType>
class DLinkedList
{
public:
	DListNode<DataType>* mHead = nullptr;
	DListNode<DataType>* mTail = nullptr;
	size_t mCount;

public:
	DLinkedList()
	{
		mHead = nullptr;
		mTail = nullptr;
		mCount = 0;
	}
	~DLinkedList()
	{
		DListNode<DataType>* itr = mHead;
		DListNode<DataType>* temp;
		while (itr)
		{
			temp = itr->mNext;

			delete itr;

			itr = temp;
		}
	}

	DListIterator<DataType> GetIterator()
	{
		return DListIterator<DataType>(this, mHead);
	}

	void Prepend(DataType data)
	{
		DListNode<DataType>* newNode = new DListNode<DataType>;
		newNode->mData = data;
		newNode->mNext = mHead;

		mHead = newNode;

		if (!mTail)
		{
			mTail = mHead;
		}

		mCount++;
	}
	void Append(DataType data)
	{
		if (!mHead)
		{
			mHead = mTail = new DListNode<DataType>;
			mHead->mData = data;
		}
		else
		{
			mTail->InsertAfter(data);
			mTail = mTail->mNext;
		}

		mCount++;
	}
	void RemoveHead()
	{
		DListNode<DataType>* node = nullptr;
		if (mHead)
		{
			node = mHead->mNext;

			delete mHead;

			mHead = node;

			if (mHead == nullptr) mTail = nullptr;
			mCount--;
		}
	}
	void RemoveTail()
	{
		DListNode<DataType>* node = mHead;
		if (mHead)
		{
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				while (node->mNext != mTail)
				{
					node = node->mNext;
				}

				mTail = node;
				delete node->mNext;
				node->mNext = nullptr;
			}

			mCount--;
		}
	}
	void Remove(DListIterator<DataType>& itr)
	{
		DListNode<DataType>* node = mHead;

		if (itr.mList != this) return;

		if (!itr.mNode) return;

		if (itr.mNode == mHead)
		{
			itr.Forth();
			RemoveHead();
		}
		else
		{
			while (node->mNext != itr.mNode)
			{
				node = node->mNext;
			}

			itr.Forth();
			if (node->mNext == mTail)
			{
				mTail = node;
			}

			delete node->mNext;

			node->mNext = itr.mNode;
		}

		mCount--;
	}
	void Insert(DListIterator<DataType>& itr, DataType data)
	{
		if (itr.mList != this) return;

		if (itr.mNode)
		{
			itr.mNode->InsertAfter(data);

			if (itr.mNode == mTail) mTail = itr.mNode->mNext;

			mCount++;
		}
		else
		{
			Append(data);
		}
	}
};

template<class DataType>
class DListIterator
{
public:
	DListNode<DataType>* mNode = nullptr;
	DLinkedList<DataType>* mList = nullptr;

public:
	DListIterator(DLinkedList<DataType>* list = nullptr, DListNode<DataType>* node = nullptr)
	{
		mList = list;
		mNode = node;
	}

	bool Valid()
	{
		return mNode != nullptr;
	}
	DataType& Item()
	{
		return mNode->mData;
	}

	void Start()
	{
		if (mList)
		{
			mNode = mList->mHead;
		}
	}
	void Forth()
	{
		if (mNode)
		{
			mNode = mNode->mNext;
		}
	}
};

template<class DataType>
class LStack : public DLinkedList<DataType>
{
public:
	DataType Top() { return DLinkedList::mTail->mData; }
	size_t Count() { return  DLinkedList::mCount; }
	void Push(DataType data) { Append(data); }
	void Pop() { DLinkedList::RemoveTail(); }
};

template<class DataType>
class AStack : public Array<DataType>
{
public:
	size_t mTop;

public:
	AStack(size_t size) : Array<DataType>(size)
	{
		mTop = 0;
	}

	size_t Count() { return mTop; }
	DataType Top() { return Array::mArray[mTop - 1]; }

	bool Push(DataType data)
	{
		if (Array::mSize != mTop)
		{
			Array::mArray[mTop] = data;
			mTop++;
			return true;
		}

		return false;
	}
	void Pop()
	{
		if (mTop > 0) mTop--;
	}
};

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

int main()
{


	return 0;
}