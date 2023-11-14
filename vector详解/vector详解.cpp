#include <iostream>
#include <vector>
using namespace std;

/*
vector容器：向量容器
底层数据结构：动态开辟的数组，每次以原来空间2倍进行扩容

vector<int> vec;
增加：
vec.push_back(20); 末尾添加元素 O(1) 导致容器扩容
vec.insert(it, 20); it迭代器指向的位置添加一个20 O(n)

删除：
vec.pop_back(); 末尾删除元素 O(1)
vec.erase(it); 删除it迭代器指向的元素

查询：
operator[] 下标随机访问vec[5] O(1)
iterator 迭代器遍历
find, for_each
foreach => 通过iterator实现

常用方法介绍：
size()
empty()
reserve() 预留空间  提前开辟空间，不会添加元素
resize() 扩容       开辟空间，并添加0
swap()

*/

int main()
{
	vector<int> vec;
	//vec.reserve(20);
	cout << vec.size() << endl;
	cout << vec.empty() << endl;

	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}

	cout << vec.size() << endl;
	cout << vec.empty() << endl;

	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	auto it2 = vec.begin();
	while (it2 != vec.end())
	{
		if (*it2 % 2 == 0)
		{
			it2 = vec.erase(it2);
		}
		else
		{
			++it2;
		}
	}

	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		if (*it1 % 2 != 0)
		{
			it1 = vec.insert(it1, *it1 - 1);
			++it1;
		}
	}

	it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	return 0;
}
