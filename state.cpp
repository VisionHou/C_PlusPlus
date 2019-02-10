#include<iostream>
#include<windows.h>

using namespace std;

//多态：不同对象完成同一行为结果不同
//条件：继承；调用函数的对象是指针或引用；被调用函数虚函数重写
//重写：生类中有跟基类完全相同的虚函数(派生类virtual可省)
#if 0
class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "buy_All Money" << endl;
	}
};

class Student:public Person
{
public:
	//virtual void BuyTicket()
	void BuyTicket()
	{
		cout << "buy_Half Money" << endl;
	}
};

void Fun(Person& people)
{
	people.BuyTicket();
}

int main()
{
	Person p;
	Fun(p);

	Student s;
	Fun(s);
	system("pause");
	return 0;
}
#endif

#if 0
//协变：重写虚函数的返回值不同，必须为基类派生类的指针或引用
class A
{};
class B:public A
{};

class Person
{
public:
	virtual A* Fun()
	{
		return new A;
	}
};

class Student :public Person
{
public:
	virtual B* Fun()
	{
		return new B ;
	}
};

void fun(Person& people)
{
	people.Fun();
}

int main()
{
	Person p;
	fun(p);

	Student s;
	fun(s);
	system("pause");
	return 0;
}
#endif

#if 0
//析构函数的重写:编译器处理为destructor
class Person
{
public:
	~Person()
	{
		cout << "~Person" << endl;
	}
};

class Student
{
public:
	~Student()
	{
		cout << "~Student" << endl;
	}
};

int main()
{
	Person* p = new Person;
	Student* s = new Student;

	delete p;
	delete s;
	system("pause");
	return 0;
}
#endif

//