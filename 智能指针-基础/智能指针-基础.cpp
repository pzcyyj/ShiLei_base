#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class RefCnt
{
public:
	RefCnt(T* ptr = nullptr) : mptr(ptr)
	{
		if (mptr != nullptr)
			mcount = 1;
	}
	void addRef() { mcount++; }
	int delRef() { return --mcount; }
private:
	T* mptr;
	int mcount;
};

/*
带引用计数的智能指针
:多个智能指针可以管理同一个资源
:给每个对象资源，匹配一个引用计数
智能指针 =》 资源的时候 =》 引用计数+1
智能指针 =》 不再使用资源的时候 =》 引用计数-1 =》 !=0  为0资源释放了
*/
template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr)
		: mptr(ptr)
	{
		mpRefCnt = new RefCnt<T>(mptr);
	}
	~CSmartPtr() 
	{
		if (mpRefCnt->delRef() == 0)
		{
			delete mptr;
			mptr = nullptr;
		}
		
	}
	T& operator*() { return *mptr; }
	T* operator->() { return mptr; }
	CSmartPtr(const CSmartPtr<T>& src)
		: mptr(src.mptr), mpRefCnt(src.mpRefCnt)
	{
		if (mptr != nullptr)
			mpRefCnt->addRef();
	}
	CSmartPtr<T>& operator=(const CSmartPtr<T>& src)
	{
		if (this == &src)
			return *this;

		if (mpRefCnt->delRef() == 0)
		{
			delete mptr;
		}
		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;
	}
private:
	T* mptr; // 指向资源的指针
	RefCnt<T>* mpRefCnt; // 指向该资源引用计数对象的指针
};

int main()
{
	CSmartPtr<int> ptr1(new int);
	CSmartPtr<int> ptr2(ptr1);
	CSmartPtr<int> ptr3(new int);
	ptr3 = ptr2;
	*ptr2 = 20;
	*ptr3 = 50;

	cout << *ptr1 << endl;
	
	return 0;
}