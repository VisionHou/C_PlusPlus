#include<iostream>
#include<windows.h>
#include<assert.h>
using namespace std;

#if 0
//函数模板
template<typename T>
void Swap(T& left, T& right)
{
	T tmp = left;
	left = right;
	right = tmp;
}
void Test1()
{
	int a = 1, b = 3;
	double c = 1.0, d = 3.0;
	Swap(a, b);
	Swap(c, d);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
	cout << "d=" << d << endl;
}

//模板实例化
template<typename T>
T Add(const T& left,const  T& right)
{

	return left + right;
}
void Test2()
{
	int a = 1, b = 3;
	double c = 1.1, d = 3.3;
	Add(a, b);//隐式实例化
	Add(c, d);
	//Add(a, c);不能通过编译，模板中 编译器不会进行类型转换操作
	Add(a, (int)c);//显式实例化
	Add<int>(c, d);//4 显式实例化
}
#endif

//非模板函数和模板函数
int Add(int left, int right)
{
	return left + right;
}

template<typename T>
T Add( T& left,   T& right)
{

	return left + right;
}

void Test3()
{
	Add(1, 3);//与非模板函数匹配
	Add<int>(1, 3);//调用模板函数
	Add<int>(1.0, 3.0);//调用模板函数

}

//类模板 Vector不是一个具体的类，是一个模板
template<typename T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		:_p(new T(capacity))
		,_size(0)
		,_capacity(capacity)
	{}

	~Vector();

	void PushBack(const T& data)
	{
		_p[_size++] = data;
	}

	void PopBack()
	{
		--_size;
	}

	size_t Size()
	{
		return _size;
	}

	T& operator[](size_t pos)
	{
		assert(pos < _size);
			return _p[pos];
	}
private:
	T* _p;
	size_t _size;
	size_t _capacity;
};

template<typename T>//类模板中的函数在类外定义时要加模板
Vector<T>::~Vector()
{
	if (_p)
		free(_p);
}


void Test4()
{
	//模板类的实例化
	Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	for (int i=0;i<v1.Size();i++)
	{
		cout << v1[i] << "";
	}
	cout << endl;

	Vector<double> v2;
	v2.PushBack(1.1);
	v2.PushBack(2.2);
	v2.PushBack(3.3);
	for (int i = 0; i < v2.Size(); i++)
	{
		cout << v2[i] << "";
	}
	cout << endl;

}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
	system("pause");
	return 0;
}