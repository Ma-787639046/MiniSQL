#include "Table.h"

Attribute::Attribute()
{
	this->attributeNumber = 0;
	this->primary_key = -1;
	for (int i = 0; i < 32; i++) {
		this->type[i] = INT;
		this->unique[i] = false;
		this->index[i] = false;
	}
}

Attribute::Attribute(const Attribute& attr)
{
	this->attributeNumber = attr.attributeNumber;
	for (int i = 0; i < 32; i++) this->type[i] = attr.type[i];
	for (int i = 0; i < 32; i++) this->name[i] = attr.name[i];
	for (int i = 0; i < 32; i++) this->unique[i] = attr.unique[i];
	this->primary_key = attr.primary_key;
	for (int i = 0; i < 32; i++) this->index[i] = attr.index[i];
}

Index::Index()
{
	this->indexNumber = 0;
	for (int i = 0; i < 32; i++) this->num[i] = 0;
}

Index::Index(const Index& index)
{
	this->indexNumber = index.indexNumber;
	for (int k = 0; k < index.indexNumber; k++) {
		this->num[k] = index.num[k];
		this->indexname[k] = index.indexname[k];
	}
	for (int k = index.indexNumber; k < 32; k++) {
		this->num[k] = 0;
	}
}

Tuple::Tuple(const Tuple& tuple)
{
	for (int i = 0; i < tuple.tuple.size(); i++) {
		this->tuple.push_back(tuple.tuple[i]);
	}
	this->valid = tuple.valid;
}

void Tuple::addTuple(key_ tuple)
{
	this->tuple.push_back(tuple);
}

std::vector<key_>& Tuple::getTuple()
{
	return this->tuple;
}


void Tuple::showTuple(Attribute& attribute)
{
	for (int i = 0; i < tuple.size(); i++) {
		switch (attribute.type[i])
		{
		case INT:	std::cout << tuple[i].INT_VALUE << "\t";
			break;
		case FLOAT:	std::cout << tuple[i].FLOAT_VALUE << "\t";
			break;
		case STRING:	std::cout << tuple[i].STRING_VALUE << "\t";
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;
}

int Tuple::size()
{
	return (int)this->tuple.size();
}

bool Tuple::getValid()
{
	return this->valid;
}

void Tuple::setValid(bool status)
{
	this->valid = status;
}

std::string Tuple::encodeTuple()
{
	std::stringstream s;
	int n = size();	//4bytes��Tuple size:n
	s.write((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++) {
		s.write((char*)&(tuple[i].INT_VALUE), sizeof(int));	//д��INT
		s.write((char*)&(tuple[i].FLOAT_VALUE), sizeof(float));	//д��FLOAT
		int string_len = tuple[i].STRING_VALUE.size();
		s.write((char*)&string_len, sizeof(int));	//д��4 bytes sizeof(STRING_VALUE)
		s.write(tuple[i].STRING_VALUE.c_str(), string_len);	//д��STRING_VALUE
	}
	return s.str();
}

void Tuple::decodeTuple(std::string& string)
{
	int n;
	std::stringstream s;
	s << string;
	s.read((char*)&n, sizeof(int));	//��ȡ4bytes��Tuple size:n
	for (int i = 0; i < n; i++) {
		key_ key;
		s.read((char*)&(key.INT_VALUE), sizeof(int)); //��ȡINT
		s.read((char*)&(key.FLOAT_VALUE), sizeof(float)); //��ȡFLOAT
		int string_len;
		s.read((char*)&string_len, sizeof(int));	//��ȡ4 bytes sizeof(STRING_VALUE)
		char* value = (char*)malloc(string_len + 1);
		memset(value, 0, string_len + 1);
		s.read(value, string_len);	//��ȡSTRING_VALUE
		key.STRING_VALUE = value;
		addTuple(key);
	}
	string = s.str();	//���ʣ���string��������һ��decode
}

Table::Table(const Table& table)
{
	this->TableName = table.TableName;
	this->attribute = table.attribute;
	this->index = table.index;
	for (int i = 0; i < table.Record.size(); i++) {
		this->Record.push_back(table.Record[i]);
	}
}

Table::Table(std::string TableName, Attribute attribute)
{
	this->TableName = TableName;
	this->attribute = attribute;
}

bool Table::setIndex(int index, std::string index_name)
{
	//�ж�ԭIndex�Ƿ���������ͬ��ͬ�����
	for (int i = 0; i < this->index.indexNumber; i++) {
		if (index == this->index.num[i]) {
			std::cout << "Index����ʧ�ܣ���Ϊ��������ѱ�������Index��" << std::endl;
			return false;
		}
	}
	for (int i = 0; i < this->index.indexNumber; i++) {
		if (index_name == this->index.indexname[i]) {
			std::cout << "Index����ʧ�ܣ���ΪIndex�������ظ�" << std::endl;
			return false;
		}
	}
	//���ظ�index����������ʼ���index
	this->index.num[this->index.indexNumber] = index;
	this->index.indexname[this->index.indexNumber] = index_name;
	this->index.indexNumber++;
	return true;	//����true�����óɹ�
}

bool Table::dropIndex(std::string index_name)
{
	//����indexname�����index_name��λ��
	int i = 0;
	for (i = 0; i < this->index.indexNumber; i++) {
		if (this->index.indexname[i] == index_name) break;
	}
	//û���ҵ���Ӧ��index_name������
	if (i >= this->index.indexNumber) {
		std::cout << "�޷�ɾ��Index��û���ҵ���Ϊ " << index_name << " ��Index" << std::endl;
		return false;
	}
	//�ҵ���Ӧ��index_name����ĩβԪ�ظ������index��popĩβԪ�أ���ɾ�����index
	index.num[i] = index.num[this->index.indexNumber - 1];
	index.indexname[i] = index.indexname[this->index.indexNumber - 1];
	this->index.indexNumber--;
	return true;
}

void Table::showTable()
{
	for (int i = 0; i < attribute.attributeNumber; i++) {
		std::cout << attribute.name[i] << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < Record.size(); i++) {
		Record[i].showTuple(attribute);
	}
}

void Table::showTable(int limit)
{
	for (int i = 0; i < attribute.attributeNumber; i++) {
		std::cout << attribute.name[i] << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < Record.size() && i < limit; i++) {
		Record[i].showTuple(attribute);
	}
}

