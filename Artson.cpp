#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#define INF 10000
using namespace std;
bool match(string a, string b){
	list<char> pattern;
	int size = 0;
	if (b.empty() && a.empty()) // 如果两个字符串已空, 说明可匹配
	{
		return true;
	}
	else if (!b.empty() && a.empty()) // 待匹配字符串未空, 模式字符串已空, 不可匹配
	{
		return false;
	}
	else if (b.empty() && !a.empty()) // 待匹配字符串已空, 模式字符串未空, 有可能能匹配
	{
		while (!a.empty())
		{
			pattern.push_back(a.back());
			a.pop_back();
		}
		goto end;
	}
	char chab = b.back();
	while (!b.empty() && chab == b.back()) //取出待匹配字符串尾部的只含一种字符的字符串
	{
		b.pop_back();
		size++;
	}
		//取出模式字符串直到遇见不同的字母
		while (!a.empty() && (a.back() == chab || a.back() == '.' ||
			a.back() == '+' || a.back() == '*'
			|| a.back() == '?'))
		{
			pattern.push_back(a.back());
			a.pop_back();
		}
	if (pattern.back() == '+' || pattern.back() == '*' || pattern.back() == '?')
		//这几个符号属于前一个字符, 归还
	{
		a.push_back(pattern.back());
		pattern.pop_back();
	}
end:
	int dots = 0;
	while (!pattern.empty() && pattern.back() == '.') //将'.'分离出, 它是可变的参数
	{
		pattern.pop_back();
		dots++;
	}
	int min = 0, max = 0;
	while (!pattern.empty()) //计算取出的模式字符串的可变长度
	{
		//? 0 1 . single * 0~INF + 1~INF
		if (pattern.front() == '?')
		{
			pattern.pop_front();
			if (max != INF) max++;
		}
		else if (pattern.front() == '*')
		{
			pattern.pop_front();
			if (max != INF)
			{
				max = INF;
			}
		}
		else if (pattern.front() == '+')
		{
			pattern.pop_front();
			if (max != INF)
			{
				max = INF;
			}
			min++;
		}
		else if (pattern.front() == '.')
		{
			min++;
			if (max != INF)
			{
				max++;
			}
		}
		else// if (pattern.front() == chab)
		{
			min++;
			if (max != INF)
			{
				max++;
			}
		}
		pattern.pop_front();
	}
	bool result = false;
	for (int i = 0; i < dots; i++)
	{
		a.push_back('.');
	}
	for (int i = 0; i <= dots; i++) //根据加'.'的多少, 进行分叉
	{
		if ((max + i) < size || (min + i) > size)
		{
			if (!a.empty()) a.pop_back();
			continue;
		}
		result |= match(a, b);
		if (!a.empty()) a.pop_back();
	}
	return result;
}
int main(){
	string pattern, str;
	bool result;
	fstream f("sample.txt");
	while (true)
	{
		f >> pattern;
		if (!pattern.compare("END"))
		{
			break;
		}
		f >> str;
		/*cin >> pattern;
		cin >> str;*/
		result = match(pattern, str);
		if (result){
			cout << "true" << endl;
		}
		else cout << "false" << endl;
	}
	return 0;
}