#include<iostream>
#include<typeinfo>
using namespace std;

#if 0
class Base
{
public:
	Base(int data = 10) : ma(data) {}
	void show() { cout << "Base::show()" << endl; }
	void show(int) { cout << "Base:show(int)" << endl; } 
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 20) : Base(data), mb(data) {}
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main()
{
	Derive d(50);
	Base* pb = &d;
	pb->show(); // 静态（编译时期）的绑定（函数的调用）call        Base::show (0851037h)
	pb->show(10); // 静态绑定 call        Base::show (0851307h)

	cout << sizeof(Base) << endl; // 4
	cout << sizeof(Derive) << endl; // 8

	cout << typeid(pb).name() << endl; // Base*
	cout << typeid(*pb).name() << endl; // Base

	return 0;
}
#endif

class Base
{
public:
	Base(int data = 10) : ma(data) {}
	virtual void show() { cout << "Base::show()" << endl; }
	virtual void show(int) { cout << "Base:show(int)" << endl; }
protected:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 20) : Base(data), mb(data) {}
	/*
	如果派生类的方法，和基类继承来的某个方法，返回值、函数名、参数列表都相同，
	而且基类的方法是virtual虚函数，那么派生类的这个方法，自动处理成虚函数
	重写《=》覆盖
	*/
	void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main()
{
	Derive d(50);
	Base* pb = &d;

	/*
	pb -> Base Base::show 如果发现show是普通函数，就进行静态绑定

	pb -> Base Base::show 如果发现show是虚函数，就进行动态绑定
	mov eax, dword ptr[pb]  // 取pb的vfptr放入eax
	mov ecx, dword ptr[eax] // 将vfptr指向的虚函数地址放入ecx
	call ecx // 动态（运行时期）的绑定（函数的调用）
	*/
	pb->show(); // 
	pb->show(10); // 

	cout << sizeof(Base) << endl; // 8
	cout << sizeof(Derive) << endl; // 12

	cout << typeid(pb).name() << endl; // class Base *
	/*
	pb的类型：Base -> 有没有虚函数
	如果Base没有虚函数，*pb识别的就是编译时期的类型  *pb  <=> Base类型
	如果Base有虚函数，*pb识别的就是运行时期的类型 RTTI类型
	pb->d(vfptr)->Derive
	*/
	cout << typeid(*pb).name() << endl; // class Derive

	return 0;
}
