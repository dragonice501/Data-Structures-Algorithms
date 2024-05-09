#include <iostream>

#include "../BinaryTree.h"
#include "../BitVector.h"
#include "../Heap.h"

template<class DataType>
class RLEPair
{
public:
	DataType mData;
	unsigned char mLength;
};

template<class DataType>
class RLE
{
public:
	typedef RLEPair<DataType> Pair;
	Array<Pair> mRLE;
	int mRuns;
	int mSize;

	RLE() : mRLE(1)
	{
		mRuns = 0;
		mSize = 0;
	}

	void CreateRLE(Array<DataType>& array)
	{
		size_t currentRun = 0;

		mRLE[0].mData = array[0];
		mRLE[0].mLength = 1;

		mSize = array.Size();

		for (size_t i = 0; i < array.Size(); i++)
		{
			if (array[i] != mRLE[currentRun].mData)
			{
				currentRun++;
				if (mRLE.mSize == currentRun) mRLE.Resize(currentRun * 2);

				mRLE[currentRun].mData = array[i];
				mRLE[currentRun].mLength = 1;
			}
			else
			{
				if (mRLE[currentRun].mLength == 255)
				{
					currentRun++;
					if (mRLE.mSize == currentRun) mRLE.Resize(currentRun * 2);

					mRLE[currentRun].mData = array[i];
					mRLE[currentRun].mLength = 1;
				}
				else
				{
					mRLE[currentRun].mLength++;
				}
			}

			mRuns = currentRun + 1;
		}
	}
	void FillArray(Array<DataType>& array)
	{
		if (array.Size() < mSize) array.Resize(mSize);

		size_t offset;

		for (size_t currentRun = 0; currentRun < mRuns; currentRun++)
		{
			for (size_t i = 0; i < mRLE[currentRun].mLength; i++)
			{
				array[offset + i] = mRLE[currentRun].mData;
			}

			offset += mRLE[currentRun].mLength;
		}
	}
	void SaveData(char* name)
	{
		FILE* file = 0;
		fopen_s(&file, name, "wb");

		fwrite(&mSize, sizeof(int), 1, file);
		fwrite(&mRuns, sizeof(int), 1, file);
		fwrite(mRLE.mArray, sizeof(Pair), mRuns, file);

		fclose(file);
	}
	void LoadData(char* name)
	{
		FILE* file = fopen(name, "rb");
		fread(&mSize, sizeof(int), 1, file);
		fread(&mRuns, sizeof(int), 1, file);

		if (mRLE.Size() < mRuns) mRLE.Resize(mRuns);

		fread(mRLE.mArray, sizeof(Pair), mRuns, file);
		fclose(file);
	}
};

template<class DataType>
class HuffmanNode
{
public:
	DataType mData;
	unsigned long int mCode;
	size_t mCodeLength;
};

template<class DataType>
class HuffmanFrequency
{
public:
	DataType mData;
	int mFrequency;
};

template<class DataType>
int CompareNodes(BinaryTree<HuffmanFrequency<DataType>>* left, BinaryTree<HuffmanFrequency<DataType>>* right)
{
	return right->mData.mFrequency - left->mData.mFrequency;
}

template<class DataType, unsigned long int maxValue>
class HuffMan
{
public:
	typedef HuffmanNode<DataType> Node;
	typedef HuffmanFrequency<DataType> Frequency;
	typedef BinaryTree<Frequency> TreeNode;

	BitVector mCompressedData;
	size_t mDataLength;
	size_t mCompressedLength;

	Array<Node> mHuffmanTree;
	int mMaxEntry;

	Array<Node> mLookupTable;

	HuffMan() :
		mCompressedData(1), mHuffmanTree(1), mLookupTable(maxValue + 1)
	{
		mDataLength = 0;
		mCompressedLength = 0;
		mMaxEntry = 0;
	}

	void CalculateTree(Array<DataType>& array)
	{
		Array<int> frequencyTable(maxValue + 1);
		for (size_t i = 0; i <= maxValue; i++)
		{
			frequencyTable[i] = 0;
		}
		for (size_t i = 0; i < array.Size(); i++)
		{
			frequencyTable[array[i]]++;
		}

		Heap<TreeNode*> heap(frequencyTable.Size(), CompareNodes);
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;

		for (size_t i = 0; i <= maxValue; i++)
		{
			if(frequencyTable[i] != 0)
			{
				parent = new TreeNode;
				parent->mData.mData = i;
				parent->mData.mFrequency = frequencyTable[i];
				heap.Enqueue(parent);
			}
		}

		while (heap.mCount > 1)
		{
			left = heap.Item();
			heap.Dequeue();

			right = heap.Item();
			heap.Dequeue();

			parent->mData.mFrequency = left->mData.mFrequency + right->mData.mFrequency;

			heap.Enqueue(parent);
		}

		ConvertTreToArray(heap.mArray[1]);
		CreateLookUpTable();
		delete heap.mArray[1];
	}

	void CreateLookUpTable()
	{
		for (size_t i = 0; i < mMaxEntry; i++)
		{
			if (mHuffmanTree[i].mCodeLength != 0)
			{
				mLookupTable[mHuffmanTree[i].mData] = mHuffmanTree[i];
			}
		}
	}
};

int main()
{
	Array<char> original(1);
	Array<char> uncompressed(1);
	RLE<char> compressed;

	char filename[80];
	size_t index;

	std::cout << "Enter file name: ";
	std::cin >> filename;

	original.ReadFile(filename);
	compressed.CreateRLE(original);

	strcat_s(filename, ".rle");
	compressed.SaveData(filename);

	std::cout << "Original File Size : " << compressed.mSize << std::endl;
	std::cout << "Compressed File Size : " << compressed.mRuns * 2 << std::endl;
	std::cout << "Compression Ratio : ";
	std::cout << (float)(compressed.mSize) / (float)(compressed.mRuns * 2);
	std::cout << std::endl;

	return 0;
}