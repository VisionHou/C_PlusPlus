#include<iostream>
#include<windows.h>
#include<assert.h>

using namespace std;

#if 0
//ģ�����
//������ģ���������Ϊ���������������ַ���
template<typename T,size_t N=10> //<����ģ�������������ģ�����>
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

//ģ���ػ�
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


//����ģ���ػ�����(��һ�������ĺ���ģ��)
  //1.template���<> 2.���������<ָ��type&> 3.�βα�Ҫ�ͻ�������һ��
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


//��ģ���ػ�
   //ȫ�ػ�����ģ�������������в����ػ�
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
	Data<char, int> d2;//���ػ�
}

#endif 


   //ƫ�ػ�:��ģ���������һ������������
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

//�ڶ��������ػ�Ϊint
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

//�ػ�Ϊָ��
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

//�ػ�Ϊ����
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
	Data<int, char> d1;//���û���ģ��
	Data<char, int> d2;//�����ػ���char intģ��
	Data<int*, int*> d3;//�����ػ�Ϊָ���ģ��
	Data<int&, int&> d4(1,3);//�����ػ�Ϊ���õ�ģ��

}

//������ȡ
#if 0
//1.ǳ����(�漰�Զ������Ϳ��ܳ���)
template<class T>
void Copy(T* dst, const T& src, size_t size)
{
	memcpy(dst, src, sizeof(T)* size);
}

//2.ѭ��Ч�ʵ� ���
template<class T>
void Copy(T* dst, const T& src, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

//3.���ֶ����ݵ���������
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


//4.ͨ��typeidȷ�����������ʵ�����ͣ���ö���бȽϣ��Ƿ�Ϊ�������ͣ�����Ч�ʵ�
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
//5.������ȡ�������������������ͺ��Զ�������
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
	Copy(a2, a1, 5);//��������ʹ���ػ���int�����е�IsPODΪTrueType,Get���������棬����ǳ����

	string s1[] = { "111","222","333" };//string����û���ػ������е�IsPODΪFalseType,Get�������ؼ٣����ø�ֵ����
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

