#include<iostream>
using namespace std;

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
	void construct(T* p, const T& val) // 负责对象构造
	{
		new (p) T(val); // 定位new
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
		cout << "vector()" << endl;
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
		if (this == &rhs) // 防止自复制
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
	void push_back(const T& val)
	{
		if (full())
			expand();
		//*_last++ = val;  _last指针指向的内存构造一个值为val的对象
		_allocator.construct(_last, val);
		_last++;
	}
	void pop_back()
	{
		if (empty())
			return;
		verify(_last - 1, _last);
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
	T& operator[] (int index)
	{
		if (index < 0 || index >= size())
		{
			throw "OutOfRangeException";
		}
		return _first[index];
	}
	class iterator
	{
	public:
		friend class vector<T, Alloc>;
		iterator(vector<T, Alloc>* pvec = nullptr
			, T* ptr = nullptr) 
			:_p(ptr), _pVec(pvec)
		{
			Iterator_Base* itb =
				new Iterator_Base(this, _pVec->_head._next);
			_pVec->_head._next = itb;
		}
		bool operator!=(const iterator& it) const
		{
			if (_pVec == nullptr || _pVec != it._pVec)
			{
				throw "iterator incompatable!";
			}
			return _p != it._p;
		}
		void operator++()
		{
			if (_pVec == nullptr)
			{
				throw "iterator invalid!";
			}
			++_p;
		}
		T& operator*() 
		{
			if (_pVec == nullptr)
			{
				throw "iterator invalid!";
			}
			return *_p;
		}
	private:
		T* _p;
		vector<T, Alloc>* _pVec;
	};

	iterator begin() { return iterator(this, _first); }
	iterator end() { return iterator(this, _last); }
	void verify(T* first, T* last)
	{
		Iterator_Base* pre = &this->_head;
		Iterator_Base* it = this->_head._next;
		while (it != nullptr)
		{
			if (it->_cur->_p >= first && it->_cur->_p <= last)
			{
				// 迭代器失效，把iterator持有的容器指针置空
				it->_cur->_pVec = nullptr;
				// 删除当前迭代器节点，继续判断后面的迭代器节点是否失效
				pre->_next = it->_next;
				delete it;
				it = pre->_next;
			}
			else
			{
				pre = it;
				it = it->_next;
			}
		}
	}
	iterator insert(iterator it, const T& val)
	{
		// 1.不考虑扩容 2.不考虑it._p的指针合法性
		verify(it._p - 1, _last);
		T* p = _last;
		while (p > it._p)
		{
			_allocator.construct(p, *(p - 1));
			_allocator.destroy(p - 1);
			p--;
		}
		_allocator.construct(p, val);
		_last++;
		return iterator(this, p);
	}
	iterator erase(iterator it)
	{
		verify(it._p - 1, _last);
		T* p = it._p;
		while (p < _last - 1)
		{
			_allocator.destroy(p);
			_allocator.construct(p, *(p + 1));
			p++;
		}
		_allocator.destroy(p);
		_last--;
		return iterator(this, it._p);
	}
private:
	T* _first;
	T* _last;
	T* _end;
	Alloc _allocator;

	// 容器迭代器失效增加代码
	struct Iterator_Base
	{
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			:_cur(c), _next(n) {}
		iterator* _cur;
		Iterator_Base* _next;
	};

	// 每个vector维护一个链表
	Iterator_Base _head;

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
	Test() { cout << "Test()" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(const Test&) { cout << "Test(const Test&)" << endl; }
};

//int main()
//{
//	int a = 1, b = 2, c = 3;
//	vector<int> v2;
//	v2.push_back(a);
//	v2.push_back(b);
//	v2.push_back(c);
//	for (int i : v2)
//		cout << i << endl;
//
//	return 0;
//}



int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; i++)
	{
		vec.push_back(rand() % 100 + 1);
	}
	for (int v : vec)
		cout << v << " ";
	cout << endl;
	auto it = vec.begin();
	/*for (; it != vec.end(); ++it)
	{
		if (*it % 2 == 0)
		{
			vec.erase(it);
		}
	}*/
	while (it != vec.end())
	{
		if (*it % 2 == 0)
		{
			it = vec.erase(it);
		}
		else
			++it;
	}
	for (int v : vec)
		cout << v << " ";

	return 0;
}
