class BitVector
{
private:
	unsigned long int* mArray;
	size_t mSize;

public:
	BitVector(size_t size)
	{
		mArray = nullptr;
		mSize = 0;

		Resize(size);
	}
	~BitVector()
	{
		if (mArray) delete[] mArray;
		mArray = nullptr;
	}

	bool operator[] (size_t index)
	{
		int cell = index / 32;
		int bit = index % 32;
		return (mArray[cell] & (1 << bit)) >> bit;
	}

	size_t Size() { return mSize; }

	void ClearAll()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mArray[i] = 0;
		}
	}

	void Set(size_t index, bool value)
	{
		int cell = index / 32;
		int bit = index % 32;

		if (value) mArray[cell] = mArray[cell] | (1 << bit);
		else mArray[cell] = mArray[cell] | (~(1 << bit));
	}

	void SetAll()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mArray[i] = 0xFFFFFFFF;
		}
	}

	void Resize(size_t size)
	{
		unsigned long int* newVector = nullptr;

		if (size % 32 == 0) size = size / 32;
		else size = (size / 32) + 1;

		newVector = new unsigned long int[size];

		if (!newVector) return;

		int min;

		if (size < mSize) min = size;
		else min = mSize;

		for (size_t i = 0; i < min; i++)
		{
			newVector[i] = mArray[i];
		}

		mSize = size;

		if (mArray) delete[] mArray;

		mArray = newVector;
	}
};