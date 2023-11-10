#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
	Base()
	{
		/*
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		rep stos esp<->ebp 0xCCCCCCCCC
		vfptr <- &Base::vftable
		*/
		cout << "call Base()" << endl;
		clear();
	}
	void clear() { memset(this, 0, sizeof(*this)); }
	virtual void show()
	{
		cout << "call Base::show()" << endl;
	}
};

class Derive : public Base
{
public:
	Derive()
	{
		/*
		push ebp
		mov ebp, esp
		sub esp, 4Ch
		rep stos esp<->ebp 0xCCCCCCCCC
		vfptr <- &Derive::vftable
		*/
		cout << "call Derive()" << endl;
	}
	void show()
	{
		cout << "call Derive::show()" << endl;
	}
};

int main()
{
	Base* pb1 = new Base();
	/*
	mov eax, dword ptr[pb1]
	mov ecx, dword ptr[eax] eax:0x00000000 不是Base::vftable
	call ecx
	*/
	pb1->show();
	delete pb1;

	// 正常运行
	/*Base* pb2 = new Derive();
	pb2->show();
	delete pb2;*/

	return 0;
}