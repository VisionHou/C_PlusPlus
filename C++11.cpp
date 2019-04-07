#include<iostream>
#include<windows.h>
using namespace std;


void Test1()
{
	int a = 10;
	double b = 11.5;
	//a = b;//隐式类型转换
	//a = (int)b;
	a = static_cast<int>(b);
	cout << a << endl;//11

	int* c = &a;
	//int d = (int)c;
	//int d = static_cast<int>(c);类型转换无效
	int d = reinterpret_cast<int>(c);
	cout << d << endl;

	//const int i = 10;
	//int* j = const_cast<int*>(&i);//const int*/int const*
	//*j = 20;
	//cout << i << endl;
	//cout << *j << endl;

	volatile const int i = 10;
	int* j = const_cast<int*>(&i);//const int*/int const*
	*j = 20;
	cout << i << endl;
	cout << *j << endl;
}

class A
{
public:
	int _a;

	virtual void f()
	{}
};
class B :public A
{
public:
	int _b;
};

void fun(A* pa)
{
	B* pb1 = static_cast<B*>(pa);
	cout << "pb1" << pb1 << endl;
	B* pb2 = dynamic_cast<B*>(pa);
	cout << "pb2" << pb2 << endl;
}

void Test2()
{
	A a;
	B b;
	fun(&a);
	fun(&b);
}
int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}