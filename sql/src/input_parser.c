#include "input_parser.h"

#include <stdlib.h>
#include <string.h>

MetaCommandResult do_meta_command(InputBuffer* input_buffer){
  if(strcmp(input_buffer->buffer,".exit")==0){
    close_input_buffer(input_buffer);
    exit(EXIT_SUCCESS);
  }
  return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement){
  if(strncmp(input_buffer->buffer,"insert",6)==0){
    statement->type=STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }else if(strncmp(input_buffer->buffer,"delete",6)==0){
    statement->type=STATEMENT_DELETE;
    return PREPARE_SUCCESS;
  }else if(strncmp(input_buffer->buffer,"update",6)==0){
    statement->type=STATEMENT_UPDATE;
    return PREPARE_SUCCESS;
  }else if(strncmp(input_buffer->buffer,"select",6)==0){
    statement->type=STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }
  return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement){
  switch(statement->type){
    case STATEMENT_INSERT:{
      printf("UNIMPLEMENTED:插入逻辑\n");
      break;
    }
    case STATEMENT_DELETE:{
      printf("UNIMPLEMENTED:删除逻辑\n");
      break;
    }
    case STATEMENT_UPDATE:{
      printf("UNIMPLEMENTED:更新逻辑\n");
      break;
    }
    case STATEMENT_SELECT:{
      printf("UNIMPLEMENTED:查询逻辑\n");
      break;
    }
  }
}

void parse_input(InputBuffer* input_buffer){
  if(input_buffer->buffer[0]=='.'){
    switch(do_meta_command(input_buffer)){
      case META_COMMAND_SUCCESS:break;
      case META_COMMAND_UNRECOGNIZED_COMMAND:{
        printf("未知命令.\n");
        break;
      }
    }
    return;
  }else{
    Statement statement;
    switch(prepare_statement(input_buffer,&statement)){
      case PREPARE_SUCCESS:execute_statement(&statement);break;
      case PREPARE_UNRECOGNIZED_STATEMENT:{
        printf("未知命令.\n");
        return;
      }
    }
    printf("执行完毕.\n");
  }
}
