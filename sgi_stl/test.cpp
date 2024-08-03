#include <iostream>
#include "myallocator.h"
#include <vector>
using namespace std;

int main()
{
	vector<int, myallocator<int>> vec;

	for (int i = 0; i < 100; ++i)
	{
		vec.push_back(rand() % 1000);
	}

	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	return 0;
}