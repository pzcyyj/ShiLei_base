#include <iostream>
#include <functional>
using namespace std;

#if 0
template<typename T>
bool compare(T a, T b)
{
    cout << "template compare" << endl;
    return a > b;
}
template<>
bool compare<const char*>(const char* a, const  char* b)
{
    cout << "compare<const char*>" << endl;
    return strcmp(a, b) > 0;
}

int main()
{
    compare(10, 20);
    compare("aaa", "bbb");

    return 0;
}
#endif // 0

#if 0
template<typename T>
class Vector
{
public:
    Vector() 
    {
        cout << "call Vector template init" << endl;
    }
};

// 下面是对char*类型提供的完全特例化版本
template<>
class Vector<char*>
{
public:
    Vector()
    {
        cout << "call Vector<char*> init" << endl;
    }
};

// 下面是对指针类型提供的部分特例化版本
template<typename Ty>
class Vector<Ty*>
{
public:
    Vector()
    {
        cout << "call Vector<Ty*> init" << endl;
    }
};

// 针对函数指针（有返回值，有两个形参变量）部分特例化
template<typename R, typename A1, typename A2>
class Vector<R(*) (A1, A2)>
{
public:
    Vector()
    {
        cout << "call Vector<R(*) (A1, A2) init" << endl;
    }
};

// 针对函数类型（有一个返回值，两个形参变量）部分特例化
template<typename R, typename A1, typename A2>
class Vector<R(A1, A2)>
{
public:
    Vector()
    {
        cout << "call Vector<R(A1, A2) init" << endl;
    }
};

int sum(int a, int b) { return a + b; }

int main()
{
    Vector<int> vec1;
    Vector<char*> vec2;
    Vector<int*> vec3;
    Vector<int(*) (int, int)> vec4;
    Vector<int(int, int)> vec5;

    // 区分函数指针类型和函数类型
    using pfunc1 = int(*)(int, int);
    pfunc1 p1 = sum;
    cout << p1(1, 2) << endl;

    typedef int pfunc2(int, int);
    pfunc2* p2 = sum;
    cout << p2(1, 2) << endl;

    return 0;
}
#endif

template<typename T>
void func(T a)
{
    cout << typeid(T).name() << endl;
}

int sum(int a, int b) { return a + b; }

template<typename R, typename A1, typename A2>
void func2(R(*a)(A1, A2))
{
    cout << typeid(R).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
    cout << a(1, 2) << endl;
}

class Test
{
public:
    int sum(int a, int b) { return a + b; }
};

template<typename R, typename T, typename A1, typename A2>
void func3(T* instance, R(T::*a)(A1, A2))
{
    cout << typeid(R).name() << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(A1).name() << endl;
    cout << typeid(A2).name() << endl;
    cout << (instance->*a)(1, 2) << endl;
}

int main()
{
    func(10);
    func("aaa");
    
    Test t;
    func2(sum); // int (*)(int,int)  如果T* ，int (int,int)
    func3(&t, &Test::sum); // int (__thiscall Test::*)(int,int)
    
    return 0;
}