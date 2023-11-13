#include <iostream>
using namespace std;

class Base
{
public:
	virtual void func() = 0;
};

class Derive1 : public Base
{
public:
	void func() { cout << "call Derive1::func" << endl; }
};

class Derive2 : public Base
{
public:
	void func() { cout << "call Derive2::func" << endl; }
	// 实现新功能API
	void derive02func()
	{
		cout << "call Derive2::derive02func" << endl;
	}
};

void showFunc(Base* p)
{
	// dynamic_cast会检查p指针是否指向的是一个Derive2类型的对象？
	// p->vfptr->vftable RTTI信息 如果是，dynamic_cast转换类型成功，
	// 返回Derive2对象的地址给pd2；否则返回nullptr
	Derive2* pd2 = dynamic_cast<Derive2*>(p);
	if (pd2 != nullptr)
	{
		pd2->derive02func();
	}
	else
	{
		p->func();
	}
}

int main()
{
	Derive1 d1;
	Derive2 d2;
	showFunc(&d1);
	showFunc(&d2);

	return 0;
}