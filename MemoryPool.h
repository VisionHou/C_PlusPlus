#ifndef __OBJECT__POOL_H__
#define __OBJECT__POOL_H__

#include<stdlib.h>
#include<iostream>
using std::cout;
using std::endl;

//定长的对象池
template<class T>
class ObjectPool
{
protected:
	struct Block
	{
		char* _start = nullptr;
		size_t _bytesize = 0;
		size_t _leftsize = 0;
		Block* _next = nullptr;

		Block(size_t bytesize)
		{
			_start = (char*)malloc(bytesize);
			_bytesize = bytesize;
			_leftsize = bytesize;
			_next = nullptr;
		}
	};

public:
	ObjectPool(size_t initnum = 8)
	{
		_head = _tail = new Block(initnum * sizeof(T));
	}

	T* New()
	{
		T* obj=nullptr;
		if (_freelist != nullptr)
		{
			//优先使用归还的链表中的内存
			obj = _freelist;
			_freelist = (*(T**)_freelist);
		}

		else
		{
			//分割对象池
			if (_tail->_leftsize == 0)
			{
				Block* newblock = new Block(_tail->_bytesize * 2);
				_tail->_next = newblock;
				_tail = newblock;
			}

			obj = (T*)_tail->_start + (_tail->_bytesize - _tail->_leftsize);
			_tail->_leftsize -= sizeof(T);
		}

		return obj;
	}

	void Delete(T* ptr)
	{
		if (_freelist == nullptr)
		{
			_freelist = ptr;
			(*(T**)ptr) = nullptr;//获取前4/8个字节
		}
		else
		{
			//头插
			(*(T**)ptr) = _freelist;
			_freelist = nullptr;
		}
	}

protected:
	//自由链表
	T* _freelist = nullptr;

	//块管理
	Block* _head=nullptr;
	Block* _tail=nullptr;
};

void TestPool()
{
	ObjectPool<int> pool;
	int* p1 = pool.New();
	int* p2 = pool.New();

	cout << p1 << endl;
	cout << p2 << endl;

	pool.Delete(p1);
	pool.Delete(p2);

	cout << pool.New() << endl;
	cout << pool.New() << endl;
}
#endif 