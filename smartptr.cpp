#include<iostream>
#include<mutex>
#include<windows.h>

using namespace std;

#if 0
template<class T>
class RAII
{
public:
	RAII(T* ptr=nullptr)
		:_ptr(ptr)
	{}
	~RAII()
	{
		if (_ptr)
			delete_ptr;
	}
private:
	T* _ptr;
};

int main()
{
	try
	{
		int* p = (int*)malloc(sizeof(int));
		RAII<int> sp(p);

		//.....sp��������
		//........
	}
	catch(const exception& e)
	{
		cout << e.what() << endl;
	}
	system("pause");
	return 0;
}
#endif


struct Date
{
	int _year;
	int _month;
	int _day;
};

#if 0
//auto_ptrʹ��
int main()
{
	auto_ptr<Date> s1(new Date);
	s1->_year = 1998;
	s1->_month = 6;
	s1->_day = 30;
	auto_ptr<Date> s2(s1);//����s1����
	s2->_year = 2019;
	s2->_month = 2;
	s2->_day = 17;

	//s1->_day = 1998;�������
	system("pause");
	return 0;
}

#endif

#if 0
//ʵ��auto_ptr
template<class T>
class Auto_Ptr
{
public:
	Auto_Ptr(T* ptr)
		:_ptr(ptr)
	{}
	
	Auto_Ptr(Auto_Ptr<T>& copy)
		:_ptr(copy._ptr)
	{
		copy._ptr = nullptr;
	}

	Auto_Ptr<T>& operator=(Auto_Ptr<T>& copy)
	{
		if (this != copy)
		{
			//�ͷŵ�ǰ������Դ
			delete _ptr;

			//ת����Դ
			_ptr = copy._ptr;
			copy->_ptr = nullptr;
		}

		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~Auto_Ptr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

int main()
{
	Auto_Ptr<Date> s1(new Date);
	s1->_year = 1998;
	s1->_month = 6;
	s1->_day = 30;
	Auto_Ptr<Date> s2(s1);
	s2->_year = 2019;
	s2->_month = 2;
	s2->_day = 17;

	//s1->_day = 1998;�������
	system("pause");
	return 0;
}

#endif



#if 0
//ʵ��unique_ptr
template<class T>
class Unique_Ptr
{
public:
	Unique_Ptr(T* ptr)
		:_ptr(ptr)
	{}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~Unique_Ptr()
	{
		if (_ptr)
			delete _ptr;
	}
	
private:
	//C++98������
	/*Unique_Ptr(const Unique_Ptr<T>& );
	Unique_Ptr<T>& operator=(const Unique_Ptr<T>&);*/

	//C++11
	Unique_Ptr(const Unique_Ptr<T>&) = delete;
	Unique_Ptr<T>& operator=(const Unique_Ptr<T>&) = delete;

	T* _ptr;
};

int main()
{
	Unique_Ptr<Date> s1(new Date);
	s1->_year = 1998;
	s1->_month = 6;
	s1->_day = 30;
	//Unique_Ptr<Date> s2(s1);���벻ͨ��

	system("pause");
	return 0;
}
#endif

#if 0
//shared_ptrʹ��
int main()
{
	//���ü���
	shared_ptr<Date> s1(new Date);
	s1->_year = 2019;
	s1->_month = 2;
	s1->_day = 18;

	shared_ptr<Date> s2(s1);
	cout << "s1_use" << s1.use_count() << endl;//2
	shared_ptr<Date> s3(s1);

	cout << "s1_use" << s1.use_count() << endl;//3
	cout << "s3_use" << s2.use_count() << endl;//3
	cout << "s3_use" << s3.use_count() << endl;//3


	system("pause");

	return 0;
}

#endif

//ʵ��shared_ptr
template<class T>
class Shared_Ptr
{
public:
	Shared_Ptr(T* ptr = nullptr)
		:_ptr(ptr)
		,_count(new int(1))
		, _mutex(new mutex)
	{
		if (_ptr == nullptr)
			*_count=0;
	}

	Shared_Ptr(const Shared_Ptr<T>& copy)
		:_ptr(copy._ptr)
		,_count(copy._count)
		,_mutex(copy._mutex)
	{
		//ptr��Ϊ���������ü���
		if (_ptr)
			AddCount();
	}

	Shared_Ptr<T>& operator=(const Shared_Ptr<T>& sp)
	{
		if (this != &sp)
		{
			//�ͷŵ�ǰ������Դ
			Release();
			//��ֵ
			_ptr = sp._ptr;
			_count = sp._count;
			_mutex = sp._mutex;
		
			if (_ptr)
				AddCount();
		}
		return *this;

	}

	~Shared_Ptr()
	{
		Release();
	}

	int AddCount()
	{
		_mutex->lock();
		(*_count)++;
		_mutex->unlock();

		return *_count;
	}

	int SubCount()
	{
		_mutex->lock();
		(*_count)--;
		_mutex->unlock();

		return *_count;
	}

	T& UseCount()
	{
		return *_count;
	}

	T* Get()
	{
		return _ptr;
	}
	
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

private:
	void Release()
	{
		if (_ptr == nullptr)
			delete _mutex;

		if (_ptr&& SubCount() == 0)
		{
			delete _ptr;
			delete _count;
			delete _mutex;
		}
	}
private:
	T* _ptr;
	int* _count;//���ü���
	mutex* _mutex;
};

int main()
{
	Shared_Ptr<int> s1(new int(10));
	Shared_Ptr<int> s2(s1);
	cout << "s1 " << s1.UseCount() << endl;
	cout << "s2 " << s2.UseCount() << endl;
	cout << "s1 " << s1.Get() << endl;
	cout << "s2 " << s2.Get() << endl;

	Shared_Ptr<int> s3;
	s3 = s1;
	cout << "s1 " << s1.UseCount() << endl;
	cout << "s1 " << s1.Get() << endl;
	cout << "s3 " << s3.UseCount() << endl;
	cout << "s3 " << s3.Get() << endl;

	*s3 = 20;
	system("pause");

	return 0;
}
