#include <iostream>

const size_t ARRAY_SIZE = 10;

int gInts[ARRAY_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
float gFloats[ARRAY_SIZE] = { 0.0f, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f };

template<class T>
T Sum(T* array, int count)
{
	T sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += array[i];
	}

	return sum;
}

template<class T>
class Adder
{
private:
	T mSum;

public:
	Adder() { mSum = 0; }

	T GetSum() { return mSum; }

	void Add(T number) { mSum += number; }
};

template<class SumType, class AverageType>
AverageType Average(SumType* array, AverageType count)
{
	SumType sum = 0;
	for (size_t i = 0; i < count; i++)
	{
		sum += array[i];
	}

	return static_cast<AverageType>(sum / count);
}

template<class DataType, size_t size, DataType zero>
class Array
{
private:
	DataType mArray[size];

public:
	void Set(DataType item, size_t index) { mArray[index] = item; }

	DataType Get(size_t index) { return mArray[index]; }

	void Clear(size_t index) { mArray[index] = zero; }
};

int main()
{
	std::cout << "Template func int: " << Sum(gInts, ARRAY_SIZE) << std::endl;
	std::cout << "Template func float: " << Sum(gFloats, ARRAY_SIZE) << std::endl << std::endl;

	Adder<int> intAdder;
	Adder<float> floatAdder;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		intAdder.Add(gInts[i]);
		floatAdder.Add(gFloats[i]);
	}

	std::cout << "Template class int: " << intAdder.GetSum() << std::endl;
	std::cout << "Template class float: " << floatAdder.GetSum() << std::endl << std::endl;

	std::cout << "Template multiple ints average: " << Average(gInts, 10) << std::endl;
	std::cout << "Template multiple floats average: " << Average(gFloats, 10.0f) << std::endl << std::endl;

	Array<int, 5, 0> intArrayFive;
	Array<int, 10, 42> intArrayTen;
	Array<float, 15, 0.5f> floatArrayFifteen;

	intArrayFive.Set(10, 0);
	intArrayFive.Set(3, 1);
	intArrayTen.Set(11, 9);
	intArrayTen.Set(2, 4);
	floatArrayFifteen.Set(10.1f, 3);
	floatArrayFifteen.Set(3.1415f, 14);

	std::cout << "Template intArray5 at 0: " << intArrayFive.Get(0) << std::endl;
	std::cout << "Template intArray5 at 1: " << intArrayFive.Get(1) << std::endl;
	std::cout << "Template intArray10 at 9: " << intArrayTen.Get(9) << std::endl;
	std::cout << "Template intArray10 at 4: " << intArrayTen.Get(4) << std::endl;
	std::cout << "Template floatArray15 at 3: " << floatArrayFifteen.Get(3) << std::endl;
	std::cout << "Template floatArray15 at 14: " << floatArrayFifteen.Get(14) << std::endl << std::endl;

	intArrayFive.Clear(0);
	intArrayTen.Clear(0);
	floatArrayFifteen.Clear(0);

	std::cout << "Template intArray5 clear at 0: " << intArrayFive.Get(0) << std::endl;
	std::cout << "Template intArray10 clear at 0: " << intArrayTen.Get(0) << std::endl;
	std::cout << "Template floatArray15 clear at 0: " << floatArrayFifteen.Get(0) << std::endl;

	return 0;
}