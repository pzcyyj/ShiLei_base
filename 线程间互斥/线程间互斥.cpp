#include <iostream>
#include <thread>
#include <mutex>
#include <list>

/*
多线程程序
竞态条件：多线程执行的结果是一致的，如果不会随着cpu不同的调度顺序
，而产生不同的运行结果
*/

int ticketCount = 10; // 车站有100张车票，由3个窗口一起卖
std::mutex mtx; // 全局的一把互斥锁

void sellTicket(int index)
{
	//mtx.lock(); 为什么不能在第一次判断前加锁，这样会导致同一个线程一直占用资源不放
	while (ticketCount > 0) // 锁+双重判断
	{
		//mtx.lock(); 只剩一张票时，可能会进两个线程
		{
			std::lock_guard<std::mutex> lock(mtx); // 利用栈上对象出作用域析构的特点，保证所有线程都能释放锁，防止死锁
			if (ticketCount > 0)
			{
				std::cout << "窗口: " << index << "卖出第: " << ticketCount << "张票!" << std::endl;
				ticketCount--;
			}
		}
		//mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	//mtx.unlock();
}

int main()
{
	std::list<std::thread> tlist;
	for (int i = 1; i <= 3; ++i)
	{
		tlist.push_back(std::thread(sellTicket, i));
		//std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	for (std::thread& t : tlist)
	{
		t.join();
	}
	std::cout << "所有窗口卖票结束！" << std::endl;

	return 0;
}