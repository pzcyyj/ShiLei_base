#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <queue>

# if 0
int main()
{
	map<int, function<int(int, int)>> caculateMap;
	caculateMap[1] = [](int a, int b)->int {return a + b; };
	caculateMap[2] = [](int a, int b)->int {return a - b; };
	caculateMap[3] = [](int a, int b)->int {return a * b; };
	caculateMap[4] = [](int a, int b)->int {return a / b; };

	cout << "选择:";
	int choice;
	cin >> choice;
	cout << "10 + 15 = " << caculateMap[choice](10, 15) << endl;


	return 0;
}
#endif

class Data
{
public:
	Data(int val1 = 10, int val2 = 10) : ma(val1), mb(val2) {}
	/*bool operator>(const Data& data) const { return ma > data.ma; }
	bool operator<(const Data& data) const { return ma < data.ma; }*/
	int mb;
	int ma;
};

int main()
{
	/*unique_ptr<FILE, function<void(FILE*)>> ptr1(fopen("data.txt", "w"), [](FILE* pf) {fclose(pf); });*/
	using FUNC = function<bool(Data&, Data&)>;
	priority_queue<Data, vector<Data>, FUNC> maxHeap([](Data& d1, Data& d2)->bool
		{
			return d1.ma > d2.ma;
		});
	maxHeap.push(Data(10, 20));
	maxHeap.push(Data(15, 15));
	maxHeap.push(Data(20, 15));

	cout << maxHeap.top().ma << endl;
	maxHeap.pop();
	cout << maxHeap.top().ma << endl;

	return 0;
}