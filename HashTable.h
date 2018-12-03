#pragma once
typedef int DataType;
typedef enum{EXIST,EMPTY,DELETE}State;
#define MAXSIZE 10

typedef struct HTElem {
	DataType _data;
	State _state;//该元素当前状态
}HtElem;//每一格元素

typedef struct HashTable {
	HtElem _array[MAXSIZE];//空间大小
	int _size;//哈希表中有效元素个数
	int _total;//哈希表中元素个数(有效和删除)
	int _IsLineDetective;//是否为线性探测
}HashTable,HT;

//初始化
void HashTableInit(HT* ht, int IsLineDetective);

//插入元素
void HashTableInsert(HT* ht, DataType data);

//删除元素
void HashTableDelete(HT* ht, DataType data);

//查找
int HashTableFind(HT* ht, DataType data);

//哈希表中有效元素个数
int HashTableSize(HT* ht );

//判空
int HashTableEmpty(HT* ht);


