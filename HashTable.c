#include"HashTable.h"
#include<assert.h>
#include<stdio.h>
#include<Windows.h>

void HashTableInit(HT* ht, int IsLineDetective)
{
	int i = 0;
	for (; i < MAXSIZE; ++i)
	{
		ht->_array[i]._state = EMPTY;
	}

	ht->_size = 0;
	ht->_total = 0;
	ht->_IsLineDetective = IsLineDetective;
}

int HashAddFun(DataType data)
{
	return data% MAXSIZE;//除留余数
}

//线性探测
int DetectiveLine(int hashAdd)
{
	hashAdd++;
	if (hashAdd == MAXSIZE )
		hashAdd = 0;

	return hashAdd;
}

//二次探测
int Detective2(int hashAdd,int i)
{
	hashAdd = hashAdd + 2 * i + 1;
	if (hashAdd >= MAXSIZE)
		hashAdd %= MAXSIZE;

	return hashAdd;
}
void HashTableInsert(HT* ht, DataType data)
{
	int i = 0;
	assert(ht);
	if (ht->_total == MAXSIZE)
		return;

	//计算哈希地址
	int hashAdd = 0;
	hashAdd = HashAddFun(data);

	while (ht->_array[hashAdd]._state != EMPTY)
	{
		if (ht->_array[hashAdd]._state == EXIST)
		{
			if (ht->_array[hashAdd]._data == data)
				return;
		}

		if (ht->_IsLineDetective)
			hashAdd=DetectiveLine(hashAdd);
		else
			hashAdd=Detective2(hashAdd,++i);
	}

	//插入元素
	ht->_array[hashAdd]._data = data;
	ht->_array[hashAdd]._state = EXIST;
	ht->_size++;
	ht->_total++;
}

void HashTableDelete(HT* ht, DataType data)
{
	assert(ht);

	int del = -1;
		del = HashTableFind(ht,data);
	if (del != -1)
	{
		ht->_array[del]._state = DELETE;
		ht->_size--;
	}
}

int HashTableFind(HT* ht, DataType data)
{
	assert(ht);
	int i = 0;
	int hashAdd = -1;
	int start = -1;

	hashAdd = HashAddFun(data);
	start = hashAdd;

	while (ht->_array[hashAdd]._state != EMPTY)
	{
		if (ht->_array[hashAdd]._state == EXIST)
		{
			if (ht->_array[hashAdd]._data == data)
				return hashAdd;
		}
		if (ht->_IsLineDetective)
		{
			hashAdd=DetectiveLine(hashAdd);

			//找了一圈没有找到
			if (hashAdd == start)
				return -1;
		}
		else
			Detective2(hashAdd, ++i);
	}

	return -1;
}

int HashTableSize(HT* ht)
{
	assert(ht);
	return ht->_size;
}

int HashTableEmpty(HT* ht)
{
	assert(ht);
	return ht->_size == 0;
}

/////////////////////////////////

void TestHashTable()
{
	HashTable ht;
	HashTableInit(&ht, 1);
	HashTableInsert(&ht, 23);
	HashTableInsert(&ht, 33);
	HashTableInsert(&ht, 12);
	HashTableInsert(&ht, 28);
	HashTableInsert(&ht, 19);
	HashTableInsert(&ht, 20);
	printf("size=%d\n", HashTableSize(&ht));

	int find = HashTableFind(&ht, 20);
	if (find == -1)
		printf("can't Find...\n");
	else
		printf("find it!!!\n");


	find = HashTableFind(&ht, 33);
	if (find == -1)
		printf("can't Find...\n");
	else
		printf("find it!!!\n");

	HashTableDelete(&ht, 33);
	printf("size=%d\n", HashTableSize(&ht));
	find = HashTableFind(&ht, 33);
	if (find == -1)
		printf("can't Find...\n");
	else
		printf("find it!!!\n");

	int ret = 0;
	ret = HashTableEmpty(&ht);
	if(ret!=0)
		printf("is empty... ");
	else
		printf("not empty... ");

}

int main()
{
	TestHashTable();
	system("pause");
	return 0;
}