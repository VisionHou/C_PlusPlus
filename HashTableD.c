#include<assert.h>
#include"HashTableD.h"
#include<stdio.h>
#include<Windows.h>


#define PRIME_COUNT 28

const unsigned long _PrimeList[PRIME_COUNT] =
{
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

size_t GetNextPrime(size_t capacity)
{
	int i = 0;
	for (; i < PRIME_COUNT; ++i)
	{
		if (_PrimeList[i] > capacity)
			return _PrimeList[i];
	}

	return _PrimeList[PRIME_COUNT - 1];
}

void HashTableInit(HT* ht, int capacity, int IsLineDetective)
{
	int i = 0;
	capacity = GetNextPrime(capacity);
	ht->_array = (HtElem*)malloc(capacity * sizeof(HtElem));
	if (ht->_array==NULL)
	{
		assert(0);
		return;
	}
	for (; i < capacity; ++i)
		ht->_array[i]._state = EMPTY;

	ht->_capacity = capacity;
	ht->_size = 0;
	ht->_IsLineDetective = IsLineDetective;
}


int HashAddFun(DataType data)
{
	return data % MAXSIZE;//除留余数
}

//线性探测
int DetectiveLine(int hashAdd)
{
	hashAdd++;
	if (hashAdd == MAXSIZE)
		hashAdd = 0;

	return hashAdd;
}

//二次探测
int Detective2(int hashAdd, int i)
{
	hashAdd = hashAdd + 2 * i + 1;
	if (hashAdd >= MAXSIZE)
		hashAdd %= MAXSIZE;

	return hashAdd;
}

void Swap(HT* htL,HT* htR)
{
	assert(htL);
	assert(htR);
	int tmp ;

	//array
	tmp = (int)htL->_array;
	htL->_array = htR->_array;
	htR->_array = (HtElem*)tmp;

	//size
	tmp = htL->_size;
	htL->_size = htR->_size;
	htR->_size = tmp;

	//capacity
	tmp = htL->_capacity;
	htL->_capacity = htR->_capacity;
	htR->_capacity = tmp;

	//size
	tmp = htL->_IsLineDetective;
	htL->_IsLineDetective = htR->_IsLineDetective;
	htR->_IsLineDetective = tmp;

}

//容量检测
int CheckCapacity(HT *ht)
{
	assert(ht);
	if (ht->_size*10/ ht->_capacity >= 7)//负载因子0.7
	{
		//开辟新空间
		int newcapacity= GetNextPrime(ht->_capacity);
		HT newht;
		HashTableInit(&newht, newcapacity, ht->_IsLineDetective);

		//拷贝元素
		for (int i = 0; i < ht->_size; ++i)
		{
			if (ht->_array[i]._state == EXIST)
				HashTableInsert(&newht, ht->_array[i]._data);
		}

		Swap(ht, &newht);
		HashTableDestroy(&newht);
	}
	return 1;
}

//插入元素
void HashTableInsert(HT* ht, DataType data)
{
	int hashAdd = 0;
	int i = 0;

	if (!CheckCapacity(ht))
		return;

	hashAdd = HashAddFun(data);
	while (ht->_array[hashAdd]._state != EMPTY)
	{
		if (ht->_array[hashAdd]._state == EXIST)
		{
			if (ht->_array[hashAdd]._data == data)
				return;
		}

		if (ht->_IsLineDetective)
			hashAdd = DetectiveLine(hashAdd);
		else
			hashAdd = Detective2(hashAdd, ++i);
	}

	//插入元素
	ht->_array[hashAdd]._data = data;
	ht->_array[hashAdd]._state = EXIST;
	ht->_size++;
}

void HashTableDelete(HT* ht, DataType data)
{
	assert(ht);
	int ret = -1;
	ret = HashTableFind(ht, data);
	if (ret == -1)
		return;

	//删除元素
	ht->_array[ret]._state = DELETE;
	ht->_size--;
}

int HashTableFind(HT* ht, DataType data)
{
	int hashAdd = -1;
	int Start = -1;
	int i = 0;

	hashAdd = HashAddFun(data);
	while (ht->_array[hashAdd]._state!=EMPTY)
	{
		if (ht->_array[hashAdd]._state == EXIST)
		{
			if(ht->_array[hashAdd]._data == data)
				return hashAdd;
		}

		if (ht->_IsLineDetective)
		{
			hashAdd = DetectiveLine(hashAdd);
			if (hashAdd == Start)
				return -1;//找了一圈没有找到
		}
		else
			hashAdd = Detective2(hashAdd,++i);
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

void HashTableDestroy(HT* ht)
{
	assert(ht);
	if (ht->_array)
	{
		free(ht->_array);
		ht->_size = 0;
		ht->_capacity = 0;
	}
}

void TestHashTableD()
{
	HashTable ht;
	int i = 1;
	HashTableInit(&ht, 10, 1);
	for (; i < 7; ++i)
		HashTableInsert(&ht, i);

	printf("size=%d\n", HashTableSize(&ht));

	int find = HashTableFind(&ht, 20);
	if (find == -1)
		printf("can't Find...\n");
	else
		printf("find it!!!\n");

	 find = HashTableFind(&ht, 4);
	if (find == -1)
		printf("can't Find...\n");
	else
		printf("find it!!!\n");

	HashTableInsert(&ht, 33);
	HashTableInsert(&ht, 12);

	printf("size=%d\n", HashTableSize(&ht));

}

int main()
{
	TestHashTableD();
	system("pause");
	return 0;
}