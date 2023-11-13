#include <iostream>
using namespace std;

class A
{
public:
	virtual void func() { cout << "call A::func()" << endl; }
private:
	int ma;
};

class B : virtual public A
{
public:
	virtual void func() { cout << "call B::func()" << endl; }
private:
	int mb;
};

/*
A a; 4个字节
B b; 8个字节 + 4 = 12字节 vbptr
*/

int main()
{
	// 基类指针指向派生类对象，永远指向的是派生类基类部分数据的起始地址
	A* p = new B();
	p->func();
	delete p;

	return 0;
}