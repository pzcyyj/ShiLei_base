#include <iostream>

class CComplex
{
public:
    CComplex operator + (const CComplex& src)
    {
        /*CComplex comp;
        comp.mreal = this->mreal + src.mreal;
        comp.mimage = this->mimage + src.mimage;
        return comp;*/
        return CComplex(this->mreal + src.mreal,
            this->mimage + src.mimage);

    }
    /*CComplex(const CComplex& src)
    {
        mreal = src.mreal;
        mimage = src.mimage;
        std::cout << "CComplex(const CComplex&)" << std::endl;
    }*/
    void show()
    {
        std::cout << "real: " << mreal << " image: " << mimage << std::endl;
    }
    CComplex(int r = 0, int i = 0)
        :mreal(r), mimage(i)
    {
        std::cout << "CComplex()" << std::endl;
    }
    CComplex operator++(int)
    {
        /*CComplex comp = *this;
        mreal++;
        mimage++;
        return comp;*/
        return CComplex(mreal++, mimage++);
    }
    CComplex& operator++()
    {
        mreal++;
        mimage++;
        return *this;
    }
    void operator+=(const CComplex& src)
    {
        mreal += src.mreal;
        mimage += src.mimage;
    }
private:
    int mreal;
    int mimage;

    friend CComplex operator+(const CComplex& lhs, const CComplex& rhs);
    friend std::ostream& operator<<(std::ostream& out, const CComplex& src);
    friend std::istream& operator>>(std::istream& in, CComplex& src);
};

CComplex operator+(const CComplex& lhs, const CComplex& rhs)
{
    return CComplex(lhs.mreal + rhs.mreal, lhs.mimage + rhs.mimage);
}

std::ostream& operator<<(std::ostream& out, const CComplex& src)
{
    out << "real: " << src.mreal << " image: " << src.mimage << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, CComplex& src) // 这里不能用const，肯定是要改变src的值的
{
    in >> src.mreal >> src.mimage;
    return in;
}

int main()
{
    CComplex comp1(10, 10);
    CComplex comp2(20, 20);
    std::cout << "-----------------" << std::endl;
    CComplex comp3 = comp1 + comp2;
    comp3.show();
    std::cout << "-----------------" << std::endl;
    CComplex comp4 = comp1 + 20; // int转成复数类型，调用符合条件的构造函数即可
    comp4.show();
    std::cout << "-----------------" << std::endl;
    // 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有成员方法，
    // 就在全局作用域找合适的运算符重载函数
    CComplex comp5 = 30 + comp1;
    comp5.show();
    std::cout << "-----------------" << std::endl;
    comp5 = comp1++; // ++ -- 单目运算符  operator++()前置++ operator++(int)后置++
    comp1.show();
    comp5.show();
    comp5 = ++comp1;
    comp1.show();
    comp5.show();
    std::cout << "-----------------" << std::endl;
    comp1 += comp2;
    comp1.show();
    std::cout << "-----------------" << std::endl;
    std::cin >> comp1;
    std::cout << comp1 << std::endl;

    return 0;
}
