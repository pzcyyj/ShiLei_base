#include <iostream>
#include <unordered_map>

int main()
{
	/*
	a,b两个文件，里面都有10亿个整数，内存限制400M，让你求出a，b两个文件当中重复的元素有哪些？
	10亿 -》 全部读取内存中，1G*4*2=8G/400M = 27个小文件
	a =》 全部读到内存当中，存储到哈希表
	b =》 从b文件读数据，在内存哈希表中查询

	把a和b两个大文件，划分成个数相等的一系列（27）小文件（分治思想）
	从a文件中读取数据，通过 数据%27=file_index
	从b文件中读取数据，通过 数据%27=file_index

	a和b两个文件中，数据相同的元素，进行哈希映射以后肯定在相同序号的小文件当中
	
	*/

	/* 
	#2 有一个文件，有大量的整数 50亿个整数，内存限制400M，让你找出文件中重复的元素，重复次数
	哈希表：50亿=5G*4=20G, 20G*2=40G内存
	分治法的思想：大文件划分成小文件，使得每一个小文件能够加载到内存当中，求出对应的重复元素
	大文件 =》 小文件的个数（40G / 400M = 120个小文件）
	data0.txt
	data1.txt
	data2.txt
	...
	data126.txt
	遍历大文件的元素，把每一个元素根据哈希映射函数，放到对应序号的小文件当中
	data % 127 = file_index
	值相同的，通过一样的哈希映射函数，肯定是放在同一个小文件当中的
	*/


#if 0 // #1 考察基本的数据查重思想
	const int SIZE = 10000;
	int ar[SIZE] = { 0 };
	for (int i = 0; i < SIZE; ++i)
	{
		ar[i] = rand();
	}

	std::unordered_map<int, int> map;
	for (int val : ar)
	{
		map[val]++;
	}

	for (auto pair : map)
	{
		if (pair.second > 1)
		{
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
#endif // 0
	return 0;
}