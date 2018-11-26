#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<string.h>
using namespace std;

class String
{
public:
	String()
		:_str(new char[1])
	{
		_str[0] = '\0';
	}

	String(const char* str)
		:_str(new char[strlen(str)+1])
	{
		strcpy(_str, str);
	}

	~String()
	{
		delete[] _str;
	}
private:
	char* _str;
};

void test1()
{
	String s1;
	String s2("hello");
	String S3(s2);

}


class String
{
public:
	//����
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}

	//��������
	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
	}

	//���صȺ�
	//s1(this)=s2(s)
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			//�ͷžɿռ�
			delete[] _str;
			//�����¿ռ䲢����s����
			char* newstr = new char[strlen(s._str) + 1];
			strcpy(newstr, s._str);
			//thisָ���¿ռ�
			_str = newstr;
		}
		return *this;
	}

	~String()
	{
		if(_str)
			delete[] _str;
	}
private:
	char* _str;
};
void test2()
{
	String s1;
	String s2("hello");
	String s3(s2);
	String s4 = s2;
}




class String
{
public:
	//����
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}

	//��������
	String(const String& s)
		:_str(nullptr)
	{
		//��s�����µ�String
		String tmp(s._str);
		//����this��tmp
		swap(_str, tmp._str);
	}

	//����=
	//s1=s2
	/*String& operator=(const String& s)
	{
		if (this != &s)
		{
			String tmp(s._str);
			swap(_str, tmp._str);
		}
		return *this;
	}
*/
	String& operator=(String& s)
	{
	
		swap(_str, s._str);
		return *this;
	}


	~String()
	{
		if (_str)
			delete[] _str;
	}
private:
	char* _str;
};
void test3()
{
	String s1;
	String s2("hello");
	String s3(s2);
	String s4 = s2;
}
int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}