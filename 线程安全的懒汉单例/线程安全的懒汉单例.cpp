#include <iostream>
#include <mutex>


#if 0
std::mutex mtx;

class Singleton
{
public:
    static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
    {
        // std::lock_guard<std::mutex> guard(mtx); // 锁的粒度太大了
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> guard(mtx);
            if (instance == nullptr) // 锁+双重判断
            {
                /*
                开辟内存
                构造对象
                instance赋值
                */
                instance = new Singleton();
            }
        }
        return instance;
    }
private:
    static Singleton* volatile instance; // #2 定义一个唯一的类的实例对象
    Singleton() // #1 构造函数私有化
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton* volatile Singleton::instance = nullptr;

int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    return 0;
}
#endif // 0

std::mutex mtx;

class Singleton
{
public:
    static Singleton* getInstance()
    {
        // g++ -o run xxx.cpp -g gdb run
        // 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了
        static Singleton instance; // 第一次运行到该对象时，进行初始化
        return &instance;
    }
private:
    Singleton()
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};


int main()
{
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    Singleton* p3 = Singleton::getInstance();
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;

    return 0;
}