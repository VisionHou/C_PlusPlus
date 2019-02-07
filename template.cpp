#include<iostream>
#include<windows.h>
#include<assert.h>
using namespace std;

#if 0
//����ģ��
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

//ģ��ʵ����
template<typename T>
T Add(const T& left,const  T& right)
{

	return left + right;
}
void Test2()
{
	int a = 1, b = 3;
	double c = 1.1, d = 3.3;
	Add(a, b);//��ʽʵ����
	Add(c, d);
	//Add(a, c);����ͨ�����룬ģ���� �����������������ת������
	Add(a, (int)c);//��ʽʵ����
	Add<int>(c, d);//4 ��ʽʵ����
}
#endif

//��ģ�庯����ģ�庯��
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
	Add(1, 3);//���ģ�庯��ƥ��
	Add<int>(1, 3);//����ģ�庯��
	Add<int>(1.0, 3.0);//����ģ�庯��

}

//��ģ�� Vector����һ��������࣬��һ��ģ��
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

template<typename T>//��ģ���еĺ��������ⶨ��ʱҪ��ģ��
Vector<T>::~Vector()
{
	if (_p)
		free(_p);
}


void Test4()
{
	//ģ�����ʵ����
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