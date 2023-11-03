#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
	String str1 = "abf";
	String str2 = "abc";
	String str3 = str1 + str2;
	cout << str3 << endl;
	cout << "--------------------" << endl;

	return 0;
}