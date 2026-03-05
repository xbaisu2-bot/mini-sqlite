#include <repl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

InputBuffer* new_input_buffer(){
  InputBuffer* input_buffer=(InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer=NULL;
  input_buffer->buffer_length=0;
  input_buffer->input_length=0;
  return input_buffer;
}

// 打印提示词
void print_prompt(){
  printf("xbaisu2_bot-db > ");
  return;
}

void prase_input(InputBuffer* input_buffer){
    if(strcmp(input_buffer->buffer,".exit")==0){
      close_input_buffer(input_buffer);
      printf("bye.\n");
      exit(EXIT_SUCCESS);
    }else{
      printf("未知命令 '%s'.\n", input_buffer->buffer);
    }
}

// 读取输入
void read_input(InputBuffer* input_buffer){
  // getline返回ssize_t：读取到的字节数，需要getline来管理缓冲区大小
  ssize_t bytes_read=getline(&(input_buffer->buffer),&(input_buffer->buffer_length),stdin);

  if(bytes_read<=0){
    printf("读取输入时错误.\n");
    exit(EXIT_FAILURE);
  }

  // 忽略行尾'\n'
  input_buffer->input_length=bytes_read-1;
  input_buffer->buffer[bytes_read-1]=0;
}

// 关闭封装器
void close_input_buffer(InputBuffer* input_buffer){
  free(input_buffer->buffer);
  free(input_buffer);
  return;
}

void start_repl(){
  InputBuffer* input_buffer=new_input_buffer();

  while(true){
    print_prompt();
    read_input(input_buffer);
    prase_input(input_buffer);
  }
  return;
}
