#include<iostream>
#include<windows.h>

using namespace std;

//��̬����ͬ�������ͬһ��Ϊ�����ͬ
//�������̳У����ú����Ķ�����ָ������ã������ú����麯����д
//��д���������и�������ȫ��ͬ���麯��(������virtual��ʡ)
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
//Э�䣺��д�麯���ķ���ֵ��ͬ������Ϊ�����������ָ�������
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
//������������д:����������Ϊdestructor
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