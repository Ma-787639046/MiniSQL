#pragma once

#include <iostream>
#include "Table.h"
#include "BufferManager.h"
#include "const.h"
#include "exceptions.h"

/* 
	Ϊ����CatalogManagerͨ��BufferManager����block�ڵĸ���table��
	����Catalog�࣬��ֱ������TableName��attribute��index��
	Catalog���൱��Table���һ�����ȵļ򻯰棬��Ҫ����CatalogManager
	�ڲ������ݹ���
*/
class Catalog {
public:
	std::string TableName;	//����
	Attribute attribute;	//�������
	Index index;	//���������Ϣ
};

namespace catalog {
	BufferManager buffer(CATALOG_FILEPATH, 256);	//�ļ�·��CATALOG_FILEPATH��������Ԥ��256��ҳ��ҳ�ɶ�̬���䣩
}

class CatalogManager {
public:
	//createTable(): ������
	//���룺���������ԣ�����
	//�쳣��������ڱ�����ͬ�ı����׳�table_name_conflict�쳣 
	void createTable(std::string table_name, Attribute attribute, Index index);

	//havetable()���ж��Ƿ�������Ϊtable_name��table����
	//���룺����
	//�����true��false
	bool havetable(std::string table_name);

	//findTableBlock(): �ҵ�������Table���ڵ�block_id
	//���룺����
	//�����Table���ڵ�block_id��û���򷵻�-1	����������havetable��ǿ���棩
	int findTableBlock(std::string table_name);

	//dropTable()��ɾ����
	//���룺����
	//�쳣�������ڣ��׳�table_not_exist
	void dropTable(std::string table_name);

	//getCatalog()����ȡ��Ϊtable_name�ı�ı��������ԡ�������Ϣ�������Catalog������
	//���룺����
	//�쳣�������ڣ��׳�table_not_exist
	Catalog getCatalog(std::string table_name);

	//showCatalog()����ӡ��Ϊtable_name�ı�ı��������ԡ�������Ϣ
	//�쳣�������ڣ��׳�table_not_exist
	void showCatalog(std::string table_name);

	//haveAttribute():�ж���Ϊtable_name�ı��Ƿ������Ϊattribute_name������
	//�쳣�������ڣ��׳�table_not_exist��
	bool haveAttribute(std::string table_name, std::string attribute_name);

	//getAttribute()����ȡ��Ϊtable_name�ı������
	//�쳣�������ڣ��׳�table_not_exist��
	Attribute getAttribute(std::string table_name);

	//addIndex()������Ϊtable_name�ı�Ϊ��Ϊattribute_name�����������Ϊindex_name��������¼
	//�쳣��1�������ڣ��׳�table_not_exist��2�����Բ����ڣ��׳�attribute_not_exist��
	//		3�������Ѿ���index���׳�index_exist_conflict��4��index�����������ֵ���׳�index_full��index num����Ϊ32�����Գ����ˣ���
	//		5�����������ڣ��׳�index_name_conflict; 6,���Բ�unique���׳�attribute_not_unique
	void addIndex(std::string table_name, std::string attribute_name, std::string index_name);

	//findAttributeThroughIndex()������Ϊtable_name�ı��ڣ�����index_name����Ӧ�����Ե�������
	//���룺������������
	//�����������
	//�쳣��1�������ڣ��׳�table_not_exist��2�����������ڣ��׳�index_not_exist
	std::string findAttributeThroughIndex(std::string table_name, std::string index_name);

	//dropIndex()������Ϊtable_name�ı��ڣ�ɾ����Ϊindex_name������
	//���룺������������
	//�쳣��1�������ڣ��׳�table_not_exist��2�����������ڣ��׳�index_not_exist
	void dropIndex(std::string table_name, std::string index_name);

	//loadCatalogFromPage()����ҳ��Ϊpage_id��ҳ������Catalog��һ��vector
	//���룺ҳ��
	//���أ�vector<Catalog>
	std::vector<Catalog> loadCatalogFromPage(int page_id);

	//catalogSize()������catalog���ܴ�С�����ж����page�ܷ����㹻�ռ�д���µ�catalog��Ϣ
	//���룺<vector>catalog
	//���أ�catalogд��ʱ���ܴ�С
	int catalogSize(std::vector<Catalog>& catalog);

	//flushCatalogToPage()����catalogд��page_idҳ��ʹ��ǰע��catalog���ܴ�С
	//���룺catalog��page_id
	void flushCatalogToPage(std::vector<Catalog>& catalog, int page_id);
};

