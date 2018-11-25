#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

using namespace std;
namespace vc
{
	class String
	{
	public:
		//迭代器
		typedef char* iterator;
		typedef const char* constiterator;

		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		constiterator cbegin()
		{
			return _str;
		}
		constiterator cend()
		{
			return _str + _size;
		}

		//构造
		String(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size > 10 ? _size : 10;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//拷贝构造
		String(const String& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			//深拷贝
			String tmp(s._str);
			this->Swap(tmp);
		}

		//析构
		~String()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//赋值
		String& operator=(String& s)
		{
			this->Swap(s);
			return *this;
		}

		void Swap(String& s)
		{
			swap(_str, s._str);
			swap(_capacity, s._capacity);
			swap(_size, s._size);
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos)const
		{
			assert(pos < _size);
			return _str[pos];
		}

		size_t Size()const
		{
			return _size;
		}

		size_t Capacity()const
		{
			return _capacity;
		}

		const char* c_str()
		{
			return _str;
		}

		void Reserve(size_t n);
		void Resize(size_t n, char ch = '\0');

		void PushBack(char ch);
		void Append(const char* str);
		String& operator+=(char ch);
		String& operator+=(const char* str);
		size_t Find(char ch, size_t pos = 0);
		size_t RFind(char ch, size_t pos = npos);

		size_t Find(const char* str, size_t pos = 0);
		void Insert(size_t pos, char ch);
		void Insert(size_t pos, const char* str);
		void Erase(size_t pos, size_t len = npos);
		String Substr(size_t pos, size_t len = npos);
		friend ostream& operator<<(ostream& cout, const String& s)
		{
			cout << s._str;
			return cout;

		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	public:
		static const size_t npos;
	};

}