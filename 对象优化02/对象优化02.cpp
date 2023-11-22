﻿#include <iostream>
using namespace std;

class Test
{
public:
    Test(int data = 10) : ma(data) { cout << "Test(" << ma << ")" << endl; }
    ~Test() { cout << "~Test(" << ma << ")" << endl; }
    Test(const Test& t) : ma(t.ma) { cout << "Test(const Test& t)" << endl; }
    void operator = (const Test& t) 
    {
        cout << "operator =" << endl;
        ma = t.ma;
    }
    int getData() const { return ma; }
private:
    int ma;
};

Test GetObject(Test &t) // 不能返回局部的或者临时的对象的指针或引用
{
    cout << "-----------" << endl;
    int val = t.getData();
    cout << "------------" << endl;
    Test tmp(val);
    return tmp;
    // vs2017上会有一步拷贝构造产生临时对象，因为tmp函数运行结束就会析构，
    // 只能通过临时对象传出去，但是vs22并未调用拷贝构造
}

int main()
{
    Test t1;
    //Test t2;
    cout << "-------------" << endl;
    Test t2 = GetObject(t1);

    return 0;
}