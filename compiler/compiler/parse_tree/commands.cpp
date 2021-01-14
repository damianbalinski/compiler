#include <iostream>
#include "commands.hpp"
#include "parse_tree.hpp"
#include "../code_generator/instr_generator.hpp"
#include "../code_generator/code_generator.hpp"
#include "../debugger/debugger.hpp"

using std::cout;
using std::endl;

CommandVector* commands;
int DEPTH = 0;

// HALT
void CHalt::print() {
    cout << "END" << endl;
}

void CHalt::code() {
    halt();
}

// WRITE
void CWrite::print() {
    DEPTH_PRINT();
    cout << "WRITE ";
    val->print();
    cout << ";" << endl;
}

void CWrite::code() {
    write(val->unit()); 
}

// READ
void CRead::print() {
    DEPTH_PRINT();
    cout << "READ ";
    val->print();
    cout << ";" << endl;
}

void CRead::code() {
    read(val->unit()); 
}

// ASSIGN
void CAssign::print() {
    DEPTH_PRINT();
    val->print();
    cout << " := ";
    exp->print();
    cout << ";" << endl;
}

void CAssign::code() {
    assign(val->unit(), exp->unit());
}

// IF THEN
void CIfThen::print() {
    DEPTH_PRINT();
    cout << "IF ";
    cond->print();
    cout << " THEN" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDIF" << endl;
}

void CIfThen::code() {
    cond_unit = cond->unit();   /* warunek */
    jump_true_false(labels, cond_unit, INIT);
    jump_end(labels, cond_unit, INIT);
    labels->label_cmd = code_get_label();

    cmd_true->code();           /* komendy */
    labels->label_end = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    DBG_JUMPS(labels);
    jumps_free(labels, cond_unit); 
}

// IF THEN ELSE
void CIfThenElse::print() {
    DEPTH_PRINT();
    cout << "IF ";
    cond->print();
    cout << " THEN" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();
    
    DEPTH_PRINT();
    cout << "ELSE" << endl;

    DEPTH_INC();
    cmd_false->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDIF" << endl;
}

void CIfThenElse::code() {
    cond_unit = cond->unit();   /* warunek */
    jump_true_false(labels, cond_unit, INIT);
    jump_end(labels, cond_unit, INIT);
    labels->label_cmd = code_get_label();

    cmd_true->code();           /* komendy true */
    jump_else(labels, cond_unit, INIT);
    labels->label_end = code_get_label();

    cmd_false->code();          /* komendy false */
    labels->label_else = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    jump_else(labels, cond_unit, FINISH);
    DBG_JUMPS(labels);
    jumps_free(labels, cond_unit); 
}

// WHILE
void CWhile::print() {
    DEPTH_PRINT();
    cout << "WHILE ";
    cond->print();
    cout << " DO" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDWHILE" << endl;
}

void CWhile::code() {                   
    labels->label_cond = code_get_label();

    cond_unit = cond->unit();    /* warunek */
    jump_true_false(labels, cond_unit, INIT);
    jump_end(labels, cond_unit, INIT);
    labels->label_cmd = code_get_label();

    cmd_true->code();           /* komendy */
    jump_cond(labels, cond_unit, INIT);
    labels->label_end = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    jump_cond(labels, cond_unit, FINISH);
    DBG_JUMPS(labels);
    jumps_free(labels, cond_unit);
}

// REPEAT
void CRepeat::print() {
    DEPTH_PRINT();
    cout << "REPEAT" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "UNTIL ";
    cond->print();
    cout << ";" << endl;
}

void CRepeat::code() {                 
    labels->label_end = code_get_label();

    cmd_true->code();               /* komendy */
    cond_unit = cond->unit();       /* warunek */
    
    jump_true_false(labels, cond_unit, INIT);
    jump_end(labels, cond_unit, INIT);
    labels->label_cmd = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    DBG_JUMPS(labels);
    jumps_free(labels, cond_unit);   
}

// FOR TO
void CForTo::print() {
    DEPTH_PRINT();
    cout << "FOR ";
    cout << iter_id;
    cout << " FROM ";
    cond->print();
    cout << " DO" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDFOR" << endl;
}

void CForTo::code() {
    cond_unit = cond->unit();               /* warunek */
    labels->label_cond = code_get_label();
    jump_true_false(labels, cond_unit, INIT);
    jump_end(labels, cond_unit, INIT);
    labels->label_cmd = code_get_label();

    iter->is_visible = true;
    cmd_true->code();                       /* komendy */
    iter->is_visible = false;
    
    for_step(labels, iter, cond_unit, FOR_TO);
    jump_cond(labels, cond_unit, INIT);
    labels->label_end = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    jump_cond(labels, cond_unit, FINISH);
    for_free(labels, cond_unit);
    // remove_iterator(iter_id);
}

// FOR DOWNTO
void CForDownto::print() {
    DEPTH_PRINT();
    cout << "FOR ";
    cout << iter_id;
    cout << " FROM ";
    cond->print();
    cout << " DO" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDFOR" << endl;
}

void CForDownto::code() {
    cond_unit = cond->unit();               /* warunek */
    labels->label_cond = code_get_label();
    jump_true_false(labels, cond_unit, INIT);
    jump_end(labels, cond_unit, INIT);
    labels->label_cmd = code_get_label();

    iter->is_visible = true;
    cmd_true->code();                       /* komendy */
    iter->is_visible = false;

    for_step(labels, iter, cond_unit, FOR_DOWNTO);
    jump_cond(labels, cond_unit, INIT);
    labels->label_end = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    jump_cond(labels, cond_unit, FINISH);
    for_free(labels, cond_unit);
    // remove_iterator(iter_id);
}