using namespace std;
#include <iostream>
static const int POOL_ITEM_SIZE = 1000000;
template<typename T>
class Queue
{
public:
	Queue()
	{
		_front = _rear = new QueueItem();
	}
	~Queue()
	{
		QueueItem* cur = _front;
		while (cur != nullptr)
		{
			_front = _front->_next;
			delete cur;
			cur = _front;
		}
	}
	void push(const T& val)
	{
		QueueItem* item = new QueueItem(val);
		_rear->_next = item;
		_rear = item;
	}
	void pop()
	{
		if (empty())
			return;
		QueueItem* first = _front->_next;
		_front->_next = first->_next;
		if (_front->_next == nullptr)
		{
			_rear = _front;
		}
		delete first;
	}
	T front() const
	{
		return _front->_next->_data;
	}
	bool empty() const { return _front == _rear; }
private:
	struct QueueItem
	{
		QueueItem(T data = T()) :_data(data), _next(nullptr) {}
		void* operator new(size_t size)
		{
			if (_itemPool == nullptr)
			{
				_itemPool = (QueueItem*)new char[POOL_ITEM_SIZE * sizeof(QueueItem)];
				QueueItem* p = _itemPool;
				for ( ; p < _itemPool + POOL_ITEM_SIZE - 1; ++p)
				{
					p->_next = p + 1;
				}
				p->_next = nullptr;
			}
			QueueItem* p = _itemPool;
			_itemPool = _itemPool->_next;
			return p;
		}
		void operator delete(void* ptr)
		{
			QueueItem* p = (QueueItem*)ptr;
			p->_next = _itemPool;
			_itemPool = p;
		}
		T _data;
		QueueItem* _next;
		static QueueItem* _itemPool;
		
	};
	QueueItem* _front;
	QueueItem* _rear;
};

template<typename T>
typename Queue<T>::QueueItem* Queue<T>::QueueItem::_itemPool = nullptr;

int main()
{
	Queue<int> que;
	for (int i = 0; i < 1000000; ++i)
	{
		que.push(i);
		que.pop();
	}
	cout << que.empty() << endl;
	return 0;
}
