#include<iostream>
#include<string>
#include<windows.h>

using namespace std;

#if 0
//�̳ж���
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
	int age = 18;//ȱʡֵ

private:
	string sex = "male";
};
    //�����ࣺ�̳й�ϵ ����
class Student1:public Person//��private��Ա���ͻ���ķ����޶�������һ��
{
protected:
	int stuId;
};

class Student2 :protected Person//������public protectedΪprotected,private���ɼ�
{
protected:
	int stuId;
};


class Student3 :private Person//������public protectedΪprivate,private���ɼ�
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
	//t.Print();//�̳з�ʽΪprotected,�޷����ʻ�����public��protected��Ա
}

#endif

#if 0
//����������������ת������Ƭ��
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
	Person p = s;//���������Ը�ֵ���������
	Person* pp = &s;//���������Ը�ֵ�������ָ��
	Person& rp = s;//���������Ը�ֵ�����������
	

	//s = p;��������ܸ�ֵ���������
	Student* sp1 = (Student*)pp; //����ָ�����ͨ��ǿת��ֵ������ָ�룬��Խ�����
	sp1->_no = 10;
	
	Student* sp2 = &s;
	sp2->_no = 10;
}

#endif


#if 0
//���أ��ض���
class Person
{
public:
	string _name = "Vision";
	int _no = 18;//����
};

class Student :public Person
{
public:
	void Print()
	{
		cout << "name=" << _name << endl;
		cout << "age=" << Person::_no << endl;
		cout << "stuId=" << _no << endl;//�����˸����е�_no
	}
protected:
	int _no = 223;//ѧ��
};

class A
{
public:
	void fun()
	{
		cout << "fun()" << endl;
	}
};

class B: public A //A B�е�fun()��������(��������ͬ��������)
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
//������Ĭ�ϳ�Ա����
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
	int _num;//ѧ��
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
//���ܱ��̳е���
	//���캯��˽�л�
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

	//final�ؼ��ֽ�ֹ���̳�
class NoInherit1 final
{};
#endif

#if 0
//��Ԫ��ϵ���ܱ��̳�:���಻�ܷ������ౣ����˽�г�Ա
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
	//cout << s._num << endl; //�޷�����
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
//���μ̳У����ݶ����Ժ���������
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
	//A.name = "Vision"; //������
	A.Student::_name = "Vision";//ָ��Ҫ���ʵĸ���
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
	A._name = "Vision";//����̳н�������ݶ����Ժ���������
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
	//�ڴ�->�����ָ��->�����->ƫ�����ҵ�A
	//��ƬʱҪ�ҵ��Լ���A
	D d;
	d.B::_a = 1;
	d.C::_a = 2;
	d._a = 3;
	d._b = 3;
	d._c = 4;
	d._d = 5;
}
#endif

//�̳к����
//is a
class Room
{
protected:
	string wallColor = "white";//ǽ����ɫ
	string floor = "glass";//�ذ�
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
	string wallColor = "white";//ǽ����ɫ
	string floor = "glass";//�ذ�

	Desk desk;
};
class Desk
{
	string _brand;//Ʒ��
	size_t size;//�ߴ�
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
