#include<iostream>
#include<string>
#include<windows.h>

using namespace std;

#if 0
//继承定义
class Person
{
public:
	void Print()
	{
		cout << "name=" << name << endl;
		cout << "age=" << age << endl;
	}

public:
	string name = "Vision";

protected:
	int age = 18;//缺省值

private:
	string sex = "male";
};
    //派生类：继承关系 基类
class Student1:public Person//除private成员，和基类的访问限定符保持一致
{
protected:
	int stuId;
};

class Student2 :protected Person//基类中public protected为protected,private不可见
{
protected:
	int stuId;
};


class Student3 :private Person//基类中public protected为private,private不可见
{
protected:
	int stuId;
};

class Teacher :protected Person
{
protected:
	int jobId;
};

void Test1()
{
	Student1 s1;
	Student2 s2;
	Student3 s3; 
	Teacher t;
	s1.Print();
	//t.Print();//继承方式为protected,无法访问基类中public和protected成员
}

#endif

#if 0
//基类和派生类对象复制转换（切片）
class Person
{
protected:
	string _name = "Vision";
	string _sex;
	int _age = 18;
};

class Student :public Person
{
public:
	int _no;
};

void Test2()
{
	Student s;
	Person p = s;//子类对象可以赋值给父类对象
	Person* pp = &s;//子类对象可以赋值给父类的指针
	Person& rp = s;//子类对象可以赋值给父类的引用
	

	//s = p;父类对象不能赋值给子类对象
	Student* sp1 = (Student*)pp; //父类指针可以通过强转赋值给子类指针，会越界访问
	sp1->_no = 10;
	
	Student* sp2 = &s;
	sp2->_no = 10;
}

#endif


#if 0
//隐藏，重定义
class Person
{
public:
	string _name = "Vision";
	int _no = 18;//年龄
};

class Student :public Person
{
public:
	void Print()
	{
		cout << "name=" << _name << endl;
		cout << "age=" << Person::_no << endl;
		cout << "stuId=" << _no << endl;//屏蔽了父类中的_no
	}
protected:
	int _no = 223;//学号
};

class A
{
public:
	void fun()
	{
		cout << "fun()" << endl;
	}
};

class B: public A //A B中的fun()构成隐藏(函数名相同构成隐藏)
{
public:
	void fun(int i)
	{
		A::fun();
		cout << "fun(int i):" << i << endl;
	}
};
void Test3()
{
	Student s;
	s.Print();

	B b;
	b.fun(10);
}

#endif

#if 0
//派生类默认成员函数
class Person
{
public:
	Person(const char* name ="vision")
		:_name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		:_name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person& opserator=(const Person& p)"<<endl;
		if (this != &p)
			_name = p._name;

		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}

private:
	string _name;
};

class Student :Person
{
public:
	Student(const char* name = "Vision", int num = 222)
		:Person(name)
		,_num(num)
	{
		cout << "Student()" << endl;
	}

	Student(const Student& s)
		:Person(s)
		, _num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}

	Student& operator=(const Student& s)
	{
		cout << "Student& operator=(const Student& s)" << endl;

		if (this != &s)
		{
			Person::operator=(s);
			_num = s._num;
		}

		return *this;
	}

	~Student()
	{
		cout << "~Student()" << endl;
	}

protected:
	int _num;//学号
};

void Test4()
{
	Student s1("Vision",10);
	Student s2(s1);
	Student s3("Jack",18);
	s1 = s3;
}

#endif

#if 0
//不能被继承的类
	//构造函数私有化
class NoInherit
{
public:
	static NoInherit GetInstance()
	{
		return NoInherit();
	}

private:
	NoInherit()
	{};
};

	//final关键字禁止被继承
class NoInherit1 final
{};
#endif

#if 0
//友元关系不能被继承:父类不能访问子类保护和私有成员
class Student;
class Person
{
public:
	friend void Display(const Person& p, const Student& s);

protected:
	string _name="Vision" ;
};

class Student:public Person
{
protected:
	int _num= 18;
};

void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	//cout << s._num << endl; //无法访问
}

void Test5()
{
	Person p; 
	Student s;
	Display(p, s);
}
#endif

#if 0
class Person
{
public:
	Person()
	{
		++_count;
	}
protected:
	string name;
public:
	static int _count;
};
int Person::_count = 0;

class Student:public Person
{
protected:
	int _stuNum;
};

class Teacher :public Person
{
protected:
	int _jobId;
};

void Test6()
{
	Student s1;
	Student s2;
	Student s3;
	Teacher t;
	cout << "total count is:" <<Person:: _count << endl;//4

	Student::_count = 0;
	cout << "total count is:" << Person::_count << endl;//0

}
#endif

#if 0
//菱形继承：数据二义性和数据冗余
class Person
{
public:
	string _name;
};

class Student :public Person
{
protected:
	int _stuNum;
};

class Teacher :public Person
{
protected:
	int _jobId;
};

class Assistant :public Student,public Teacher
{
protected:
	int _major;
};


void Test7()
{
	Assistant A;
	//A.name = "Vision"; //二义性
	A.Student::_name = "Vision";//指定要访问的父类
	A.Teacher::_name = "Jack";

}

#endif

#if 0
class Person
{
public:
	string _name;
};

class Student :virtual public Person
{
protected:
	int _stuNum;
};

class Teacher :virtual public Person
{
protected:
	int _jobId;
};

class Assistant :public Student, public Teacher
{
protected:
	int _major;
};

void Test8()
{
	Assistant A;
	A._name = "Vision";//虚拟继承解决了数据二义性和数据冗余
}
#endif

#if 0
class A
{
public:
	int _a;
};
//class B:public A
class B :virtual public A
{
public:
	int _b;
};
//class C :public A
class C :virtual public A
{
public:
	int _c;
};
class D :public B, public C
{
public:
	int _d;
};
void Test9()
{
	//内存->虚基表指针->虚基表->偏移量找到A
	//切片时要找到自己的A
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._a = 3;
	d._b = 3;
	d._c = 4;
	d._d = 5;
}
#endif

//继承和组合
//is a
class Room
{
protected:
	string wallColor = "white";//墙的颜色
	string floor = "glass";//地板
};
class classroom :public Room
{
public:
	void Derive()
	{
		cout << "clean" << endl;
	}
};


//has a
class Room
{
protected:
	string wallColor = "white";//墙的颜色
	string floor = "glass";//地板

	Desk desk;
};
class Desk
{
	string _brand;//品牌
	size_t size;//尺寸
};

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	system("pause");
	return 0;
}
