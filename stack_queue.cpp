#include<windows.h>
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<functional>
using namespace std;

//stack模拟实现
//template<class T, class container = vector<T>>
//template<class T, class container = list<T>>
template<class T, class container = deque<T>>

class Stack
{
public:
	Stack()
	{}
	void Push(const T& x)
	{
		_con.push_back(x);
	}

	void Pop()
	{
		_con.pop_back();
	}

	size_t Size() const
	{
		return _con.size();
	}

	bool Empty() const
	{
		return _con.empty();
	}

	T& Top()
	{
		return _con.back();
	}


	const T& Top() const
	{
		return _con.back();
	}
private:
	container _con;
};
void Teststack()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	cout << s.Top() << endl;
	cout << s.Size() << endl;
	s.Pop();
	cout << s.Top() << endl;
	cout << s.Size() << endl;
}

//queue模拟实现
//template<class T, class container = vector<T>>
//template<class T, class container = list<T>>
template<class T, class container = deque<T>>
class Queue
{
public:
	Queue()
	{}

	void Push(const T& x)
	{
		_con.push_back(x);
	}

	void Pop()
	{
		_con.pop_front();
	}

	size_t Size() const
	{
		return _con.size();
	}

	T& Front()
	{
		return _con.front();
	}

	const T& Front() const
	{
		return _con.front();
	}

	T& Back()
	{
		return _con.back();
	}

	const T& Back() const
	{
		return _con.Back();
	}
	bool Empty()
	{
		return _con.empty();
	}
private:
	container _con;
};

void Testqueue()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	cout <<"size="<< q.Size() << endl;
	cout <<"front=="<< q.Front() << endl;
	cout << "back="<< q.Back() << endl;

	q.Pop();
	cout << "size=" << q.Size() << endl;
	cout << "front==" << q.Front() << endl;
	cout << "back=" << q.Back() << endl;
}

int main()
{
	//Teststack();
	Testqueue();

	system("pause");
	return 0;
}