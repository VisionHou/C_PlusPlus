#include<windows.h>
#include<iostream>
#include<queue>
#include<vector>
#include<deque>
#include<functional>
using namespace std;

#if 0
//内置类型
void TestPriority()
{
	priority_queue<int> q;
	q.push(3);
	q.push(6);
	q.push(2);
	q.push(9);
	q.push(5);
	cout << q.top()<< endl;

	priority_queue<int> q1;
	vector<int> v{ 1,4,7,9,0,4,5 };
	for (const auto& e : v)
		q1.push(e);
	cout << "top==" << q1.top() << endl;
	cout << "size" << q1.size() << endl;

	q1.pop();
	cout << "top==" << q1.top() << endl;
	cout << "size=" << q1.size() << endl;

	priority_queue<int,vector<int>,greater<int>> q2(v.begin(),v.end());
	for (const auto& e : v)
		q2.push(e);
	cout << "top==" << q2.top() << endl;
}

//自定义类型
class Date
{
public:
	Date(int year = 1998, int month = 6, int day = 30)
		:_year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator>(const Date& d) const
	{
		return (_year > d._year) ||
			((_year == d._year)&&(_month > d._month)) ||
			((_year == d._year)&&(_month == d._month)&&(_day > d._day));
	}

	bool operator<(const Date& d) const
	{
		return (_year < d._year) ||
			((_year == d._year) && (_month < d._month)) ||
			((_year == d._year) && (_month ==d._month) && (_day < d._day));
	}

	friend ostream& operator<<(ostream& _cout, const Date d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};
void TestPriority2()
{
	Date d(2018, 11, 28);
	cout << d << endl;

	priority_queue<Date> q;
	q.push(Date(2018, 10, 20));
	q.push(Date(2019, 10, 20));
	q.push(Date(2018, 10, 29));
	cout << q.top() << endl;
	q.pop();
	cout << q.top() << endl;

	priority_queue<Date,vector<Date>,greater<Date>>q1;
	q1.push(Date(2018, 10, 20));
	q1.push(Date(2019, 10, 20));
	q1.push(Date(2018, 10, 29));
	cout << q1.top() << endl;
	q1.pop();
	cout << q1.top() << endl;

}

//自定义比较
void TestPriority3()
{
	class Less
	{
	public:
		bool operator()(const Date* pleft,const Date* pright)
		{
			return *pleft < *pright;
		}
	};
	priority_queue<Date*, vector<Date*>, Less> q1;
	q1.push(&Date(2017, 10, 20));
	q1.push(&Date(2019, 10, 20));
	q1.push(&Date(2018, 10, 29));
	cout << *q1.top() << endl;
	q1.pop();
	cout << *q1.top() << endl;
}
#endif

template<class T>
class Less {
public:
	bool operator()(const T& x1, const T& x2)const
	{
		return x1 < x2;
	}
};

template<class T>
class Greater {
public:
	bool operator()(const T& x1, const T& x2)const
	{
		return x1 > x2;
	}
};

template<class T,class container=vector<T>,class compare=Greater<T>>
//template<class T,class container=vector<T>>
class PriorityQueue
{
public:
	void _AdjustUp(size_t child)
	{
		int parent = (child - 1) / 2;
		while (child>0)
		{
			//if (_con[child] < _con[parent])
			compare com;
			if (com(_con[child] , _con[parent]))
			{
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child -1) /2;
			}

			else
			{
				return;
			}
		}
	}

	void _AdjustDown(int parent)
	{
		int child = parent * 2 + 1;

		while (child<_con.size())
		{

			//if (child + 1< _con.size()&&_con[child + 1] < _con[child])
			compare com;
			if (child + 1 < _con.size() && com(_con[child + 1] , _con[child]))
				child += 1;

			//if (_con[child] < _con[parent])
			if (com(_con[child] , _con[parent]))
			{
				swap(_con[child], _con[parent]);
				parent = child;
				child = parent * 2 + 1;
			}

			else
				return;
		}
	}

	void Push(const T& x)
	{
		_con.push_back(x);
		_AdjustUp(_con.size() - 1);
	}

	void Pop()
	{
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		_AdjustDown(0);
	}

	T& Top()
	{
		return _con[0];
	}

	size_t Size()
	{
		return _con.size();
	}

	bool Empty()
	{
		return _con.empty();
	}
private:
	container _con;
};

void TestPriority4()
{
	//PriorityQueue<int,vector<int>> q;
	//PriorityQueue<int, deque<int>> q;

	//PriorityQueue<int, vector<int>> q;
	//PriorityQueue<int, vector<int>,Greater<int>> q;
	//PriorityQueue<int, vector<int>, Less<int>> q;

	//PriorityQueue<int, deque<int>, Greater<int>> q;
	PriorityQueue<int, deque<int>, Less<int>> q;


	q.Push(2);
	q.Push(3);
	q.Push(9);
	q.Push(6);
	q.Push(8);
	cout << "size=" << q.Size() << endl;

	while (!q.Empty())
	{
		cout << q.Top() << endl;
		q.Pop();
	}
	cout << endl;
	cout << "size=" << q.Size() << endl;


}

int main()
{
	//TestPriority1();
	//TestPriority2();
	//TestPriority3();

	TestPriority4();
	Less<int> less;
	cout << less(20, 10) << endl;
	cout << less.operator()(20, 10) << endl;

	system("pause");
	return 0;
}
