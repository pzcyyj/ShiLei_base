#include<iostream>

using namespace std;

// 容器的空间配置器allocator做四件事情  内存开辟/内存释放  对象构造/对象析构
template<typename T>
class Allocator
{
	T* allocate(size_t size) // 负责内存开辟
	{
		return (T*)malloc(sizeof(T) * size);
	}
	void dealllocate(void* p) // 负责内存释放
	{
		free(p);
	}
	void construct(T* p, const T& val) // 负责对象构造
	{
		new (p) T(val); // 定位new
	}
	void destroy(T* p) // 负责对象析构
	{
		p->~T();
	}
};
template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	vector(int size = 10)
	{
		_first = new T[size];
		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		delete[] _first;
		_first = _end = _last = nullptr;
	}
	vector(const vector<T>& rhs)
	{
		int size = rhs._end - rhs._first;
		_first = new T[size];
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			_first[i] = rhs._first[i];
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

		delete[] _first;

		int size = rhs._end - rhs._first;
		_first = new T[size];
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			_first[i] = rhs._first[i];
		}
		_last = _first + len;
		_end = _first + size;
		return *this;
	}
	void push_back(const T& val)
	{
		if (full())
			expand();
		*_last++ = val;
	}
	void pop_back()
	{
		if (empty())
			return;
		--_last;
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
		T* ptmp = new T[2 * size];
		for (int i = 0; i < size; i++)
		{
			ptmp[i] = _first[i];
		}
		delete[] _first;
		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}
};

class Test
{
public:
	Test() { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
};

int main()
{
	vector<Test> v1(20);


	return 0;
}
