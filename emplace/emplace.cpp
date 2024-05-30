#include <iostream>
//#include <vector>
using namespace std;

class Test
{
public:
	Test(int a) { cout << "Test(int)" << endl; }
	~Test() { cout << "~Test()" << endl; }
	Test(int a, int b) { cout << "Test(int, int)" << endl; }
	Test(const Test&) { cout << "Test(const Test&)" << endl; }
	Test(Test&&) { cout << "Test(Test &&)" << endl; }
};

template<typename T>
struct MyAllocator
{
	T* allocate(size_t size)
	{
		return (T*)malloc(size * sizeof(T));
	}
	template<typename... Types>
	void construct(T* ptr, Types&&... args)
	{
		// args 是一个参数，而且是个Test对象，那么调用拷贝构造
		// args 是多个参数，那么调用构造函数
		new (ptr) T(forward<Types>(args)...);
	}
};

template<typename T, typename Alloc = MyAllocator<T>>
class vector
{
public:
	vector()
		: vec_(nullptr)
		, size_(0)
		, idx_(0)
	{}
public:
	void reserve(size_t size)
	{
		vec_ = allocator_.allocate(size);
		size_ = size;
	}
	/*void push_back(const T& val)
	{
		allocator_.construct(vec_ + idx_, val);
		idx_++;
	}
	void push_back(T&& val)
	{
		allocator_.construct(vec_ + idx_, move(val));
		idx_++;
	}*/
	template<typename Ty>
	void push_back(Ty&& val)
	{
		allocator_.construct(vec_ + idx_, forward<Ty>(val));
		idx_++;
	}
	template<typename... Types>
	void emplace_back(Types&&... args)
	{
		allocator_.construct(vec_ + idx_, forward<Types>(args)...);
		idx_++;
	}
private:
	T* vec_;
	int size_;
	int idx_;
	Alloc allocator_;
};

int main()
{
	Test t1(10);
	vector<Test> vec;
	vec.reserve(100);

	cout << "-----------------" << endl;

	vec.push_back(t1);
	vec.emplace_back(t1);
	
	cout << "----------------" << endl;

	vec.push_back(Test(20));
	vec.emplace_back(Test(20));

	cout << "----------------" << endl;

	vec.push_back(20);
	vec.emplace_back(39, 40);

	cout << "----------------" << endl;
}