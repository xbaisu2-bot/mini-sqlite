#include "single_table.h"
#include "input_parser.h"

void serialize_row(Row* source, void* destination){
  // 序列化ID
  memcpy(destination + ID_OFFSET,&(source->id),ID_SIZE);
  // 序列化用户名
  memcpy(destination + USERNAME_OFFSET,&(source->username),USERNAME_SIZE);
  // 序列化邮箱
  memcpy(destination + EMAIL_OFFSET,&(source->email),EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination){
  // 反序列化ID
  memcpy(destination->id,source + ID_OFFSET,ID_SIZE);
  // 反序列化用户名
  memcpy(destination->username,source + USERNAME_OFFSET,USERNAME_SIZE);
  // 反序列化邮箱
  memcpy(destination->email,source + EMAIL_OFFSET,EMAIL_SIZE);
}

Table* new_table(){
  Table* table=(Table*)malloc(sizeof(Table));
  table->num_rows=0;
  for(uint32_t i=0;i<TABLE_MAX_PAGES;i++){
    table->page[i]=NULL;
  }
  return table;
}

void free_table(Table* table){
  for(uint32_t i=0;table->page[i];i++){
    free(table->page[i]);
  }
  free(table);
}

void print_row(Row* row){
  prtinf("(%d, %s, %s)\n",row->id,row->username,row->email);
}

void* row_slot(Table* table,uint32_t row_num){
  uint32_t page_num=row_num/ROWS_PER_PAGE;
  void* page=table->page[page_num];
  if(page==NULL){
    // 仅在需要时为page分配内存
    page=table->page[page_num]=malloc(PAGE_SIZE);
  }
  uint32_t row_offset=row_num % ROWS_PER_PAGE;
  uint32_t byte_offset=row_offset*ROW_SIZE;
  return page+byte_offset;
}

