#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <ctime>
using namespace std;

// 输出容器内所有值
template<typename Container>
void showContainer(Container& con)
{
    // 加上typename告知编译器后面的Container::iterator是一个类型
    typename Container::iterator it = con.begin();
    for (; it != con.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp)
{
    for (; first != last; ++first)
    {
        if (comp(*first))
        {
            return first;
        }
    }
    return last;
}

template<typename Compare, typename T>
class _mybind1st
{
public:
    _mybind1st(Compare comp, T val)
        : _comp(comp), _val(val) {}
    bool operator() (const T& second)
    {
        return _comp(_val, second);
    }
private:
    Compare _comp;
    T _val;
};

template<typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T& val)
{
    return _mybind1st<Compare, T>(comp, val);
}

int main()
{
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 20; ++i)
    {
        vec.push_back(rand() % 100 + 1);
    }
    showContainer(vec);
    sort(vec.begin(), vec.end());
    showContainer(vec);
    sort(vec.begin(), vec.end(), greater<int>());
    showContainer(vec);
    /*
    把70按顺序插入到vec容器中，即找第一个小于70的数
    需要一个一元函数对象 operator() (const T& val)
    绑定器 + 二元函数对象 =》 一元函数对象
    bind1st: + greater bool operator() (70, const _Ty& _Right)
    bind2nd: + less bool operator() (const _Ty& _Left, 70)
    */
    auto it1 = my_find_if(vec.begin(), vec.end(), 
        bind1st(greater<int>(), 70));
    /*auto it1 = my_find_if(vec.begin(), vec.end(),
        bind2nd(less<int>(), 70));*/
    if (it1 != vec.end())
    {
        vec.insert(it1, 70);
    }
    showContainer(vec);

    return 0;
}