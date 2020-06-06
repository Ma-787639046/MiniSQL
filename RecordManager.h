#pragma once

#include <sstream>
#include "BufferManager.h"
#include "Table.h"
//	std::vector<key_> tuple;	//һ��tuple��Tuple = (key1, key2, key3 ����) 
//	std::vector<Tuple> Record;	//��ļ�¼����������Tuple

//Record Manager��������¼�������ݵ������ļ�����Ҫ����Ϊʵ�������ļ��Ĵ�����ɾ�����ɱ�Ķ�����
//ɾ�����𣩡���¼�Ĳ��롢ɾ������Ҳ������������ṩ��Ӧ�Ľӿڡ����м�¼�Ĳ��Ҳ���Ҫ���ܹ�֧�ֲ���
//�����Ĳ��Һʹ�һ�������Ĳ��ң�������ֵ���ҡ�����ֵ���Һ�������ң���`

//�����ļ���һ���������ݿ���ɣ����СӦ�뻺�������С��ͬ��һ�����а���һ����������¼��Ϊ����
//����ֻҪ��֧�ֶ�����¼�Ĵ洢���Ҳ�Ҫ��֧�ּ�¼�Ŀ��洢��



class RecordManager {
public:
	void createTableFile(std::string table_name);	//������Record�ļ�
	void dropTableFile(std::string table_name);		//ɾ����Record�ļ�
	
	std::vector<Tuple> loadTuples(std::string table_name);	//��table_name�����е�tuplesװ�������vector
private:
	void setBlockStringSize(int size, std::string& s);		//����block�����ÿռ��С
	void setTupleStringSize(int size, std::string& s);		//����Tuple�ĸ���
	std::string createFormatedBlockString();	//����һ������ˢ��block��string
	int getBlockStringSize(std::string s);	//��ȡBlockString�����ÿռ���ܴ�С
	int getTupleStringSize(std::string s);	//��ȡBlock��Tuple�ĸ���
	void writeTupleString(std::string& s, Tuple& tuple);	//��s��д��һ��Tuple
	std::vector<Tuple> readTupleString(std::string& s);	//��ȡTuple��һ��vector��

	void flushToBlock(std::string s, int block_id, std::string table_name);	//��Record��¼ˢ������ļ���Ӧ��block��
	std::string loadBlockString(int block_id, std::string table_name);	//��һ��blockװ����string��
};