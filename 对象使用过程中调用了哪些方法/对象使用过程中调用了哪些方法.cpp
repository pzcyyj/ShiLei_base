#include <iostream>
using namespace std;

class Test
{
public:
	Test(int a = 5, int b = 5) : ma(a), mb(b) { cout << "Test(" << ma << ", " << mb << ")" << endl; }
	~Test() { cout << "~Test(" << ma << ", " << mb << ")" << endl; }
	Test(const Test& t) : ma(t.ma), mb(t.mb) { cout << "Test(const Test& t)" << ma << endl; }
	Test& operator = (const Test& t)
	{
		cout << "operator=" << endl;
		ma = t.ma;
		mb = t.mb;
		return *this;
	}
	Test& operator + (const Test& t)
	{
		cout << "operator+" << endl;
		ma = t.ma + ma;
		return *this;
	}
	void setMa(int ma)
	{
		this->ma = ma;
	}
private:
	int ma;
	int mb;
};

Test func(Test t1, Test t2)
{
	Test t = t1 + t2;
	t.setMa(20);
	return t;
}

//Test t1(10, 10);

int main()
{
	Test t1(5);
	Test t2(6);
	cout << "----------------------" << endl;
	t2 = Test(100); // 会显示生成临时对象，会调用构造析构
	cout << "----------------------" << endl;
	t2 = (Test)30; // 会显示生成临时对象，会调用构造析构
	cout << "----------------------" << endl;
	t2 = 40; // 会隐式生成临时对象，会调用构造析构
	cout << "----------------------" << endl;
	//Test* p = &Test(40);  // 不安全的，vs22直接编译不过
	const Test& ref = Test(50); // 是ok的，临时对象不会被马上析构
	cout << "----------------------" << endl;
	Test t7 = func(t1, t2);
	Test t6(20, 20);
	Test t3 = t6;
	Test t5(10, 10);
	const Test& ref = Test(50, 51);
	static Test t4 = Test(24, 24); // 程序运行结束时析构
	cout << "----------------------" << endl;
	Test* p1 = new Test[2];
	delete[] p1;
	return 0;
}


//Test t10(20, 30); // 在main函数执行前构造，main函数结束后析构