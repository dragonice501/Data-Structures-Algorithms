#include <iostream>
#include <fstream>
#include <random>

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

class Player
{
public:
	int life, money, experience, level;
};

Array<Player> gPlayers(64);
BitVector gModifiedStates(64);

void GameInit()
{
	for (size_t i = 0; i < 64; i++)
	{
		gPlayers[i].life = 11 + rand() % 10;
		gPlayers[i].money = rand() % 100;
		gPlayers[i].experience = 0;
		gPlayers[i].level = 1 + rand() % 5;
	}

	gModifiedStates.SetAll();
}

void SetMoney(size_t player, size_t money)
{
	gPlayers[player].money = money;
	gModifiedStates.Set(player, true);
}

void SetExperience(size_t player, size_t experience)
{
	gPlayers[player].experience = experience;
	gModifiedStates.Set(player, true);
}

void SetLevel(size_t player, size_t level)
{
	gPlayers[player].level = level;
	gModifiedStates.Set(player, true);
}

bool SavePlayers(const char* filename)
{
	std::ifstream gameSaveInFile;
	gameSaveInFile.open(filename);
	if (gameSaveInFile.is_open())
	{
		gameSaveInFile.close();
		std::remove(filename);
	}

	std::ofstream gameSaveOutFile;
	gameSaveOutFile.open(filename);
	if (gameSaveOutFile.is_open())
	{
		for (int i = 0; i < 64; i++)
		{
			if (gModifiedStates[i])
			{
				gameSaveOutFile <<
					i << ' ' <<
					gPlayers[i].experience << ' ' <<
					gPlayers[i].level << ' ' <<
					gPlayers[i].life << ' ' <<
					gPlayers[i].money << ' ' <<
					std::endl;
			}
		}
	}
	gameSaveInFile.close();

	gModifiedStates.ClearAll();

	return true;
}

bool LoadPlayers()
{
	/*char* type;
	std::ifstream gameSaveInFile(char* filename);
	while (gameSaveInFile >> type)
	{
		int index = 0;
		gameSaveInFile >> gPlayers[index].experience;
	}*/

	return true;
}

int main()
{
	srand(time(NULL));

	BitVector bits(32);
	bool b;

	bits.Set(0, true);
	b = bits[0];

	if (b) std::cout << "0 is true" << std::endl;

	bits.Set(31, false);
	b = bits[31];

	if (!b) std::cout << "31 is false" << std::endl;
	else std::cout << "31 is true" << std::endl;

	bits.ClearAll();
	for (size_t i = 0; i < 32; i++)
	{
		if (bits[i]) std::cout << i << " is true" << std::endl;
		else std::cout << i << " is false" << std::endl;
	}

	bits.SetAll();
	for (size_t i = 0; i < 32; i++)
	{
		if (bits[i]) std::cout << i << " is true" << std::endl;
		else std::cout << i << " is false" << std::endl;
	}

	bits.Resize(48);

	std::cout << bits.Size() << std::endl;

	return 0;
}