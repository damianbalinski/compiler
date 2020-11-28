#include <stdio.h>
#include "codes.h"


/* Memory */
int stack[999];

/* Registers */
int                 pc   = 0;
struct instruction  ir;
int                 ar   = 0;
int                 top  = 0;

void fetch_execute_cycle() {   
    
    do { 
        /* Fetch         */
        ir = code[pc++];
        
        /* Execute       */
        switch (ir.op) {
            case HALT      : printf( "halt\n" );                            break;
            case READ_INT  : printf( "Input: " );
                             scanf( "%ld", &stack[ar+ir.arg] );             break;
            case WRITE_INT : printf( "Output: %d\n", stack[top--] );        break;
            case STORE     : stack[ir.arg] = stack[top--];                  break;
            case JMP_FALSE : if ( stack[top--] == 0 )pc = ir.arg;           break;

            case GOTO      : pc = ir.arg;                                   break;
            case DATA      : top = top + ir.arg;                            break;
            case LD_INT    : stack[++top] = ir.arg;                         break;
            case LD_VAR    : stack[++top] = stack[ar+ir.arg];               break;
            case LT        : if ( stack[top-1] < stack[top] )
                                stack[--top] = 1;
                            else 
                                stack[--top] = 0;                           break;
            case EQ        : if ( stack[top-1] == stack[top] )
                                stack[--top] = 1;
                            else
                                stack[--top] = 0;                           break;
            case GT        : if ( stack[top-1] > stack[top] )
                                stack[--top] = 1;
                             else
                                stack[--top] = 0;top--;                     break;
            case ADD       : stack[top-1] = stack[top-1] + stack[top];top--;break;
            case SUB       : stack[top-1] = stack[top-1] - stack[top];top--;break;
            case MULT      : stack[top-1] = stack[top-1] * stack[top];top--;break;
            case DIV       : stack[top-1] = stack[top-1] / stack[top];top--;break;
            case PWR       : stack[top-1] = stack[top-1] * stack[top];top--;break;
            
            default        : printf( "Internal Error: Memory Dump\n" );     break;
        }

    } while (ir.op != HALT);
    
}

// int main(void) {
//     return 0;
// }