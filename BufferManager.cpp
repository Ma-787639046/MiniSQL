//
//  BufferManager.cpp
//  Created by MGY on 2020/06/02
//

#include <BufferManager.h>
#include <const.h>

// Page��
Page::Page() {
    memset(buffer, 0, PAGESIZE);
    block_id = -1;
    pinNum = 0;
    dirty = false;
    valid = false;
}

Page::~Page() {}

inline char* Page::getPagePointer() {
    return this->buffer;
}

inline void Page::setBlockID(int ID) {
    this->block_id = ID;
}

inline int Page::getBlockID() {
    return this->block_id;
}

inline void Page::pin()
{
    this->pinNum++;
}

inline void Page::unpin()
{
    this->pinNum--;
}

inline int Page::getPinNum()
{
    return this->pinNum;
}

inline bool Page::getDirty()
{
    return this->dirty;
}

inline void Page::setDirty(bool dirty)
{
    this->dirty = dirty;
}

inline bool Page::getValid()
{
    return this->valid;
}

inline void Page::setValid(bool valid)
{
    this->valid = valid;
}

BufferManager::BufferManager(std::string filename, size_t buffer_size)
{
    Buffer.reserve(buffer_size); //����buffer_size��Page�Ŀռ䣬�����malloc�ٶ�
    this->filename = filename;
    this->buffer_size = buffer_size;
}

BufferManager::~BufferManager()
{
    for (int i = 0; i < (int)Buffer.size(); i++) {
        if (Buffer[i].getValid() == true && Buffer[i].getDirty() == true) {
            swapOutPage(i); // valid��dirty��swap out���Page
        }
    }
    Buffer.clear();
}

std::string BufferManager::getFilename()
{
    return this->filename;
}

int BufferManager::getBlockID(int page_id)
{
    return Buffer[page_id].getBlockID();
}

int BufferManager::getPageID(int block_id)
{
    //��ͷ����ɨ������Page����ö�Ӧ��PageID��û���򷵻�-1
    for (int i = 0; i < (int)Buffer.size(); i++) {
        if (this->filename == filename && Buffer[i].getBlockID() == block_id) {
            return i;
        }
    }
    return -1;
}

int BufferManager::loadBlock(int block_id)
{
    int PageID = -1;
    if (Buffer.size() < this->buffer_size) {
        Page* page = new Page();
        Buffer.push_back(*page);    //����ҳ
        PageID = Buffer.size() - 1;
    }
    else {
        //Buffer��������Ѱ��valid==false��ҳ
        for (int i = 0; i < (int)Buffer.size(); i++) {
            if (Buffer[i].getValid() == false) PageID = i;
        }
        //�Ҳ���unvalid��Page����swap outһ��Page���������д�����һ��ҳ�滻���ԣ�
        if (PageID == -1) {
            swapOutPage(0);
            PageID = 0;
        }
    }
    FILE* file = fopen((this->filename).c_str(), "r");
    if (file == nullptr) {  //������file���򴴽����ļ��������ϣ��ļ���Record Manager��Catalog Manager��ģ�鴴����ɾ�����ļ��Ƿ����Ӧ������ģ���顣 
        file = fopen((this->filename).c_str(), "w");
        fwrite("", 1, 0, file);
        fclose(file);
        file = fopen((this->filename).c_str(), "r");
    }
    fseek(file, block_id * PAGESIZE, 0);    //��λ�ļ�ָ��
    fread(Buffer[PageID].getPagePointer(), PAGESIZE, 1, file);  //��ȡPAGESIZE bytes��Page��
    fclose(file);
    Buffer[PageID].setBlockID(block_id);
    Buffer[PageID].setDirty(false);
    Buffer[PageID].setValid(true);
    return PageID;
}

void BufferManager::swapOutPage(int page_id)
{
    if (getDirty(page_id) == true) {
        //д��block
        FILE* file = fopen((this->filename).c_str(), "r+");
        fseek(file, Buffer[page_id].getBlockID() * PAGESIZE, 0);    //��λ�ļ�ָ��
        fwrite(getPagePointer(page_id), PAGESIZE, 1, file); //д��
        fclose(file);
    }
    setValid(page_id, false);
}

char* BufferManager::getPagePointer(int page_id)
{
    return Buffer[page_id].getPagePointer();
}

void BufferManager::pinPage(int page_id)
{
    Buffer[page_id].pin();
}

void BufferManager::unpinPage(int page_id)
{
    Buffer[page_id].unpin();
}

bool BufferManager::getPin(int page_id)
{
    return Buffer[page_id].getPinNum() > 0;
}

void BufferManager::setDirty(int page_id, bool status)
{
    Buffer[page_id].setDirty(status);
}

bool BufferManager::getDirty(int page_id)
{
    return Buffer[page_id].getDirty();
}

void BufferManager::setValid(int page_id, bool status)
{
    Buffer[page_id].setValid(status);
}

bool BufferManager::getValid(int page_id)
{
    return Buffer[page_id].getValid();
}

int BufferManager::getBlockNum()
{
    struct _stat info;
    _stat(this->filename.c_str(), &info);
    int size = info.st_size;
    return size/PAGESIZE;
}

//������main

//int main() {
//    BufferManager buffer("Buffer.db");
//    int page_id = buffer.loadBlock(buffer.getFilename(), 0);
//    //д�����Ĳ���
//    /*std::string s = "123456";
//    char* page = buffer.getPagePointer(page_id);
//    memcpy_s(page, PAGESIZE, &s, sizeof(s));
//    buffer.setDirty(page_id, true);*/
//    //��ȡ����Ĳ���
//    /*char* page = buffer.getPagePointer(page_id);
//    std::string s = *(std::string*)page;
//    std::cout << s << std::endl;*/
//    return 0;
//}
