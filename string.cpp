#include"string.h"
#define _CRT_SECURE_NO_WARNINGS

using vc::String;

const size_t String::npos = -1;

void  String::Reserve(size_t n)
{
	if (n > _capacity)
	{
		char* newstr = new char[n + 1];
		strcpy(newstr, _str);
		delete[] _str;
		_str = newstr;
		_capacity = n;
	}
}

void String::Resize(size_t n, char ch )
{
	if (n < _size)
	{
		_str[n] = '\0';
		_size = n;
	}
	else
	{
		if (n > Capacity())
		{
			Reserve(n);
		}
		size_t pos = _size;
		while (pos < n)
		{
			_str[pos] = ch;
			pos++;
		}
		_size = n;
		_str[n]='\0';

	}
}

void String::PushBack(char ch)
{
	//检测是否需要增容
	if (_size == _capacity)
		Reserve(_capacity * 2);

	_str[_size] = ch;
	_size++;
	_str[_size] = '\0';


}

void String::Append(const char* str)
{
	//检测是否需要增容
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		Reserve(_size + len);
	}

	strcpy(_str + _size, str);
	_size += len;
}

String& String:: operator+=(char ch)
{
	this->PushBack(ch);
	return *this;
}

String& String::operator+=(const char* str)
{
	this->Append(str);
	return *this;
}

size_t String:: Find(char ch, size_t pos )
{
	assert(pos < _size);

	while (pos < _size)
	{
		if (ch == _str[pos])
		{
			return pos;
		}

		++pos;
	}

	return String::npos;
}

size_t String::RFind(char ch, size_t pos)
{
	int end = _size - 1;

	if (pos != String::npos)
	{
		assert(pos < _size);

		end = pos;
	}

	while (end > 0)
	{
		if (ch ==_str[end])
		{
			return end;
		}

		--end;
	}

	return String::npos;
}

size_t String::String::Find(const char* str, size_t pos)
{
	assert(pos < _size);

	char* pmatch = strstr(_str, str);
	if (pmatch == nullptr)
		return npos;
	else
		return pmatch - _str;
}

void String::Insert(size_t pos, char ch)
{
	assert(pos < _size);
	//增容
	if (_size == _capacity)
	{
		Reserve(_capacity * 2);
	}

	//搬移元素
	int end = _size ;
	while ((int)pos <= end)
	{
		_str[end + 1] = _str[end];
		end--;
	}

	//插入元素
	_str[pos] = ch;
	_size++;
}

void String::Insert(size_t pos, const char* str)
{
	int len = strlen(str);
	//增容
	if (_size + len > _capacity)
	{
		Reserve(_size + len);
	}

	//搬移元素
	int end = _size ;
	while ((int)pos <= end)
	{
		_str[end + len] = _str[end];
		end--;
	}

	//插入字符串
	while (*str)
	{
		_str[pos] = *str;
		pos++;
		str++;
	}

	_size += len;
}

void ::String::Erase(size_t pos, size_t len)
{

	assert(pos < _size);
	if (len == npos || pos + len >= _size)
	{
		_str[pos] = '\0';
		_size = pos;
	}
	else
	{
		for (size_t i = 0; i < len; ++i)
		{
			_str[pos] = _str[pos + len];
			pos++;
		}

		_size -= len;
		_str[_size] = '\0';
	}
}

String String::Substr(size_t pos, size_t len)
{
	assert(pos < _size);
	//len太长
	if (pos + len > _size)
	{
		len = _size - pos;
	}

	String substr;
	substr.Reserve(len);
	for (size_t i =pos; i < pos+len; i++)
	{
		substr+= _str[i];
	}

	return substr;
}

