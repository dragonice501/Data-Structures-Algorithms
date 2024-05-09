#include <iostream>
#include <random>

class Monster
{
public:
	int x, y, hitPoints;
};

template<class DataType>
class Array
{
private:
	DataType* mArray;
	int mSize;

public:
	Array(const size_t size)
	{
		mArray = new DataType[size];
		mSize = size;
	}

	~Array()
	{
		if(mArray) delete[] mArray;

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

Array<Monster> gMonsterArray(32);
size_t gMonsters = 0;

bool AddMonster()
{
	if (gMonsters == gMonsterArray.Size())
	{
		gMonsterArray.Resize(gMonsterArray.Size() + 32);
	}

	gMonsterArray[gMonsters].x = rand() % 640;
	gMonsterArray[gMonsters].y = rand() % 480;
	gMonsterArray[gMonsters].hitPoints = 11 + (rand() % 10);
	gMonsters++;

	return true;
}

void RemoveMonster(const size_t index)
{
	gMonsters--;
	gMonsterArray[index] = gMonsterArray[gMonsters];
}

void CheckMonsters()
{
	size_t index = 0;
	while (index < gMonsters)
	{
		if (gMonsterArray[index].hitPoints <= 0)
			RemoveMonster(index);
		else
			index++;
	}
}

int main()
{
	srand(time(NULL));

	int array[] = { 0, 1, 2, 3, 4, 5, 6 };

	std::cout << sizeof(array) / sizeof(int) << std::endl;

	int* dynArray = new int[10];
	for (size_t i = 0; i < 10; i++)
	{
		dynArray[i] = i;
	}

	int* temp = new int[20];
	for (size_t i = 0; i < 10; i++)
	{
		temp[i] = dynArray[i];
	}

	delete[] dynArray;
	dynArray = temp;
	temp = nullptr;

	Array<int> intArray(10);
	Array<float> floatArray(5);

	intArray[0] = 10;
	floatArray[0] = 3.1415f;

	int i = intArray[0];
	float f = floatArray[0];

	intArray[1] = 12;
	floatArray[1] = 6.28f;

	intArray.Insert(11, 1);
	floatArray.Insert(4.2f, 1);

	intArray.Remove(0);
	floatArray.Remove(0);

	intArray.Resize(3);
	floatArray.Resize(4);



	return 0;
}