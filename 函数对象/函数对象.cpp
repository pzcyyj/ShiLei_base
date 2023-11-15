#include <iostream>
using namespace std;

/*
template<typename T>
bool mygreater(T a, T b)
{
	return a > b;
}

template<typename T>
bool myless(T a, T b)
{
	return a < b;
}
*/

/*
1.通过函数对象调用operator()，可以省略函数的调用开销，比通过函数指针
调用函数（不能够内联调用）效率高
2.因为函数对象是用类生成的，所以可以添加相关的成员变量，用来记录函数
对象使用时更多的信息
*/
// C++函数对象的版本实现
template<typename T>
class mygreater
{
public:
	// 二元函数对象
	bool operator() (T a, T b) { return a > b; }
};

template<typename T>
class myless
{
public:
	// 二元函数对象
	bool operator() (T a, T b) { return a < b; }
};

template<typename T, typename Compare>
bool compare(T a, T b, Compare comp)
{
	// 通过函数指针调用函数，是没有办法内联的，效率很低，因为有函数调用开销
	return comp(a, b);
}

int main()
{
	cout << compare(10, 20, mygreater<int>()) << endl;
	cout << compare(10, 20, myless<int>()) << endl;

	return 0;
}