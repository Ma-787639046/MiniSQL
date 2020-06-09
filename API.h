//
//	API.h
//	Created by MGY on 2020/06/09
//

/*
	API����װ�ײ��3��Manager�ĸ��������ṩ�ӿڸ�����Interpreterʹ��
		API�������쳣���쳣�Ĳ����ɵײ�Manager���У�
		API�������쳣���쳣�Ĵ����ɶ���Interpreter���С�
*/
#pragma once

#include "Table.h"
#include "RecordManager.h"
#include "IndexManager.h"

class API {
public:
	//createTable(): ������
	//���룺������
	//		���ԣ����������ơ����͡��Ƿ�unique��������û��������Ϊ-1��������д��Ӧ�±ꡣ
	//												ע������һ����unique�ģ����Ƿ���index��
	//		��������������������������Ӧ�ڼ�������(����һ��������)
	//�쳣��������ڱ�����ͬ�ı����׳�table_name_conflict�쳣 
	void createTable(std::string table_name, Attribute attribute, Index index);

	//dropTable()��ɾ����
	//���룺����
	//�쳣�������ڣ��׳�table_not_exist
	void dropTable(std::string table_name);

	//selectRecord()��������relation����ļ�¼�������ش��м�¼�ı�
	//���룺��������ϵ���飺��ϵ1 and ��ϵ2 and ��ϵ3 ����
	//						һ����ϵ = ������ + �������ͣ�INT/FLOAT/STRING��+ ���ţ�>, >=, != ������+ ֵ
	//						���磺relation1 = "salary", FLOAT, GREATER_OR_EQUAL, 3000.0f
	//��������м�¼�ı�
	//�쳣��1��table_name��Ӧ�ı�����catalog�в����ڣ��׳�table_not_exist
	//		2��relation�У���ΪAttribute name��Attribute�����ڣ����׳�attribute_not_exist
	//		3��Attribute�������������relation ��ƥ�䣬�׳�key_type_conflict
	Table selectRecord(std::string table_name, std::vector<Relation> relation);

	//deleteRecord()��ɾ�����з���relation�ļ�¼��������ɾ��������
	//���룺��������ϵ���飺��ϵ1 and ��ϵ2 and ��ϵ3 ����
	//�����ɾ��������
	//�쳣��1��table_name��Ӧ�ı�����catalog�в����ڣ��׳�table_not_exist
	//		2��Attribute�������������relation ��ƥ�䣬�׳�key_type_conflict
	int deleteRecord(std::string table_name, std::vector<Relation> relation);

	//insertRecord()������Ϊtable_name�еı�񣬲���һ��tuple��¼
	//���룺������tuple
	//�������
	//�쳣����1��table_name��Ӧ�ı�����catalog�в����ڣ��׳�table_not_exist
	//			2�������ظ����������׳�primary_key_conflict
	//			3������unique�������ظ���ֵ���׳�unique_conflict�쳣
	//ע�⣺�������������tuple���͡������Ƿ���Attributeƥ�䡣�������ط���Interpreterִ�У�������
	void insertRecord(std::string table_name, Tuple& tuple);

private:
	CatalogManager catalog_manager;
	RecordManager record_manager;
};