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

    // 参数占位符
    bind(hello, _1)("hello bind 2!");
    cout << bind(sum, _1, _2)(200, 300) << endl;
    // 绑定器出了语句无法继续使用了

    function<void(string)> func1 = bind(hello, _1);
    func1("abc");
    func1("aaa");

    return 0;
}
#endif // 0

class Thread
{
public:
    Thread(function<void()> func) : _func(func) {}
    thread start()
    {
        thread t(_func);
        return t;
    }
private:
    function<void()> _func;
};

class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool() 
    {
        for (int i = 0; i < _pool.size(); ++i)
            delete _pool[i];
    }
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, i)));
        }
        for (int i = 0; i < size; ++i)
        {
            _handler.push_back(_pool[i]->start());
        }
        for (thread& t : _handler)
        {
            t.join();
        }
    }
private:
    vector<Thread*> _pool;
    vector<thread> _handler;
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