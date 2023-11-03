#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class String
{
public:
	String(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			_pstr = new char[strlen(p) + 1];
			strcpy(_pstr, p);
		}
		else
		{
			_pstr = new char[1];
			*_pstr = '\0';
		}
		cout << "String()" << endl;
	}
	~String()
	{
		delete[] _pstr;
		_pstr = nullptr;
		cout << "~String()" << endl;
	}
	String(const String& str)
	{
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		cout << "String(const String&)" << endl;
	}
	String& operator=(const String& str)
	{
		if (this == &str)
			return *this;
		delete[] _pstr;
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		cout << "String& operator=(const String&)" << endl;
		return *this;
	}
	bool operator>(const String& str) const
	{
		return strcmp(_pstr, str._pstr) > 0;
	}
	bool operator<(const String& str) const
	{
		return strcmp(_pstr, str._pstr) < 0;
	}
	bool operator==(const String& str) const
	{
		return strcmp(_pstr, str._pstr) == 0;
	}
	int length() const { return strlen(_pstr); }
	char& operator[](int index) { return _pstr[index]; };
	const char& operator[](int index) const { return _pstr[index]; }
	const char* c_str() const { return _pstr; }
	class iterator
	{
	public:
		iterator(char* p = nullptr) :_p(p) {}
		bool operator!=(const iterator& it)
		{
			return _p != it._p;
		}
		void operator++()
		{
			++_p;
		}
		char& operator*() { return *_p; }
	private:
		char* _p;
	};
	// 首元素迭代器表示
	iterator begin() { return iterator(_pstr); }
	// 末尾元素迭代器表示
	iterator end() { return iterator(_pstr + length()); }
private:
	char* _pstr;
	friend ostream& operator<<(ostream& out, const String& str);
	friend String operator+(const String& lhs, const String& rhs);
};

String operator+(const String& lhs, const String& rhs)
{
	//char* ptmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	String tmp;
	tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
	strcpy(tmp._pstr, lhs._pstr);
	strcat(tmp._pstr, rhs._pstr);
	// delete[] ptmp;
	return tmp;
	//return String(ptmp); 会造成内存泄漏，没有释放ptmp占用的空间
}
ostream& operator<<(ostream& out, const String& str)
{
	out << str._pstr;
	return out;
}

int main()
{
	// 迭代器的功能：提供一种统一的方式，来透明的遍历容器
	String str1 = "hello world!";
	String::iterator it = str1.begin();
	for (; it != str1.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	for (char ch : str1)
		cout << ch << " ";
	cout << endl;

	return 0;
}