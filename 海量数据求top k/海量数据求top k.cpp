#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int partition(std::vector<int>& arr, int i, int j)
{
	int k = arr[i];
	while (i < j)
	{
		while (i < j && arr[j] > k)
			j--;
		if (i < j)
			arr[i++] = arr[j];

		while (i < j && arr[i] < k)
			i++;
		if (i < j)
			arr[j--] = arr[i];
	}
	arr[i] = k;
	return i;
}

int main()
{	
#if 0
	std::vector<int> vec;
	for (int i = 0; i < 10000; ++i)
	{
		vec.push_back(rand() + i);
	}

	// 定义小根堆
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	int k = 0;
	for (; k < 10; ++k)
	{
		minHeap.push(vec[k]);
	}

	for (; k < vec.size(); ++k)
	{
		if (vec[k] > minHeap.top())
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}

	while (!minHeap.empty())
	{
		std::cout << minHeap.top() << " ";
		minHeap.pop();
	}
	std::cout << std::endl;

	return 0;
#endif // 0


}