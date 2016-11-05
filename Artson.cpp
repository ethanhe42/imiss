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
	if (b.empty() && a.empty()) // ��������ַ����ѿ�, ˵����ƥ��
	{
		return true;
	}
	else if (!b.empty() && a.empty()) // ��ƥ���ַ���δ��, ģʽ�ַ����ѿ�, ����ƥ��
	{
		return false;
	}
	else if (b.empty() && !a.empty()) // ��ƥ���ַ����ѿ�, ģʽ�ַ���δ��, �п�����ƥ��
	{
		while (!a.empty())
		{
			pattern.push_back(a.back());
			a.pop_back();
		}
		goto end;
	}
	char chab = b.back();
	while (!b.empty() && chab == b.back()) //ȡ����ƥ���ַ���β����ֻ��һ���ַ����ַ���
	{
		b.pop_back();
		size++;
	}
		//ȡ��ģʽ�ַ���ֱ��������ͬ����ĸ
		while (!a.empty() && (a.back() == chab || a.back() == '.' ||
			a.back() == '+' || a.back() == '*'
			|| a.back() == '?'))
		{
			pattern.push_back(a.back());
			a.pop_back();
		}
	if (pattern.back() == '+' || pattern.back() == '*' || pattern.back() == '?')
		//�⼸����������ǰһ���ַ�, �黹
	{
		a.push_back(pattern.back());
		pattern.pop_back();
	}
end:
	int dots = 0;
	while (!pattern.empty() && pattern.back() == '.') //��'.'�����, ���ǿɱ�Ĳ���
	{
		pattern.pop_back();
		dots++;
	}
	int min = 0, max = 0;
	while (!pattern.empty()) //����ȡ����ģʽ�ַ����Ŀɱ䳤��
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
	for (int i = 0; i <= dots; i++) //���ݼ�'.'�Ķ���, ���зֲ�
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