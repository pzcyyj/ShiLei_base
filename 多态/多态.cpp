#include <iostream>
#include <string>
using namespace std;
/*
如何解释多态？
静态（编译时期）的多态：函数重载（在编译阶段就确定好调用的函数版本）、模板（函数模板和类模板）
动态（运行时期）的多态：
在继承结构中，基类指针（引用）指向派生类对象，通过该指针（引用）调用同名覆盖方法（虚函数），
基类指针指向哪个派生类对象，就会调用哪个派生类的覆盖方法，称为多态
pbase->show();
多态底层是通过动态绑定来实现的，pbase-》访问谁的vfptr=》继续访问谁的vftable
                                   =》当然调用的是对应的派生类对象的方法
*/

class Animal
{
public:
	Animal(string name) : _name(name) {}
	virtual void bark() {}
protected:
	string _name;
};

class Cat : public Animal
{
public:
	Cat(string name) : Animal(name) {}
	void bark() { cout << _name << " bark: miao miao!" << endl; }
};


class Dog : public Animal
{
public:
	Dog(string name) : Animal(name) {}
	void bark() { cout << _name << " bark: wang wang!" << endl; }
};

class Pig : public Animal
{
public:
	Pig(string name) : Animal(name) {}
	void bark() { cout << _name << " bark: heng heng!" << endl; }
};

/*
下面的API无法做到“开-闭”原则

void bark(Cat &cat)
{
	cat.bark();
}

void bark(Dog& dog)
{
	dog.bark();
}

void bark(Pig& pig)
{
	pig.bark();
}
*/

void bark(Animal* p)
{
	p->bark();
}

int main()
{
	Cat cat("猫咪");
	Dog dog("二哈");
	Pig pig("佩奇");

	bark(&cat); // 动态绑定
	bark(&dog);
	bark(&pig);

	return 0;
}
