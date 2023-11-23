#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

template<typename T>
class MyDeleter
{
public:
	void operator() (T* ptr) const
	{
		cout << "call MyDeleter.operator()" << endl;
		delete[] ptr;
	}
};

template<typename T>
class MyFileDeleter
{
public:
	void operator() (T* ptr) const
	{
		cout << "call MyFileDeleter.operator()" << endl;
		fclose(ptr);
	}
};

int main()
{
	//unique_ptr<int, MyDeleter<int>> ptr1(new int[100]);
	//unique_ptr<FILE, MyFileDeleter<FILE>> ptr2(fopen("data.txt", "w"));

	unique_ptr<int, function<void(int*)>> ptr1(new int[100],
		[](int* p)->void {
			cout << "lambda" << endl;
			delete[] p;
		}
	);
	unique_ptr<FILE, function<void(FILE*)>> ptr2(fopen("data.txt", "w"),
		[](FILE* p)->void {
			cout << "lambda file" << endl;
			fclose(p);
		}
	);
	return 0;
}
