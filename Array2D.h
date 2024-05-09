template<class DataType>
class Array2D
{
private:
	DataType* mArray;
	int mWidth, mHeight;

public:
	Array2D(const size_t width, const size_t height)
	{
		mArray = new DataType[width * height];
		mWidth = width;
		mHeight = height;
	}
	~Array2D()
	{
		if (mArray) delete[] mArray;
		mArray = nullptr;
	}

	DataType& Get(const size_t x, const size_t y)
	{
		return mArray[x + y * mWidth];
	}

	size_t Width() { return mWidth; }
	size_t Height() { return mHeight; }
	size_t Size() { return mWidth * mHeight; }

	void Resize(size_t width, size_t height)
	{
		DataType* newArray = new DataType[width * height];
		if (!newArray) return;

		size_t x, y, t1, t2;
		size_t minX = width < mWidth ? width : mWidth;
		size_t minY = height < height ? height : mHeight;

		for (y = 0; y < minY; y++)
		{
			t1 = y * width;
			t2 = y * mWidth;

			for (x = 0; x < minX; x++)
			{
				newArray[t1 + x] = mArray[t2 + x];
			}
		}

		if (mArray) delete[] mArray;
		mArray = newArray;
		mWidth = width;
		mHeight = height;
	}
};