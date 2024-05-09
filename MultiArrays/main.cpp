#include <iostream>

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

template <class Datatype>
class Array3D
{
private:
	Datatype* mArray;
	size_t mWidth;
	size_t mHeight;
	size_t mDepth;

public:
	Array3D(size_t p_width, size_t p_height, size_t p_depth)
	{
		mArray = new Datatype[p_width * p_height * p_depth];
		mWidth = p_width;
		mHeight = p_height;
		mDepth = p_depth;
	}
	~Array3D()
	{
		if (mArray != 0) delete[] mArray;
		mArray = 0;
	}

	Datatype& Get(size_t p_x, size_t p_y, size_t p_z)
	{
		return mArray[(p_z * mWidth * mHeight) + (p_y * mWidth) + p_x];
	}

	size_t Size() { return mWidth * mHeight * mDepth; }
	size_t Width() { return mWidth; }
	size_t Height() { return mHeight; }
	size_t Depth() { return mDepth; }

	void Resize(size_t p_width, size_t p_height, size_t p_depth)
	{
		Datatype* newarray = new Datatype[p_width * p_height * p_depth];
		if (newarray == 0) return;

		size_t x, y, z, t1, t2, t3, t4;
		size_t minx = (p_width < mWidth ? p_width : mWidth);
		size_t miny = (p_height < mHeight ? p_height : mHeight);
		size_t minz = (p_depth < mDepth ? p_depth : mDepth);
		for (z = 0; z < minz; z++)
		{
			t1 = z * p_width * p_height;
			t2 = z * mWidth * mHeight;
			Team LRN
				Dynamic Multi - Dimensional Arrays 129
				for (y = 0; y < miny; y++)
				{
					t3 = y * p_width;
					t4 = y * m_width;
					for (x = 0; x < minx; x++)
					{
						newarray[t1 + t3 + x] = m_array[t2 + t4 + x];
					}
				}
		}

		if (mArray != 0)
			delete[] mArray;

		mArray = newarray;
		mWidth = p_width;
		mHeight = p_height;
		mDepth = p_depth;
	}
};

int main()
{
	Array2D<int> intArray(5, 5);
	Array2D<float> floatArray(4, 4);

	int i;
	float f;

	intArray.Get(4, 4) = 10;
	floatArray.Get(3, 2) = 0.5f;

	i = intArray.Get(4, 4);
	f = floatArray.Get(3, 2);

	std::cout << "i at 4,4 is " << i << std::endl;
	std::cout << "f at 3,2 is " << f << std::endl;

	std::cout << "size of intarray is " << intArray.Size() << std::endl;
	std::cout << "size of floatarray is " << floatArray.Size() << std::endl;

	for (size_t y = 0; y < 5; y++)
	{
		for (size_t x = 0; x < 5; x++)
		{
			intArray.Get(x, y) = x + y * 5;
			std::cout << intArray.Get(x, y) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	intArray.Resize(6, 6);
	for (size_t y = 0; y < 6; y++)
	{
		for (size_t x = 0; x < 6; x++)
		{
			std::cout << intArray.Get(x, y) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return 0;
}