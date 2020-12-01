#ifndef _CODES_H_
#define _CODES_H_

/* OPERATIONS: Internal Representation */
enum code_ops { HALT, STORE, JMP_FALSE, GOTO,
                DATA, LD_INT, LD_VAR, 
                READ_INT, WRITE_INT,
                LT, EQ, GT, ADD, SUB, MULT, DIV, PWR };

/* OPERATIONS: External Representation */
char *op_name[] = { "halt", "store", "jmp_false", "goto",
                    "data", "ld_int", "ld_var",
                    "in_int", "out_int",
                    "lt", "eq", "gt", "add", "sub", "mult", "div", "pwr" };

#endif      /* _CODES_H_ */