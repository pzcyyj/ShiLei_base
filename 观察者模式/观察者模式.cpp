#include <iostream>
#include <unordered_map>
#include <list>

class Observer
{
public:
	// 处理消息的接口
	virtual void handle(int msgid) = 0;
};

class Observer1 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			std::cout << "Observer1 recv 1 msg!" << std::endl;
			break;
		case 2:
			std::cout << "Observer1 recv 2 msg!" << std::endl;
			break;
		default:
			std::cout << "Observer1 recv unknown msg!" << std::endl;
			break;
		}
	}
};

class Observer2 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 2:
			std::cout << "Observer2 recv 2 msg!" << std::endl;
			break;
		default:
			std::cout << "Observer2 recv unknown msg!" << std::endl;
			break;
		}
	}
};

class Observer3 : public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			std::cout << "Observer3 recv 1 msg!" << std::endl;
			break;
		case 3:
			std::cout << "Observer3 recv 3 msg!" << std::endl;
			break;
		default:
			std::cout << "Observer3 recv unknown msg!" << std::endl;
			break;
		}
	}
};

class Subject
{
public:
	// 给主题增加观察者对象
	void addObserver(Observer* obser, int msgid)
	{
		_subMap[msgid].push_back(obser);
		/*auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			it->second.push_back(obser);
		}
		else
		{
			std::list<Observer*> lis;
			lis.push_back(obser);
			_subMap.insert({ msgid, lis });
		}*/
	}
	// 主题检测发生改变，通知相应的观察者对象处理事件
	void dispatch(int msgid)
	{
		auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			for (Observer* p : it->second)
			{
				p->handle(msgid);
			}
		}
		else
		{
			std::cout << "no observer" << std::endl;
		}
	}
private:
	std::unordered_map<int, std::list<Observer*>> _subMap;
};

int main()
{
	Subject subject;
	Observer* p1 = new Observer1();
	Observer* p2 = new Observer2();
	Observer* p3 = new Observer3();
	subject.addObserver(p1, 1);
	subject.addObserver(p1, 2);
	subject.addObserver(p2, 2);
	subject.addObserver(p3, 1);
	subject.addObserver(p3, 3);
	subject.dispatch(1);
	subject.dispatch(5);


	return 0;
}