#include<iostream>
#include<windows.h>
#include<set>
#include<map>
#include<string>

using std::cout;
using std::endl;

void TestSet()
{
	using std::set;
	int array[] = { 1,7,9,0,5,4,3,2,1,4,8,8,6 };
    set<int> s(array, array + sizeof(array) / sizeof(array[0]));//去重
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;

	cout << s.count(8) << endl;
	set<int>::iterator itfind = s.find(7);
	s.erase(itfind);//删除后重置itfind
	itfind = s.begin();
	while (itfind != s.end())
	{
		cout << *itfind << " ";
		itfind++;
	}
	cout << endl;

	s.erase(7);
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	/*set<int> s;
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		s.insert(array[i]);
	}

	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;*/
}

void TestMultiset()
{
	std::multiset<int> ms;
	ms.insert(3);
	ms.insert(3);
	ms.insert(3);
	ms.insert(7);
	ms.insert(9);
	std::multiset<int>::iterator it = ms.begin();
	for (; it != ms.end(); it++)
		cout << *it << " ";
	cout << endl;

	it = ms.find(3);
	//it = ms.find(19);崩溃
	ms.erase(it);
	it = ms.begin();
	for (; it != ms.end(); it++)
		cout << *it << " ";
	cout << endl;

	ms.erase(18);//没有就不删
	it = ms.begin();
	for (; it != ms.end(); it++)
		cout << *it << " ";
	cout << endl;
}

void TestMap()
{
/*
	std::map<std::string, std::string> dict;
	dict.insert(std::pair<std::string, std::string>("apple", "苹果"));
	dict.insert(std::pair<std::string, std::string>("banana", "香蕉"));
	dict.insert(std::pair<std::string, std::string>("peach", "桃子"));
	dict.insert(std::pair<std::string, std::string>("watermelon", "西瓜"));

	std::map<std::string, std::string>::iterator it = dict.begin();
	for (; it != dict.end(); it++)
	{
		cout << it->first << "->" << it->second << endl;
	}

	*/
	typedef std::map<std::string, std::string> Dict;
	Dict dict;
	dict.insert(std::pair<std::string, std::string>("apple", "苹果"));
	dict.insert(std::pair<std::string, std::string>("banana", "香蕉"));
	dict.insert(std::pair<std::string, std::string>("peach", "桃子"));
	dict.insert(std::pair<std::string, std::string>("watermelon", "西瓜"));

	auto it = dict.begin();
	for (; it != dict.end(); it++)
	{
		cout << it->first << "->" << it->second << endl;
	}


#if 0
	std::map<char, int> mymap;
	std::map<char, int>::iterator it;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	it = mymap.find('b');
	mymap.erase(it);                   // erasing by iterator

	mymap.erase('c');                  // erasing by key

	it = mymap.find('e');
	mymap.erase(it, mymap.end());    // erasing by range

	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		cout << it->first << " => " << it->second << endl;

#endif
}

void TestMultimap()
{
	/*	std::multimap<std::string, std::string> name;
	name.insert(std::pair<std::string, std::string>("杨帆","山西"));
	name.insert(std::pair<std::string, std::string>("杨帆", "长沙"));
	name.insert(std::pair<std::string, std::string>("杨帆", "北京"));
	name.insert(std::pair<std::string, std::string>("杨帆", "天津"));

	std::multimap<std::string, std::string>::iterator it = name.begin();
	for (; it != name.end();it++)
	{
		cout << it->first << " => " << it->second << endl;
	}*/

	typedef std::multimap<std::string, std::string> Names;
	Names name;
	typedef std::pair<std::string, std::string> mk_pair;
	name.insert(mk_pair("杨帆","山西"));
	name.insert(mk_pair("杨帆", "长沙"));
	name.insert(mk_pair("张伟", "长沙"));
	name.insert(mk_pair("李伟", "北京"));
	name.insert(mk_pair("杨帆", "天津"));

	auto it = name.begin();

	for (;it!=name.end();it++)
	{
		cout << it->first << " => " << it->second << endl;
	}

	cout << name.count("杨帆") << endl;

	it = name.find("杨帆");
	name.erase(it);
	it = name.begin();
	for (; it != name.end(); it++)
	{
		cout << it->first << " => " << it->second << endl;
	}
}

int main()
{
	//TestSet();//排序加去重
	//TestMultiset();//排序
	//TestMap();//k-v
	TestMultimap();
	system("pause");
	return 0;
}