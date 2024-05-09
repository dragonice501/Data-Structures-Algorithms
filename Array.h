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

	bool WriteFile(const char* filename)
	{
		FILE* outfile = 0;
		int written = 0;

		fopen_s(&outfile, filename, "wb");
		if (outfile == 0) return false;

		written = fwrite(mArray, sizeof(DataType), mSize, outfile);
		fclose(outfile);

		if (written != mSize) return false;

		return true;
	}
	bool ReadFile(const char* filename)
	{
		FILE* infile = 0;
		int read = 0;

		fopen_s(&infile, filename, "rb");
		if (infile == 0) return false;

		read = fread(mArray, sizeof(DataType), mSize, infile);
		fclose(infile);

		if (read != mSize) return false;

		return true;
	}
};