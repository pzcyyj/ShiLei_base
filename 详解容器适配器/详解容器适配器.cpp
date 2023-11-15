#include <iostream>
#include <deque>
#include <queue>
#include <stack>
using namespace std;

/*
标准容器 - 容器适配器
1.适配器底层没有自己的数据结构，它是另外一个容器的封装，它的方法全部由底层依赖的容器进行实现
2.没有实现自己的迭代器

template<typename T, typename Container=deque<T>>
class Stack
{
public:
	void push(const T& val) { con.push_back(val); }
	void pop() { con.pop_back(); }
	T top() const { return con.back(); }

private:
	Container con;
};
*/
int main()
{
	stack<int> s1;
	for (int i = 0; i < 20; i++)
	{
		s1.push(rand() % 100 + 1);
	}

	cout << s1.size() << endl;

	while (!s1.empty())
	{
		cout << s1.top() << " ";
		s1.pop();
	}

	return 0;
}
