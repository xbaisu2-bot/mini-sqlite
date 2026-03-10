#ifndef REPL_H
#define REPL_H

#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

// 与getline交互所需封装器
typedef struct{
  char* buffer; // 缓冲区
  size_t buffer_length; // 已分配缓冲区容量
  ssize_t input_length; // 已读取的字节数,<=buffer_length
}InputBuffer;

InputBuffer* new_input_buffer();

void print_prompt();

void read_input(InputBuffer* input_buffer);

void close_input_buffer(InputBuffer* input_buffer);

void start_repl();

#endif
