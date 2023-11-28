#include <iostream>
#include <list>
#include <thread>
#include <atomic> // 包含了很多原子类型

volatile std::atomic_bool isReady = false;
volatile std::atomic_int count = 0; // volatile 防止多线程程序对共享变量缓存

void task()
{
    while (!isReady)
    {
        std::this_thread::yield(); // 线程出让当前的cpu时间片，等待下一次调度
    }

    for (int i = 0; i < 100; ++i)
    {
        count++;
    }
}

int main()
{
    std::list<std::thread> tlist;
    for (int i = 0; i < 10; ++i)
    {
        tlist.push_back(std::thread(task));
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    isReady = true;

    for (std::thread& t : tlist)
    {
        t.join();
    }
    std::cout << "count: " << count << std::endl;

    return 0;
}
