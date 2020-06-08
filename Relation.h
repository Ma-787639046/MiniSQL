#pragma once
#include "Table.h"

// Relation.h
// Created by MGY on 2020.06.08

// Relation.h���ڴ洢Where�������ҵĹ�ϵ����ֵ
// API�ڵ���RecordManager����Where��������ʱ�����Դ���һ��~���Relation�ṹ��
// Relation�ṹ�� = Ŀ��Attribute Name + Attribute Type(INT, FLOAT, STRING) + sign + key
// ���� where salary > 3.1 �У�
// Attribute Name = "salary"
// Attribute Type = FLOAT
// sign = GREATER
// key.FLAOT_VALUE = 3.1

// Sign��ʾWhere�����еķ���
typedef enum {
    NOT_EQUAL,
    EQUAL,
    LESS,
    LESS_OR_EQUAL,
    GREATER_OR_EQUAL,
    GREATER
} Sign_;

class Relation {
public:
    std::string attributeName;
    AttrType attributeType;
    Sign_ sign;
    key_ key;
};

