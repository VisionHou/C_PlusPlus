#include<iostream>
#include<list>
#include<string>
#include"list.hpp"
#include<windows.h>

using namespace std;

void Test1()
{
	list<int> l1;
	list<int> l2(3, 10);
	list<int> l3(l2.begin(), l2.end());
	list<int> l4(l2);

	list<int>::reverse_iterator l = l2.rbegin();
	while (l != l2.rend())
	{
		cout << *l << " ";
		l++;
	}
	cout << endl;

	for (const auto& e : l3)
	{
		cout << e << " ";
	}
	cout << endl;

	auto e = l4.cbegin();
	while (e != l4.cend())
	{
		cout << *e << " ";
		e++;
	}
	cout << endl;

	int array[] = { 11,22,33,44 };
	list<int> l5(array, array + sizeof(array) / sizeof(array[0]));
	for (const auto& e : l5)
	{
		cout << e << " ";
	}
	cout << endl;

	string s("hello");
	list<int> l6(s.begin(), s.end());
	for (const auto& e : l6)
	{
		cout << e << " ";
	}
	cout << endl;
}

void Test2()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	for (const auto& e : l)
	{
		cout << e << " ";
	}
	cout << endl;

	l.pop_back();
}

void Test3()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	auto pos = find(l.begin(), l.end(), 3);
	l.insert(pos, 7);//插入元素迭代器不会失效，还指向原位置
	for (const auto& e : l)
	{
		cout << e << " ";
	}
	cout << endl;

	l.erase(pos);//删除节点后迭代器失效
	for (const auto& e : l)
	{
		cout << e << " ";
	}
	cout << endl;
	*pos;//程序崩溃
    
}

class Date
{
public:
	Date(int year = 2018, int month = 11, int day = 22)
		:_year(year), _month(month), _day(day)
	{
		cout << "Date(int,int,int):" << this << endl;
	}

	Date(const Date& d)
		:_year(d._year), _month(d._month), _day(d._day)
	{
		cout << "Date(const Date&):" << this << endl;

	}

private:
	int _year;
	int _month;
	int _day;
};
void Test4()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	auto pos = find(l.begin(), l.end(), 3);
	l.emplace(pos,9);//和insert效果一样
	for (const auto& e : l)  
	{
		cout << e << " ";
	}
	cout << endl;

	Date d;
	list<Date> l1;
	l1.emplace(l1.begin(),d);//调用一次构造一次拷贝构造

	l1.emplace(l1.begin(),2018,11,23);//隐式类型转换20181123先构造一个对象，在用这个对象去插入

}

void Test5()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(4);
	l.push_back(5);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.sort();//排序
	for (const auto& e : l)
	{
		cout << e << " ";
	}
	cout << endl;

	l.unique();//去重(前后比较是否相同)，先排序再去重
	for (const auto& e : l)
	{
		cout << e << " ";
	}
	cout << endl;
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//vc::TestList1();
	//vc::TestList2();
	vc::TestList3();
	system("pause");
	return 0;
}