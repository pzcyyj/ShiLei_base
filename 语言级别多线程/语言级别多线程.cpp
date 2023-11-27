#include <iostream>
#include <thread>
using std::cout;
using std::endl;

/*
C++语言级别的多线程  =》 代码可以跨平台
线程内容：
一 怎么创建启动一个线程
std::thread定义一个线程对象，传入线程所需要的线程函数和参数，
线程自动开启

二 子线程如何结束
子线程函数运行完成，线程就结束了

三 主线程如何处理子线程
t.join() : 等待t线程结束，当前线程继续往下运行
t.detach() : 把t线程设为分离线程，主线程结束，整个进程结束，
                所有子线程都自动结束！
*/

void threadHandler1(int time)
{
    std::this_thread::sleep_for(std::chrono::seconds(time));
    cout << "hello thread1" << endl;
}

int main()
{
    // 创建线程对象，传入线程函数，新线程开始运行
    std::thread t1(threadHandler1, 2);
    cout << "--------------" << endl;
    // 主线程等待调用join的线程完成线程函数结束，再继续往下运行
    t1.join();
    // 把子线程设置为分离线程
    /*t1.detach();*/
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "main thread done!" << endl;

    // 主线程运行完成，查看如果当前进程还有未运行完成的子线程
    // 进程就会异常终止
    return 0;
}
