#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include "repl.h"

typedef enum{
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommandResult;

typedef enum{
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED_STATEMENT
}PrepareResult;

typedef enum{
  STATEMENT_INSERT,
  STATEMENT_DELETE,
  STATEMENT_UPDATE,
  STATEMENT_SELECT
}StatementType;

typedef struct{
  StatementType type;
}Statement;


MetaCommandResult do_meta_command(InputBuffer* input_buffer);

PrepareResult prepare_statement(InputBuffer* input_buffer,Statement* statement);

void parse_input(InputBuffer* input_buffer);

#endif
