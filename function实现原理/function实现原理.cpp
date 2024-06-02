#include <iostream>
#include <functional>
using namespace std;

template<typename Fty>
class myfunction {};

#if 0
template<typename R, typename A1>
class myfunction<R(A1)>
{
public:
	using PFUNC = R(*)(A1);
	myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
	R operator() (A1 arg)
	{
		return _pfunc(arg);
	}
private:
	PFUNC _pfunc;

};

template<typename R, typename A1, typename A2>
class myfunction<R(A1, A2)>
{
public:
	typedef R(*PFUNC)(A1, A2);
	myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
	R operator() (A1 arg1, A2 arg2)
	{
		return _pfunc(arg1, arg2);
	}
private:
	PFUNC _pfunc;
};
#endif

template<typename R, typename... A>
class myfunction<R(A...)>
{
public:
	using PFUNC = R(*)(A...);
	myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
	R operator() (A... arg)
	{
		return _pfunc(arg...);
	}
private:
	PFUNC _pfunc;
};

class Sum
{
public:
	int operator() (int a, int b)
	{
		return a + b;
	}
};

void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
void sum3(int a, int b, int c) { cout << a << b << c << endl; }

int main()
{
	myfunction<void(string)> func1 = hello;
	func1("hello world!");
	function<int(int, int)> func2 = sum;
	cout << func2(10, 20) << endl;
	myfunction<void(int, int, int)> func3 = sum3;
	
	func3(1, 2, 3);

	return 0;
}