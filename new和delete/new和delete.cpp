#include <iostream>
using namespace std;

void* operator new(size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new addr: " << p << endl;
	return p;
}

void* operator new[](size_t size)
{
	void* p = malloc(size);
	if (p == nullptr)
		throw bad_alloc();
	cout << "operator new[] addr: " << p << endl;
	return p;
}

void operator delete(void* ptr)
{
	cout << "operator delete addr: " << ptr << endl;
	free(ptr);
}

void operator delete[](void* ptr)
{
	cout << "operator delete[] addr: " << ptr << endl;
	free(ptr);
}

class Test
{
public:
	Test(int data = 10) { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }

private:
	int* ptr;
};

int main()
{
	Test* p1 = new Test[6];
	delete p1;
}