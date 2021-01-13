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
    cout << "write" << endl;
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

void CIfThen::print() {
    DEPTH_PRINT();
    cout << "IF ";
    con->print();
    cout << " THEN" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDIF" << endl;
}

void CIfThenElse::print() {
    DEPTH_PRINT();
    cout << "IF ";
    con->print();
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
    labels = cond_alloc();                    
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
    labels = cond_alloc();                 
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



void CForTo::print() {
    DEPTH_PRINT();
    cout << "FOR ";
    cout << iter;
    cout << " FROM ";
    val1->print();
    cout << " TO ";
    val2->print();
    cout << " DO" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDFOR" << endl;
}

void CForDownto::print() {
    DEPTH_PRINT();
    cout << "FOR ";
    cout << iter;
    cout << " FROM ";
    val1->print();
    cout << " DOWNTO ";
    val2->print();
    cout << " DO" << endl;

    DEPTH_INC();
    cmd_true->print();
    DEPTH_DEC();

    DEPTH_PRINT();
    cout << "ENDFOR" << endl;
}
