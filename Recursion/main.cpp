#include <iostream>

void Hanoi(int n, int s, int d, int o)
{
	if (n > 0)
	{
		Hanoi(n - 1, s, o, d);
		std::cout << "Moving " << n << " from " << s << " to " << d << std::endl;
		Hanoi(n - 1, o, d, s);
	}
}

int main()
{
	Hanoi(3, 1, 3, 2);

	return 0;
}