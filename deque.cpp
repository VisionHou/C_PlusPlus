#include<iostream>
#include<windows.h>

using namespace std;

template<class T ,class Ref,class Ptr>
struct _DequeIterator
{
	typedef _DequeIterator<T, Ref, Ptr> Self;

	T* first;
	T* last;
	T* cur;
	T** node;

	Ref operator*()
	{
		return *cur;
	}

	bool operator!=(const Self& it)
	{
		return it.node != node;
	}


	bool operator==(const Self& it)
	{
		return it.node != node;
	}

	//buffer++
	Self operator++()
	{
		if (cur != last)
			++cur;

		else
		{
			++node;
			first = *node;
			last = first + 20;
			cur = first;
		}
		return *this;
	}

};

template<class T>
class Deque
{
public:
	typedef _DequeIterator<T, T&, T*> iterator;
	iterator begin()
	{
		return start;
	}

	iterator end()
	{
		return finish;
	}

private:
	iterator start;//buffer
	iterator finish;//buffer
	T** _mapArray;//中控(指针数组)
};

int main()
{
	Deque<int> d;
	Deque<int>::iterator it = d.begin();
	while (it != d.end())
	{
		*it;
		++it;
	}

	system("pause");
	return 0;
}