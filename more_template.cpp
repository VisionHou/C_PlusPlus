#include<iostream>
#include<windows.h>
#include<assert.h>

using namespace std;

#if 0
//模板参数
//非类型模板参数不能为浮点数，类对象和字符串
template<typename T,size_t N=10> //<类型模板参数，非类型模板参数>
class Array
{
public:
	T& operator[](size_t index)
	{
		return _array[index];
	}

	const T& operator[](size_t index)const
	{
		return _array[index];
	}

	size_t Size()
	{
		return _size;
	}

	bool Empty()
	{
		return _size == 0;
	}

private:
	T _array[N];
	size_t _size;
};

//模板特化
template<class T>
bool IsEqual(T& left, T& right)
{
	return left == right;
}
void Test1()
{
	const char* p1 = "hello";
	const char* p2 = "world";
	if (IsEqual(p1, p2))
		cout << p1 << endl;
	else
		cout << p2 << endl;
}


//函数模板特化步骤(有一个基础的函数模板)
  //1.template后加<> 2.函数名后加<指定type&> 3.形参表要和基础类型一样
template<>
bool IsEqual<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) > 0)
		return true;
	return false;
}

void Test2()
{
	const char* p1 = "hello";
	const char* p2 = "world";
	if (IsEqual(p1, p2))
		cout << p1 << endl;
	else
		cout << p2 << endl;
}


//类模板特化
   //全特化：将模板参数类表中所有参数特化
template<typename T1,typename T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2> "<< endl;
	}
private:
	T1 _data1;
	T2 _data2;
};

template<>
class Data<char,int>
{
public:
	Data()
	{
		cout << "Data<char,int> " << endl;
	}
private:
	char _data1;
	int _data2;
};

void Test3()
{
	Data<int, int> d1;
	Data<char, int> d2;//调特化
}

#endif 


   //偏特化:对模板参数更进一步的条件限制
template<typename T1, typename T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2> " << endl;
	}
private:
	T1 _data1;
	T2 _data2;
};

//第二个参数特化为int
template<typename T1>
class Data<T1,int>
{
public:
	Data()
	{
		cout << "Data<T1,int>" << endl;
	}
private:
	T1 _data1;
	int _data2;
};

//特化为指针
template<typename T1, typename T2>
class Data<T1* , T2*>
{
public:
	Data()
	{
		cout << "Data<T1*,T2*> " << endl;
	}
private:
	T1 _data1;
	T2 _data2;
};

//特化为引用
template<typename T1, typename T2>
class Data<T1& , T2&>
{
public:
	Data(const T1& d1,const T2& d2)
		:_data1(d1)
		,_data2(d2)
	{
		cout << "Data<T1&,T2&> " << endl;
	}
private:
	const T1& _data1;
	const T2& _data2;
};

void Test4()
{
	Data<int, char> d1;//调用基础模板
	Data<char, int> d2;//调用特化的char int模板
	Data<int*, int*> d3;//调用特化为指针的模板
	Data<int&, int&> d4(1,3);//调用特化为引用的模板

}

//类型萃取
#if 0
//1.浅拷贝(涉及自定义类型可能出错)
template<class T>
void Copy(T* dst, const T& src, size_t size)
{
	memcpy(dst, src, sizeof(T)* size);
}

//2.循环效率低 深拷贝
template<class T>
void Copy(T* dst, const T& src, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

//3.需手动传递第三个参数
template<class T>
void Copy(T* dst, const T& src, size_t size, bool IsPOD)
{
	if(IsPOD)
		memcpy(dst, src, sizeof(T)*size);
	else
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
}


//4.通过typeid确定拷贝对象的实际类型，在枚举中比较，是否为内置类型，遍历效率低
bool IsPodType(const char* strType)
{
	const char* arrType[] = { "char","short","int","long","long long","float","double","long double" };
	for (size_t i = 0; i < sizeof(arrType) / sizeof(arrType[0]); i++)
	{
		if (strcmp(strType, arrType[i]))
			return true;

		return false;
	}
}
template<class T>
void Copy(T* dst, const T& src, size_t size)
{
	if (IsPodType(typeid(T).name()))
		memcpy(dst, src, sizeof(T)*size);
	else
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
}

#endif
//5.类型萃取：两个类区分内置类型和自定义类型
struct TrueType
{
	static bool Get()
	{
		return true;
	}
};
struct FalseType
{
	static bool Get()
	{
		return false;
	}
};

template<class T>
struct TypeTraits
{
	typedef FalseType IsPOD;
};

template<>
struct TypeTraits<bool>
{
	typedef TrueType IsPOD;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType IsPOD;
}; 

template<>
struct TypeTraits<char>
{
	typedef TrueType IsPOD;
}; 

template<>
struct TypeTraits<short>
{
	typedef TrueType IsPOD;
};

template<>
struct TypeTraits<double>
{
	typedef TrueType IsPOD;
};

template<class T>
struct TypeTraits<T*>
{
	typedef TrueType IsPOD;
};
//......

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if(TypeTraits<T>::IsPOD::Get())
		memcpy(dst, src, sizeof(T)*size);
	else
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
}

void Test5()
{
	int a1[] = { 1,2,3,4,5 };
	int a2[5];
	Copy(a2, a1, 5);//程序运行使用特化的int，其中的IsPOD为TrueType,Get函数返回真，调用浅拷贝

	string s1[] = { "111","222","333" };//string类型没有特化，其中的IsPOD为FalseType,Get函数返回假，调用赋值拷贝
	string s2[3];
	Copy(s2, s1, 3);
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	system("pause");
	return 0;
}

