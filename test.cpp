#include<iostream>
#include<windows.h>

using namespace std;

#if 0
//内存对齐
class A
{
private:
	double a;
};

class B
{
public:
	void Fun() {}

private:
	int a;
	double b;
	char c;
};

class C
{
};
void Test1()
{
	cout << sizeof(A) << endl;//8
	cout << sizeof(B) << endl;//24
	cout << sizeof(C) << endl;//1

}
#endif

#if 0
//this指针不改变成员变量时可以为空
class A
{
public:
	void PrintA()
	{
		cout << _a << endl;
	}

	void Show()
	{
		cout << "Show()" << endl;
	}
private:
	int _a;
};

void Test2()
{
		A* p = NULL;
		//p->PrintA();//编译崩溃
		p->Show();
}

int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "jack")
	{
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}
	~String()
	{
		cout << "~String()" << endl;
		free(_str);
	}
private:
	char* _str;
};
int main()
{
	String s1("hello");
	String s2(s1);
}
#endif

#if 0
//总会使用初始化列表
class Time
{
public:
	Time(int hour = 0)
		:_hour(hour)
	{
		cout << "Time" << endl;
	}
private:
 int _hour;
};
class Date
{
public:
	Date(int day)
	{}
private:
	Time t;
	int _day;
};

int main()
{
	Date d(1);
	return 0;
}
#endif


#if 0

class Date
{
public:
	Date(int year)
		:_year(year)
	{}


	//禁止隐式类型转换
   /* explicit Date(int year)
		:_year(year)
	{}*/

private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2018);
	d1 = 2019;//隐式类型转换

	return 0;
}#endif

//C++11 非静态成员变量可以在声明时初始化
class B
{
public:
	B(int b = 0)
		:_b(b)
	{}
	int _b;
};
class A
{
public:
	void Print()
	{
		cout << a << endl;
		cout << b._b << endl;
		cout << p << endl;
	}
private:

	int a = 10;
	B b = 20;
	int* p = (int*)malloc(4);
	static int n;
};
int A::n = 10;
int main()
{
	A a;
	a.Print();
	system("pause");
	return 0;
}
