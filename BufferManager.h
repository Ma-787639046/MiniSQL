//
//  BufferManager.h
//  Created by MGY on 2020/06/02
//

// Buffer Manager���𻺳����Ĺ�����Ҫ�����У�
// 1.	������Ҫ����ȡָ�������ݵ�ϵͳ�������򽫻������е�����д�����ļ�
// 2.	ʵ�ֻ��������滻�㷨������������ʱѡ����ʵ�ҳ�����滻
// 3.	��¼�������и�ҳ��״̬�����Ƿ��޸Ĺ���
// 4.	�ṩ������ҳ��pin���ܣ���������������ҳ���������滻��ȥ

#pragma once

#include <iostream>
#include <const.h>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <io.h>

#define BUFFERSIZE 128*250	// ����BUFFERSIZE��128*x ���� x Mb

/*
    Page�ࣺPage�����Buffer�е�һ��ҳ��Page����һ��Pageͨ����Ӧһ�������ļ��еĿ飨block����
            Page��ı�����һ��char buffer[PAGESIZE]���飬����block_id��filename��pinNum��
            dirty��valid�ȱ�־��Ϣ������صĺ�����
*/
class Page {
public:
    Page();
    ~Page();
    char* getPagePointer();    //��ȡPage���׵�ַ
    void setBlockID(int ID);
    int getBlockID();
    /*void setFileName(std::string filename);
    std::string getFileName();*/
    void pin();
    void unpin();
    int getPinNum();
    bool getDirty();
    void setDirty(bool dirty);
    bool getValid();
    void setValid(bool valid);

private:
    char buffer[PAGESIZE];  // ����һ����СΪPAGESIZE��char���飬��ʾһ��ҳ
    // ���±�����¼�����Page��ӳ��ģ��ڴ����ļ��е�block��Ϣ
    int block_id;   // �����ļ��еĿ�š�ͨ��һ��Page <-> һ������block���ڴ����ļ��У����Ϊblock_id����ʼλ�ö�ӦPAGESIZE*block_id��
    // ���±�����¼��Page��״̬������pin���������ź�������dirty���Ƿ����޸ģ���valid���Ƿ���ã�
    int pinNum;    // pinNum���ź����ķ�ʽ����ʾPage������״̬��ÿpinһ��Page��pin++����pin==0ʱ��Page��swap out����pin>0ʱ��Page����swap out��
    bool dirty; // dirty��ʾPage�Ƿ����޸ġ���dirty==trueʱ��swap out���Pageʱ�����뽲��ҳ��д����̶�Ӧ��block��
    bool valid; // ��ʾPage�Ƿ���á���Page��ʼ������swap outʱ��valid==false����Page��load��Ӧ��block�����ݣ�valid==true
};

class BufferManager {
public:
    BufferManager(std::string filename, size_t buffer_size);
    ~BufferManager();   // �������������
    // ���º�������buffer�е�Page������е�block�Ľ���
    std::string getFilename();  //��ȡBuffer��Ӧ�Ĵ���filename
    int getBlockID(int page_id);    //ͨ��page_id�õ�block_id��û�ҵ��򷵻�-1
    int getPageID(int block_id);  //ͨ��block_id�õ�page_id��û�ҵ��򷵻�-1��δ�ҵ���˵�����block���ܱ�swap out��δװ��buffer��
    int loadBlock(int block_id); //��Blockװ���ڴ棬���ض�Ӧ��PageID
    void swapOutPage(int page_id);  //��Page swap out����Ӧblock�У�ͬʱ����valid=false

    char* getPagePointer(int page_id);  //ͨ��PageID�õ�Page��ͷָ��
    void pinPage(int page_id);  //Pinһ��Page
    void unpinPage(int page_id);    //unpinһ��Page
    bool getPin(int page_id);   //��ȡPage��pin��־λ
    void setDirty(int page_id, bool status); //����Page��dirty
    bool getDirty(int page_id); //��ȡPage��dirty��־λ
    void setValid(int page_id, bool status); //����Page��valid
    bool getValid(int page_id);
    int getBlockNum();  //ͨ���ļ���С������block������

private:
    std::vector<Page> Buffer;   // BufferΪһ��vector�������ض�������Page
    std::string filename;   // Buffer��Ӧ��filename
    size_t buffer_size; //Buffer�Ƽ��Ĵ�С����ҳ��Ϊ��λ
};
