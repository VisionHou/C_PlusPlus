#include<iostream>
#include<windows.h>
#include<string>
#include<vector>

#if 0
double Division(int left, int right)
{
	//除数为0时抛异常
	if (right == 0)
		throw "Division zero bug...";
	else
		return ((double)left / (double)right);
}
void Fun()
{
	int a, b;
	std::cin >> a >> b;
	std::cout <<Division(a, b)<<std::endl;
}

int main()
{
	try {
		Fun();
	}
	catch (const char* errmsg)
	{
		std::cout << errmsg << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknow error";
	}
	system("pause");
	return 0;
}
#endif

#if 0
//重新抛出异常
double Division(int left, int right)
{
	//除数为0时抛异常
	if (right == 0)
		throw "Division zero bug...";
	else
		return ((double)left / (double)right);
}
void Fun()
{
	int *array = new int[10];
	try {
		int a, b;
		std::cin >> a >> b;
		std::cout << Division(a, b) << std::endl;

	}
	//除0错误抛出异常，捕获后重新抛出去
	catch (...)
	{
		std::cout << "delete[]" << array << std::endl;
		delete[] array;
		throw;
	}

	std::cout << "delete[]" << array << std::endl;
	delete[] array;
}

int main()
{
	try {
		Fun();
	}
	catch (const char* errmsg)
	{
		std::cout << errmsg << std::endl;
	}
	system("pause");
	return 0;
}
#endif

/*
//可能抛出A/B/C/D类型的异常
void fun()
{
	throw(A, B, C, D);
}
//只抛出bad_alloc的异常
void* operator new(std::size_t size)
{
	throw(std::bad_alloc); 
}
//不会抛异常
void* operator delete(std::size_t size, void* ptr)
{
	throw();
}
*/
#if 0
//抛出派生类对象，捕获基类
class Exception
{
protected:
	std::string _errmsg;
	int _id;
};

class SqlException : public Exception
{};
class CacheException : public Exception
{};
class HttpServerException : public Exception
{};

int main()
{
	try
	{
		//抛出派生类对象
	}
	catch (const Exception& e)
	{
		//捕获父类对象	
	}
	catch (...)
	{
		std::cout << "Unknow error"<<std::endl;
	}
	system("pause");
	return 0;
}
#endif

int main()
{
	try
	{
		std::vector<int> v(10, 5);
		v.reserve(1000000000);//bad_alloc
		v.at(10) = 10;//invalid vector<T> suscript
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknow error" << std::endl;
	}
	system("pause");
	return 0;
}