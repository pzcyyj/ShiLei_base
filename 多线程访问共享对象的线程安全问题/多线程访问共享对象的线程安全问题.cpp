#include <iostream>
#include <memory>
#include <thread>
using namespace std;

class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void testA() { cout << "很好的方法" << endl; }
};

void handler01(shared_ptr<A> pw)
{
	//std::this_thread::sleep_for(std::chrono::seconds(20));
	// q访问a对象时，需要侦测一下A对象是否存活
	/*shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->testA();
	}
	else
		cout << "A对象已经析构，不能再访问" << endl;*/
	if (pw != nullptr)
	{
		pw->testA();
	}
	else
		cout << "A对象已经析构，不能再访问" << endl;
}

int main()
{
	{
		shared_ptr<A> p(new A());

		thread t1(handler01, p);

		t1.detach();

		p->testA();

		std::this_thread::sleep_for(std::chrono::seconds(20));
	}

	

	return 0;
}
