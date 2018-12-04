#pragma once

#define MAXSIZE 10
//typedef char* DataType;
typedef int DataType;

typedef enum { EMPTY ,EXIST, DELETE }State;



typedef struct HTElem {
	DataType _data;
	State _state;//��Ԫ�ص�ǰ״̬
}HtElem;//ÿһ��Ԫ��

typedef struct HashTable {
	HtElem* _array;
	int _size;//��ϣ������ЧԪ�ظ���
	int _capacity;//����
	int _IsLineDetective;//�Ƿ�Ϊ����̽��
}HashTable, HT;

//��ʼ��
void HashTableInit(HT* ht, int capacity, int IsLineDetective);

//����Ԫ��
void HashTableInsert(HT* ht, DataType data);

//ɾ��Ԫ��
void HashTableDelete(HT* ht, DataType data);

//����
int HashTableFind(HT* ht, DataType data);

//��ϣ������ЧԪ�ظ���
int HashTableSize(HT* ht);

//�п�
int HashTableEmpty(HT* ht);

//����
void HashTableDestroy(HT* ht);
