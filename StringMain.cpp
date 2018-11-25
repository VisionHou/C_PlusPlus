#include"string.h"
using vc::String;

void Test1()
{
	vc::String S1;
	vc::String S2("hello world");
	vc::String S3(S2);

	cout << S1 << endl;
	cout << S2 << endl;
	cout << S3 << endl;
	S1 = S2;
	cout << S1 << endl;

}

void Test2()
{
	vc::String S1;
	S1.PushBack('h');
	S1.PushBack('e');
	S1.PushBack('l');
	S1.PushBack('l');
	S1.PushBack('o');
	S1.Append("world");

	String::iterator it = S1.begin();
	while (it != S1.end())
	{
		cout << *it << "";
		it++;
	}
	cout << endl;

	cout << "size=" << S1.Size() << endl;
	cout << "capacity=" << S1.Capacity() << endl;

	vc::String S2;
	S2 += "nihaoya";
	S2.Swap(S1);
	cout << S1 << endl;
	cout << S2 << endl;

}

void Test3()
{
	vc::String S1;
	S1.Append("whatdoyousay");
	cout << S1 << endl;
	cout << "size=" << S1.Size() << endl;
	cout << "capacity=" << S1.Capacity() << endl;

	S1.Reserve(20);
	cout << S1 << endl;
	cout << "size=" << S1.Size() << endl;
	cout << "capacity=" << S1.Capacity() << endl;

	S1.Resize(3);	cout << S1 << endl;
	cout << "size=" << S1.Size() << endl;
	cout << "capacity=" << S1.Capacity() << endl;

	S1.Resize(10, 'h');
	cout << S1 << endl;
	cout << "size=" << S1.Size() << endl;
	cout << "capacity=" << S1.Capacity() << endl;

	S1.Resize(25, 'h');
	cout << S1 << endl;
	cout << "size=" << S1.Size() << endl;
	cout << "capacity=" << S1.Capacity() << endl;

}

void Test4()
{
	vc::String S1;
	S1.Append("HOWAREYOU");
	cout << S1[0] << endl;

	cout << "findpos=" << S1.Find("ARE") << endl;
	S1.Insert(2, "hahaha");
	cout << S1 << endl;
	S1.Erase(2, 6);
	cout << S1 << endl;


	cout << S1.Substr(2, 3) << endl;

}
int main()
{/*
	Test1();
	Test2();
	Test3();*/
	Test4();
	system("pause");
	return 0;
}




#if 0
///////////////////////////////////////
/////////////深浅拷贝/////////////////
/////////////////////////////////////
#include<iostream>
using namespace std;

class String
{
public:
	//构造 浅拷贝
	String()
		:_str(new char[1])
	{
		_str[0] = '\0';
	}

	String(char* str)
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}

	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}

	//浅拷贝
	String(const String& S)
		:_str(new char[strlrn(S._str] + 1)
	{
		strcpy(_str, S._str);
	}

	//传统写法深拷贝
	//s2(s1)
	String(const String& S)
		:_str(new char[strlen(S._str) + 1])
	{
		strcpy(_str, S._str);
	}

	//s2=s1
	String operator=(const String S)
	{
		if (this != &S)
		{
			delete[] _str;
			_str = new char[strlen(S._str) + 1];
			strcpy(_str, S._str);
		}
		return *this;
	}

	//现代写法深拷贝
		//s2(s1)
	String(const String& S)
		:_str(nullptr)
	{
		String tmp(S._str);
		swap(_str, tmp._str);
	}

	////s2=s1
	//String operator=(const String S)
	//{
	//	if (this != &S)
	//	{
	//		String tmp(S._str);
	//		swap(_str, tmp._str);
	//	}
	//	return *this;
	//}

	String operator=(const String S)
	{
		if (this != &S)
		{
			swap(_str, S._str);
		}
		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
		}
	}

private:
	char* _str;
};

#endif