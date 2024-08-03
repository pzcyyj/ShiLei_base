#include <iostream>
#include <thread>
using namespace std;
// 智能指针测试类
class A : public enable_shared_from_this<A>
{
public:
	A() :mptr(new int)
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
		delete mptr;
		mptr = nullptr;
	}

	// A类提供了一个成员方法，返回指向自身对象的shared_ptr智能指针。
	shared_ptr<A> getSharedPtr()
	{
		/*注意：不能直接返回this，在多线程环境下，根本无法获知this指针指向
		的对象的生存状态，通过shared_ptr和weak_ptr可以解决多线程访问共享
		对象的线程安全问题，参考我的另一篇介绍智能指针的博客*/
		return shared_from_this();
	}
private:
	int* mptr;
};

void threadFunc(shared_ptr<A> a)
{
	shared_ptr<A> ptr = a->getSharedPtr();
	cout << ptr.use_count() << endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main()
{
	auto a = make_shared<A>();
	thread t1(threadFunc, a);
	thread t2(threadFunc, a);

	/* 按原先的想法，上面两个智能指针管理的是同一个A对象资源，但是这里打印都是1
	导致出main函数A对象析构两次，析构逻辑有问题*/
	t1.join();
	t2.join();

	return 0;
}

