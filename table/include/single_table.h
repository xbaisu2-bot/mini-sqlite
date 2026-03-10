#ifndef SINGLE_TABLE_H
#define SINGLE_TABLE_H
// 核心思想是将数据组织成固定大小的内存块/数据库存储的基本单元（4KB，故意与操作系统虚拟内存的页大小相同，方便操作系统高效管理)，每个页内紧凑的存储序列化后的行数据
#include <stdint.h>

// 通过地址为0的空指针不通过实例结构体获取成员的字节长度
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

#define USERNAME_COL_MAXSIZE 32
#define EMAIL_COL_MAXSIZE 255

typedef struct{
  uint32_t id; // 避免 unsigned int在不同系统出现不同长度，确保行为一致
  char username[USERNAME_COL_MAXSIZE];
  char email[EMAIL_COL_MAXSIZE];
}Row;


// 行数据需要在内存中紧密存储，而struct可能由于内存对齐使得成员间存在填充字节（padding），导致结构体的实际大小大于其成员大小之和，我们需要手动分配使其紧凑（不造成空间浪费）
const uint32_t ID_SIZE=size_of_attribute(Row,id);
const uint32_t USERNAME_SIZE=size_of_attribute(Row,username);
const uint32_t EMAIL_SIZE=size_of_attribute(Row,email);
const uint32_t ID_OFFSET=0;
const uint32_t USERNAME_OFFSET=ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET=USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE=ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

// 序列化：将内存对象（此处为行对象）转为与内存布局无关的扁平字节流，存到任意内存区域，通过操作该内存区域可以写入文件/进行网络数据传输等
void serialize_row(Row* source, void* destination);
// 反序列化：恢复回内存对象
void deserialize_row(void* source, Row* destination);

const uint32_t PAGE_SIZE=4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE=PAGE_SIZE/ROW_SIZE;
const uint32_t TABLE_MAX_ROWS=ROWS_PER_PAGE*TABLE_MAX_PAGES;

typedef struct{
  uint32_t num_rows;
  void* page[TABLE_MAX_PAGES];
}Table;

Table* new_table();

void free_table(Table* table);

// 行在内存中的位置
void* row_slot(Table* table,uint32_t row_num);

void print_row(Row* row);


#endif