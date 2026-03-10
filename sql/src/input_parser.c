#include "input_parser.h"

#include <stdlib.h>
#include <string.h>

MetaCommandResult do_meta_command(InputBuffer* input_buffer,Table* table){
  if(strcmp(input_buffer->buffer,".exit")==0){
    close_input_buffer(input_buffer);
    free_table(table);
    exit(EXIT_SUCCESS);
  }
  return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement){
  if(strncmp(input_buffer->buffer,"insert",6)==0){
    statement->type=STATEMENT_INSERT;
    int args_num=sscanf(input_buffer->buffer,
                      "insert %d %s %s",&(statement->row_to_insert.id),
                      &(statement->row_to_insert.username),&(statement->row_to_insert.email));
    if(args_num!=3){
      return PREPARE_SYNTAX_ERROR;
    }
    return PREPARE_SUCCESS;
  }else if(strncmp(input_buffer->buffer,"delete",6)==0){
    statement->type=STATEMENT_DELETE;
    return PREPARE_SUCCESS;
  }else if(strncmp(input_buffer->buffer,"update",6)==0){
    statement->type=STATEMENT_UPDATE;
    return PREPARE_SUCCESS;
  }else if(strncmp(input_buffer->buffer,"select",6)==0){
    statement->type=STATEMENT_SELECT;
  }
  return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement* statement,Table* table){
  if(table->num_rows>TABLE_MAX_ROWS){
    return EXECUTE_TABLE_FULL;
  }
  Row* row_to_insert=&(statement->row_to_insert);
  serialize_row(row_to_insert,row_slot(table,table->num_rows));
  table->num_rows++;
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement,Table* table){
  Row row;
  for(uint32_t i=0;i<table->num_rows;i++){
    deserialize_row(row_slot(table,i),&row);
    print_row(&row);
  }
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement,Table* table){
  switch(statement->type){
    case STATEMENT_INSERT:{
      return execute_insert(statement,table);
    }
    case STATEMENT_DELETE:{
      printf("UNIMPLEMENTED:删除逻辑\n");
      exit(EXIT_FAILURE);
      break;
    }
    case STATEMENT_UPDATE:{
      printf("UNIMPLEMENTED:更新逻辑\n");
      exit(EXIT_FAILURE);
      break;
    }
    case STATEMENT_SELECT:{
      return execute_select(statement,table);
    }
  }
}

void parse_input(InputBuffer* input_buffer,Table* table){
  if(input_buffer->buffer[0]=='.'){
    switch(do_meta_command(input_buffer,table)){
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
      case PREPARE_SUCCESS:{
        switch(execute_statement(&statement,table)){
          case EXECUTE_SUCCESS:{
            printf("执行成功.\n");
            break;
          }case EXECUTE_TABLE_FULL:{
            printf("错误: 表已满.\n");
            break;
          }
        }
      }
      case PREPARE_SYNTAX_ERROR:{
        printf("语法错误.\n");
        return;
      }
      case PREPARE_UNRECOGNIZED_STATEMENT:{
        printf("未知命令.\n");
        return;
      }
    }
    printf("执行完毕.\n");
  }
}
