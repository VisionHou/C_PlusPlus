#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <windows.h>
#include"vector.h"

using namespace std;

void test_vector1()
{
	string str("hello");

	vector<int> v1;
	vector<int> v2(10, 3);
	vector<int> v3(v2.begin(), v2.end());
	vector<int> v4(str.begin(), str.end());

	vector<int >::iterator it = v2.begin();

	while (it != v2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	it = v3.begin();
	while (it != v3.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	it = v4.begin();
	while (it != v4.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//vector<int>::reverse_iterator rit = v4.rbegin();
	auto rit= v4.rbegin();
	while (rit != v4.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	vector<int>::const_iterator cit = v4.cbegin();
	while (cit != v4.cend())
	{
		cout << *cit << " ";
		++cit;
	}
	cout << endl;


	for (size_t i = 0; i < v4.size(); i++)
	{
		cout << v4[i] << " ";
	}
	cout << endl;

	for (const auto& e : v4)
	{
		cout << e << " ";
	}
	cout << endl;
	

	vector<string> s;
	s.push_back("hello");
	s.push_back("hello");
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;


}

void test_vector2()
{
	size_t sz;
	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	foo.reserve(100);
	for (int i = 0; i < 100; ++i) {
		foo.push_back(i);
		//foo[i] = i;
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	for (const auto& e : foo)
	{
		cout << e << " ";
	}
	cout << endl;
}


void test_vector3()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//v.push_back(5);

	//vector<int>::iterator pos = find(v.begin(), v.end(), 2);
	auto pos = find(v.begin(), v.end(), 2);
	if (pos != v.end())
	{
		v.insert(pos, 20);
	}

	//// 迭代器失效
	//插入和删除
	*pos = 10;
	pos = find(v.begin(), v.end(), 2);
	v.erase(pos);
	*pos = 10;

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	auto e = v.begin();
	while (e != v.end())
	{
		if (*e % 2 == 0)
		{
			e=v.erase(e);
		}
		else
		{
			e++;
		}
	}

	for (auto it : v)
	{
		cout << it << " ";
	}
	cout << endl;
}




void TestVector1()
{

	vc::Vector<int> v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	v1.PopBack();
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	vc::Vector<int> v2(10,3);
	for (auto e : v2)
	{
		cout << e << " ";
	}
	cout << endl;

	vc::Vector<int> v3(v2.begin(),v2.end());
	for (auto e : v3)
	{
		cout << e << " ";
	}
	cout << endl;

	vc::Vector<int> v4(v2);
	for (auto e : v4)
	{
		cout << e << " ";
	}
	cout << endl;

	vc::Vector<string> strv;
	strv.PushBack("hello");
	strv.PushBack("world");
	for (size_t i = 0; i < strv.Size(); ++i)
	{
		cout << strv[i] << " ";
	}

}

void TestVector2()
{
	//迭代器测试
	vc::Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);

	vc::Vector<int>::Iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//使用迭代器修改
	vc::Vector<int>::Iterator iit = v.begin();

	while (iit != v.end())
	{
		(*iit) *= 2;
		cout << *iit << " ";
		++iit;
	}
	cout << endl;
}

//Capacity/reserve
void TestVector3()
{
	//从1二倍增长
	vc::Vector<int> bar;
	size_t capacity = bar.Capacity();
	cout << "capacity: " << capacity << endl;

	cout << "growing:" << endl;
	for (int i = 0; i < 100; i++)
	{
		bar.PushBack(i);
		if (capacity != bar.Capacity())
		{
			capacity = bar.Capacity();
			cout << "changed: " << capacity << endl;
		}
	}

	//reserve
	vc::Vector<int> bar1;
	size_t capacity1 = bar1.Capacity();
	bar1.Reserve(100);
	cout << "capacity1: " << capacity1 << endl;

	cout << "growing:" << endl;
	for (int i = 0; i < 100; i++)
	{
		bar1.PushBack(i);
		if (capacity1 != bar1.Capacity())
		{
			capacity1 = bar1.Capacity();
			cout << "changed: " << capacity1 << endl;
		}
	}

}

//resize
void TestVector4()
{
	vc::Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	v.Resize(3);
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.Resize(10, 6);
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.Resize(100, 6);
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;


}

//find/insert/erase
void TestVector5()
{
	vc::Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	

	//find
	vc::Vector<int>::Iterator pos = find(v.begin(), v.end(), 3);
	vc::Vector<int>::Iterator pos1 = find(v.begin(), v.end(), 4);


	//insert
	v.Insert(pos, 3);
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//erase
	v.Erase(pos1);
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;


}

//operator[]/=
void TestVector6()
{
	vc::Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	v[0] = 10;
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	vc::Vector<int> v1;
	v1 = v;
	for (const auto& e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

}

//out of use Iterator
void TestVector7()
{
	vc::Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	v.PushBack(6);
	vc::Vector<int>::Iterator it = v.begin();
	//迭代器失效
	//while (it != v.end())
	//{
	//	if (*it % 2 == 0)
	//	{
	//		v.Erase(it);
	//		it++;
	//	}
	//}

	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.Erase(it);

		}
		else
			it++;
	}
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{

#if 0
    test_vector1();
	test_vector2();
	test_vector3();
	test_vector4();
#endif

	//TestVector1();
	//TestVector2();
	//TestVector3();
	//TestVector4();
	//TestVector5();
	//TestVector6();
	TestVector7();

	system("pause");
	return 0;
}