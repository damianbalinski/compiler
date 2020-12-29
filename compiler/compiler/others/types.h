#pragma once

typedef unsigned long long val_type;
typedef unsigned long long input_type;

typedef struct {
    input_type label_cmd;
    input_type label_cond;
    input_type label_end;

    input_type jump_first;  /* jump true, jump false */
    input_type jump_end;    /* jump end              */
    input_type jump_last;   /* jump cmd, jump cond   */
} cond_type;