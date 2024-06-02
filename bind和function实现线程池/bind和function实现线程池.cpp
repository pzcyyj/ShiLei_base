#include <iostream>
#include <functional>
#include <vector>
#include <thread>
using namespace std;
using namespace placeholders;

#if 0
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
class Test
{
public:
    int sum(int a, int b) { return a + b; }
};
int main()
{
    bind(hello, "hello bind!")();
    cout << bind(sum, 10, 10)() << endl;
    cout << bind(&Test::sum, Test(), 20, 30)() << endl;
    function<int(Test, int)> func3 = bind(&Test::sum, placeholders::_1, 20, placeholders::_2);
    cout << func3(Test(), 18) << endl;

    // 参数占位符
    bind(hello, _1)("hello bind 2!");
    cout << bind(sum, placeholders::_1, _2)(200, 300) << endl;
    // 绑定器出了语句无法继续使用了，因此借助function来复用
    function<int(int, int)> func4 = bind(sum, placeholders::_1, _2);

    function<void(string)> func1 = bind(hello, _1);
    func1("abc");
    func1("aaa");

    return 0;
}
#endif

class Thread
{
public:
    using Func = function<void(int)>;
    Thread(Func func, int no) : _func(func), _no(no) {}
    thread start()
    {
        thread t(_func, _no);
        return t;
    }
private:
    Func _func;
    int _no;
};

class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool()
    {
        // 释放Thread对象占用的堆资源
        for (unsigned int i = 0; i < _pool.size(); ++i)
            delete _pool[i];
    }
    // 开启线程池
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, _1), i));
        }
        for (int i = 0; i < size; ++i)
        {
            _handler.push_back(_pool[i]->start());
        }
        for (thread& t : _handler){ t.join(); }
    }
private:
    vector<Thread*> _pool;
    vector<thread> _handler;
    // 线程函数
    void runInThread(int id)
    {
        cout << "call runInThread! id:" << id << endl;
    }
};

int main()
{
    ThreadPool pool;
    pool.startPool(10);

    return 0;
}