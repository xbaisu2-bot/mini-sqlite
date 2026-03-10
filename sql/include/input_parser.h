#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include "repl.h"
#include "single_table.h"

typedef enum{
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommandResult;

typedef enum{
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
}PrepareResult;

typedef enum{
  STATEMENT_INSERT,
  STATEMENT_DELETE,
  STATEMENT_UPDATE,
  STATEMENT_SELECT
}StatementType;

typedef enum{
  EXECUTE_SUCCESS,
  EXECUTE_TABLE_FULL
}ExecuteResult;

typedef struct{
  StatementType type;
  Row row_to_insert;  // 只用于单表插入
}Statement;


MetaCommandResult do_meta_command(InputBuffer* input_buffer,Table* table);

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement);

ExecuteResult execute_insert(Statement* statement,Table* table);

// TODO:目前为全表打印
ExecuteResult execute_select(Statement* statement,Table* table);

ExecuteResult execute_statement(Statement* statement,Table* table);

void parse_input(InputBuffer* input_buffer,Table* table);

#endif
