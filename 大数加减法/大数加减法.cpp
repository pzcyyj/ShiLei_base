#include <algorithm>
#include <iostream>
#include <string>

class BigInt
{
public:
	BigInt(std::string str) : strDight(str) {}
private:
	std::string strDight;
	friend std::ostream& operator<<(std::ostream& out, const BigInt& src);
	friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
	friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
};

std::ostream& operator<<(std::ostream& out, const BigInt& src)
{
	out << src.strDight;
	return out;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs)
{
	/*
	遍历字符串l，r，从后往前遍历
	同位置的数字相加，进位flag存入一个结果当中string result
	同时完成
	某个字符串先完成 都要考虑进位
	*/
	std::string result;
	bool flag = false;
	int size1 = lhs.strDight.length() - 1;
	int size2 = rhs.strDight.length() - 1;
	int i = size1, j = size2;

	for (; i >= 0 && j >= 0; --i, --j)
	{
		int ret = lhs.strDight[i] - '0' + rhs.strDight[j] - '0';
		if (flag)
		{
			ret += 1;
			flag = false;
		}

		if (ret >= 10)
		{
			ret %= 10;
			flag = true;
		}

		result.push_back(ret + '0');
	}

	if (i >= 0)
	{
		while (i >= 0)
		{
			int ret = lhs.strDight[i] - '0';
			if (flag)
			{
				ret += 1;
				flag = false;
			}

			if (ret >= 10)
			{
				ret %= 10;
				flag = true;
			}
			result.push_back(ret + '0');
			i--;
		}
	}
	else if (j >= 0)
	{
		while (j >= 0)
		{
			int ret = rhs.strDight[j] - '0';
			if (flag)
			{
				ret += 1;
				flag = false;
			}

			if (ret >= 10)
			{
				ret %= 10;
				flag = true;
			}
			result.push_back(ret + '0');
			j--;
		}
	}
	if (flag)
		result.push_back('1');

	std::reverse(result.begin(), result.end());
	return result;
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs)
{
	std::string result;
	bool flag = false;
	bool minor = false;

	std::string maxStr = lhs.strDight;
	std::string minStr = rhs.strDight;

	if (maxStr.length() < minStr.length())
	{
		maxStr = rhs.strDight;
		minStr = lhs.strDight;
		minor = true;
	}
	else if (maxStr.length() == minStr.length())
	{
		if (maxStr < minStr)
		{
			maxStr = rhs.strDight;
			minStr = lhs.strDight;
			minor = true;
		}
		else if (maxStr == minStr)
			return std::string("0");
	}

	int size1 = maxStr.length() - 1;
	int size2 = minStr.length() - 1;
	int i = size1, j = size2;

	for (; i >= 0 && j >= 0; --i, --j)
	{
		int ret = maxStr[i] - minStr[j];
		if (flag)
		{
			ret -= 1;
			flag = false;
		}

		if (ret < 0)
		{
			ret += 10;
			flag = true;
		}
		result.push_back(ret + '0');
	}
	
	while (i >= 0)
	{
		int ret = maxStr[i] - '0';
		if (flag)
		{
			ret -= 1;
			flag = false;
		}

		if (ret < 0)
		{
			ret += 10;
			flag = true;
		}
		result.push_back(ret + '0');
		i--;
	}
	while (*(result.rbegin()) == '0')
		result.pop_back();
	if (minor)
		result.push_back('-');
	std::reverse(result.begin(), result.end());

	return result;
}

int main()
{
	BigInt int1("123");
	BigInt int2("99");

	std::cout << int1 + int2 << std::endl;

	std::cout << int1 - int2 << std::endl;
}