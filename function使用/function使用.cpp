#include <iostream>
#include <functional>
#include <map>
using namespace std;


/*
1.用函数类型实例化function
2.通过function调用operator()函数时，需要根据函数类型传入相应的参数
*/

#if 0
void hello1() { cout << "hello world" << endl; }
void hello2(string str) { cout << str << endl; }

class Test
{
public:
	void hello(string str) { cout << str << endl; }
};

int main()
{
	function<void()> func1 = hello1;
	func1();

	function<void(string)> func2 = hello2;
	func2("hello nmd");

	function<int(int, int)> func3 = [](int a, int b)->int { return a + b; };
	cout << func3(10, 20) << endl;

	function<void(Test*, string)> func4 = &Test::hello;

	func4(new Test(), "call Test::hello!");

	return 0;
}
#endif // 0

void doShowAllBooks() { cout << "查看所有书籍信息" << endl; }
void doBorrow() { cout << "借书" << endl; }
void doBack() { cout << "还书" << endl; }
void doQueryBooks() { cout << "查询书籍" << endl; }
void doLoginOut() { cout << "注销" << endl; }

int main()
{
	int choice = 0;
	// 跟函数指针相比，应用更广泛，可以接收lambda表达式，绑定器
	map<int, function<void()>> actionMap;
	actionMap.insert({ 1, doShowAllBooks });
	actionMap.insert({ 2, doBorrow });
	actionMap.insert({ 3, doBack });
	actionMap.insert({ 4, doQueryBooks });
	actionMap.insert({ 5, doLoginOut });
	for (; ;)
	{
		cout << "-----------------" << endl;
		cout << "1.查看所有书籍信息" << endl;
		cout << "2.借书" << endl;
		cout << "3.还书" << endl;
		cout << "4.查询书籍" << endl;
		cout << "5.注销" << endl;
		cout << "-----------------" << endl;
		cout << "请选择:";
		cin >> choice;
	

	auto it = actionMap.find(choice);
	if (it != actionMap.end())
	{
		it->second();
	}
	else
	{
		cout << "输入数字无效，重新选择！" << endl;
	}

	}
	/*
	switch (choice) // 不好，因为这块代码无法闭合  无法做到“开-闭”原则 不好增删改功能
	{
	case1:
		break;
	case2:
		break;
	case3:
		break;
	case4:
		break;
	case5:
		break;
	default:
		break;
	}
	*/

	return 0;
}