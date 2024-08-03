#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue> // C++ stl所有的容器都不是线程安全的

/*
多线程编程两个问题：
1.线程间互斥
竞态条件 =》 临界区代码段 =》 保证原子操作 =》互斥锁mutex 轻量级的的无锁实现CAS
2.线程间的同步通信
*/

std::mutex mtx;
std::condition_variable cv;

class Queue
{
public:
	void put(int val, int index)
	{
		std::unique_lock<std::mutex> lck(mtx);
		while (!que.empty()) // 不能用if，有可能是假唤醒
		{
			// que不为空，生产者应该通知消费者去消费，消费完了再继续生产
			// 生产者线程应该进入等待状态，并且把mtx互斥锁释放掉
			cv.wait(lck);
		}
		que.push(val);
		cv.notify_all();
		std::cout << "生产者" << index << "生产：" << val << "号物品" << std::endl;
	}
	int get(int index)
	{
		std::unique_lock<std::mutex> lck(mtx);
		while (que.empty())
		{
			std::cout << index << " get wait..." << std::endl;
			cv.wait(lck);
		}
		int val = que.front();
		que.pop();
		cv.notify_all();
		std::cout << "消费者" << index << "消费：" << val << "号物品" << std::endl;
		return val;
	}
private:
	std::queue<int> que;
};

void producer(Queue* que, int index)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->put(i, index);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer(Queue* que, int index)
{
	for (int i = 1; i <= 10; ++i)
	{
		que->get(index);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	Queue que;

	std::thread t1(producer, &que, 1);
	std::thread t2(consumer, &que, 1);
	//std::thread t3(consumer, &que, 2);

	t1.join();
	t2.join();
	//t3.join();

	return 0;
}