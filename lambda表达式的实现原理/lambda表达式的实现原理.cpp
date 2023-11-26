#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

/*
lambda表达式的语法：
[捕获外部变量]（形参列表)->返回值{操作代码};

如果lambda表达式的返回值不需要，那么"->返回值"可以省略

[捕获外部变量]
[]: 表示不捕获任何外部变量
[=]: 以传值的方式捕获外部的所有变量
[&]: 以传引用的方式捕获外部的所有变量
[this]: 捕获外部的this指针
[=, &a]: 以传值的方式捕获外部的所有变量，但是a变量以传引用的方式捕获
[a, b]: 以值传递的方式捕获外部变量a和b
[a, &b]: a以值传递捕获，b以传引用的方式捕获
*/

class TestLambda03
{
public:
	TestLambda03(int& a, int& b): ma(a), mb(b) {}
	void operator() () const
	{
		int tmp = ma;
		ma = mb;
		mb = tmp;
	}
private:
	int& ma;
	int& mb;
};

int main()
{
	auto func1 = []() {cout << "hello world!" << endl; };
	func1();

	auto func2 = [](int a, int b)->int {return a + b; };
	cout << func2(20, 30) << endl;

	int a = 10;
	int b = 20;
	/*auto func3 = [a, b]() mutable
		{
			int tmp = a;
			a = b;
			b = tmp;
		};*/
	auto func3 = [&a, &b]()
		{
			int tmp = a;
			a = b;
			b = tmp;
		};
	func3();
	/*TestLambda03 t1(a, b);
	t1();*/
	cout << "a:" << a << " b:" << b << endl;

	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	sort(vec.begin(), vec.end(), [](int a, int b)-> bool
		{
			return a > b;
		});
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	auto it = find_if(vec.begin(), vec.end(), 
		[](int a)->bool
		{
			return a < 65;
		});
	if (it != vec.end())
	{
		vec.insert(it, 65);
	}
	for (int val : vec)
	{
		cout << val << " ";
	}
	cout << endl;

	for_each(vec.begin(), vec.end(), 
		[](int a)
		{
			if (a % 2 == 0) { cout << a << " "; }	
		});

	return 0;
}