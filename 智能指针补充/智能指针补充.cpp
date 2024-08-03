#include <iostream>
#include <thread>
using namespace std;
// ����ָ�������
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

	// A���ṩ��һ����Ա����������ָ����������shared_ptr����ָ�롣
	shared_ptr<A> getSharedPtr()
	{
		/*ע�⣺����ֱ�ӷ���this���ڶ��̻߳����£������޷���֪thisָ��ָ��
		�Ķ��������״̬��ͨ��shared_ptr��weak_ptr���Խ�����̷߳��ʹ���
		������̰߳�ȫ���⣬�ο��ҵ���һƪ��������ָ��Ĳ���*/
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

	/* ��ԭ�ȵ��뷨��������������ָ��������ͬһ��A������Դ�����������ӡ����1
	���³�main����A�����������Σ������߼�������*/
	t1.join();
	t2.join();

	return 0;
}

