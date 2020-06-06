#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/*
һ��Table��
	TableName
	Attribute��int��float��string����
	Record: Tuple1 (1, 2.1, "ABC" ����)
			Tuple2 (2, 1.1, "BC" ����)
			����
	Index:(IndexName, ��Ӧ�ڼ���Attribute)
*/

/* ���涨����Attribute, Attribute�����32�� */
typedef enum {
	INT,
	FLOAT,
	STRING
} AttrType;

class Attribute {
public:
	Attribute();
	Attribute(const Attribute& attr);	//�������캯��
	int attributeNumber;	//attribute����
	AttrType type[32];	//���ÿ�����Ե�����
	std::string name[32];	//���ÿ�����Ե�����
	bool unique[32];	//�ж�ÿ�������Ƿ�unique����Ϊtrue
	int primary_key;	//�ж��Ƿ��������,-1Ϊ�����ڣ�������Ϊ����������λ��
	bool index[32];	//��Ӧ����ֵ�Ƿ��������
};

/* ���涨����Index */
class Index {
public:
	Index();
	Index(const Index& index);
	int indexNumber;	//index�ĸ���
	int num[32];	//ÿ��index��Attribute��name�������ǵڼ���
	std::string indexname[32]; //ÿ��index������
};

/* ���涨����Tuple��record�ɶ���Tuple���� */
//struct����һ��key��Tuple = (key1, key2, key3 ����)
//ʹ��key֮ǰ��������ͨ��Attribute.type[i]ȷ��key��int��float������string
//��������union���޷�ʹ��string����ֱ����char[255]̫�˷ѿռ䣬�����structǶ��
//����key����union����ʡ�ռ�
class key_ {
public:
	int INT_VALUE;
	float FLOAT_VALUE;
	std::string STRING_VALUE;
};

//	����һ��Tuple��Tuple = (key1, key2, key3 ����)
class Tuple {
public:
	Tuple() :valid(false) {};	//Ĭ�Ϲ��캯����valid=false
	Tuple(const Tuple& tuple);  //�������캯��
	void addTuple(key_ tuple);	//������Tuple��push_backһ��ֵ
	std::vector<key_>& getTuple();	//����Tuple������
	void showTuple(Attribute& attribute);	//��ʾTuple���������ݣ���Ҫ������Ӧ��Attribute 
	int size();	//����Tuple����
	bool getValid();	//����Tuple�Ƿ����
	void setValid(bool status);	//����Tuple�Ƿ����
	std::string encodeTuple();	//��Tupleת��Ϊstring��ʽ�����㴢�档
								//Tuple = 4bytes��Tuple size:n + (4 bytes INT + 4 bytes FLOAT + 4 bytes sizeof(STRING_VALUE) + STRING_VALUE)*n
	void decodeTuple(std::string& string);	//��string��ʽ��Tuple���룬ʣ���string��أ���������ʹ��decodeTuple
private:
	std::vector<key_> tuple;	//һ��tuple��Tuple = (key1, key2, key3 ����) 
	bool valid;	//	����Tuple�Ƿ����
};

/* ���涨��Table��Table����TableName��Attribute��Record��Index*/
class Table {
public:
	std::string TableName;	//����
	Attribute attribute;	//�������
	std::vector<Tuple> Record;	//��ļ�¼����������Tuple
	Index index;	//���������Ϣ

	Table() {};	//Ĭ�Ϲ��캯��
	Table(const Table& table);	//�������캯��
	Table(std::string TableName, Attribute attribute);	//��TableName��attribute�����ձ�

	bool setIndex(int index, std::string index_name);	//��������������Ҫ����������Attribute�ı�ţ��Լ����������֣��ɹ�����true,ʧ�ܷ���false
	bool dropIndex(std::string index_name);	//ɾ�����������뽨�������������֣��ɹ�����true,ʧ�ܷ���false

	void showTable(); //��ʾtable����
	void showTable(int limit);	//��ʾ����limit������
};