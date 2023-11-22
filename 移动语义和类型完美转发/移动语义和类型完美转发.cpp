#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class CMyString
{
public:
	CMyString(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			mptr = new char[strlen(p) + 1];
			strcpy(mptr, p);
		}
		else
		{
			mptr = new char[1];
			*mptr = '\0';
		}
		cout << "CMyString()" << endl;
	}
	~CMyString()
	{
		delete[] mptr;
		mptr = nullptr;
		cout << "~CMyString()" << endl;
	}

	CMyString(const CMyString& str)
	{
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
		cout << "CMyString(const CMyString&)" << endl;
	}

	CMyString(CMyString&& str)
	{
		mptr = str.mptr;
		str.mptr = nullptr;
		cout << "CMyString(CMyString&&)" << endl;
	}

	CMyString& operator=(CMyString&& str)
	{
		cout << "String& operator=(String&&)" << endl;
		if (this == &str)
			return *this;

		delete[] mptr;

		mptr = str.mptr;
		str.mptr = nullptr;

		return *this;
	}
	const char* c_str() const { return mptr; }

private:
	char* mptr;
	friend CMyString operator+(const CMyString& lhs,
		const CMyString& rhs);
	friend ostream& operator<<(ostream& out, const CMyString& str);
};

CMyString GetString(CMyString& str)
{
	const char* pstr = str.c_str();
	CMyString tmpStr(pstr);
	cout << "--------------------" << endl;
	return tmpStr;
}

CMyString operator+(const CMyString& lhs,
	const CMyString& rhs)
{
	cout << "--------------------" << endl;
	// char* ptmp = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
	CMyString tmpStr;
	tmpStr.mptr = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
	strcpy(tmpStr.mptr, lhs.mptr);
	strcat(tmpStr.mptr, rhs.mptr);


	return tmpStr;
}

ostream& operator<<(ostream& out, const CMyString& str)
{
	out << str.mptr;
	return out;
}

// 容器的空间配置器allocator做四件事情  内存开辟/内存释放  对象构造/对象析构
template<typename T>
struct Allocator
{
	T* allocate(size_t size) // 负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p) // 负责内存释放
	{
		free(p);
	}

	//void construct(T* p, const T& val) // 负责对象构造
	//{
	//	new (p) T(val); // 定位new
	//}
	//void construct(T* p, T&& val) // 负责对象构造
	//{
	//	new (p) T(std::move(val)); // 定位new
	//}

	template<typename Ty>
	void construct(T* p, Ty&& val)
	{
		new (p) T(std::forward<Ty>(val));
	}

	void destroy(T* p) // 负责对象析构
	{
		p->~T();
	}
};

/*
容器底层内存开辟，内存释放，对象构造和析构，都通过allocator空间配置器来实现
*/
template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	vector(int size = 10)
	{
		// 需要把内存开辟和对象构造分开处理
		// _first = new T[size];
		_first = _allocator.allocate(size);
		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		// 析构容器有效的元素，然后释放_first指针指向的堆内存
		// delete[] _first;
		for (T* p = _first; p != _last; ++p) // 把有效的对象析构从_first到_last
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first); // 释放内存
		_first = _end = _last = nullptr;
	}
	vector(const vector<T>& rhs)
	{
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator = (const vector<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		//delete[] _first;
		for (T* p = _first; p != _last; ++p) // 把有效的对象析构从_first到_last
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
		return *this;
	}
	//void push_back(const T& val)
	//{
	//	if (full())
	//		expand();
	//	//*_last++ = val;  _last指针指向的内存构造一个值为val的对象
	//	_allocator.construct(_last, val);
	//	_last++;
	//}
	//void push_back(T&& val)
	//{
	//	if (full())
	//		expand();
	//	_allocator.construct(_last, std::move(val));
	//	_last++;
	//}
	template<typename Ty> // 函数模板的类型推演+引用折叠
	void push_back(Ty&& val) // 引用折叠，& + && = &, && + && = &&
	{
		if (full())
			expand();

		// move:移动语义，得到右值类型
		// forward:类型完美转发，能够识别左值和右值类型
		_allocator.construct(_last, std::forward<Ty>(val));
		_last++;
	}
	void pop_back()
	{
		if (empty())
			return;
		//--_last;   不仅要把_last指针--，还需要析构删除的元素
		--_last;
		_allocator.destroy(_last);
	}
	T back() const
	{
		return *(_last - 1);
	}
	bool full() const { return _last == _end; }
	bool empty() const { return _first == _last; }
	int size() const { return _last - _first; }
private:
	T* _first;
	T* _last;
	T* _end;
	Alloc _allocator;
	void expand()
	{
		int size = _end - _first;
		//T* ptmp = new T[2 * size];
		T* ptmp = _allocator.allocate(2 * size);
		for (int i = 0; i < size; i++)
		{
			_allocator.construct(ptmp + i, _first[i]);
			//ptmp[i] = _first[i];
		}
		//delete[] _first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);
		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}
};

class Test
{
public:
	Test(int a = 10) : ma(a) { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test& t)
	{
		ma = t.ma;
		cout << "Test(const Test& t)" << endl;
	}
public:
	int ma;
};

int main()
{
	CMyString str1 = "aaa";
	vector<CMyString> vec;

	cout << "------------------" << endl;
	vec.push_back(str1);
	vec.push_back(CMyString("bbbb"));
	cout << "------------------" << endl;

    return 0;
}
