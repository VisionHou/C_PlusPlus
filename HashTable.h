#pragma once
typedef int DataType;
typedef enum{EXIST,EMPTY,DELETE}State;
#define MAXSIZE 10

typedef struct HTElem {
	DataType _data;
	State _state;//��Ԫ�ص�ǰ״̬
}HtElem;//ÿһ��Ԫ��

typedef struct HashTable {
	HtElem _array[MAXSIZE];//�ռ��С
	int _size;//��ϣ������ЧԪ�ظ���
	int _total;//��ϣ����Ԫ�ظ���(��Ч��ɾ��)
	int _IsLineDetective;//�Ƿ�Ϊ����̽��
}HashTable,HT;

//��ʼ��
void HashTableInit(HT* ht, int IsLineDetective);

//����Ԫ��
void HashTableInsert(HT* ht, DataType data);

//ɾ��Ԫ��
void HashTableDelete(HT* ht, DataType data);

//����
int HashTableFind(HT* ht, DataType data);

//��ϣ������ЧԪ�ظ���
int HashTableSize(HT* ht );

//�п�
int HashTableEmpty(HT* ht);


