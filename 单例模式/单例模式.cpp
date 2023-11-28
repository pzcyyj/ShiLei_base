#include <iostream>


// 懒汉单例 线程不安全
class Singleton
{
public:
    static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }
private:
    static Singleton* instance; // #2 定义一个唯一的类的实例对象
    Singleton() // #1 构造函数私有化
    {
        std::cout << "Singleton()" << std::endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::instance = nullptr;

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