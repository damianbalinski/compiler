#include <iostream>
#include "commands.hpp"
#include "parse_tree.hpp"
#include "../code_generator/code_generator.hpp"
#include "../code_generator/registers_machine.hpp"
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

/* Drukuje dane na wyjsciu. */
void CWrite::code() {
    unit_type* unit = val->unit();
    DBG_INSTRUCTION_BEGIN("write");
    
    // INSTRUKCJE
    reg_check(unit);        // adres zmiennej
    put(unit->reg);         // zapis na wyjscie

    // ZWALNIANIE
    reg_free(unit->reg);
    unit_free(unit); 

    DBG_INSTRUCTION_END("write");
}

// READ
void CRead::print() {
    DEPTH_PRINT();
    cout << "READ ";
    val->print();
    cout << ";" << endl;
}

/* Pobiera dane z wejscia. */
void CRead::code() {
    unit_type* unit = val->unit();
    DBG_INSTRUCTION_BEGIN("read");

    // INSTRUKCJE
    reg_check(unit);        // adres zmiennej
    get(unit->reg);         // pobranie wejscia

    // ZWALNIANIE
    reg_free(unit->reg);
    unit_free(unit);

    DBG_INSTRUCTION_END("read");
}

// ASSIGN
void CAssign::print() {
    DEPTH_PRINT();
    val->print();
    cout << " := ";
    exp->print();
    cout << ";" << endl;
}

/* Przypisuje wartosc do zmiennej. */
void CAssign::code() {
    unit_type* unit1 = val->unit();
    unit_type* unit2 = exp->unit();
    DBG_INSTRUCTION_BEGIN("assign");

    // INSTRUKCJE
    reg_check(unit1);
    reg_check(unit2);
    store(unit2->reg, unit1->reg);
    
    // ZWALNIANIE
    reg_free(unit1->reg);
    reg_free(unit2->reg);
    unit_free(unit1); 
    unit_free(unit2);

    DBG_INSTRUCTION_END("assign");
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
    finish();                   /* koniec */
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
    finish();                   /* koniec */
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
    finish();                   /* koniec */
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
    finish();                       /* koniec */ 
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
    
    step();                                 /* krok */
    jump_cond(labels, cond_unit, INIT);
    labels->label_end = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    jump_cond(labels, cond_unit, FINISH);
    finish();                               /* koniec */
}

void CForTo::step() {
    DBG_INSTRUCTION_BEGIN("for_step");
    cond_unit->reg = cond_unit->reg_prev;
    int x = cond_unit->reg;

    // VALUE
    reg_const(SUPER_REGISTER, iter->offset);
    load(x, SUPER_REGISTER);
    inc(x);
    store(x, SUPER_REGISTER);

    // CONDITION
    inc(SUPER_REGISTER);
    load(x, SUPER_REGISTER);
    dec(x);
    store(x, SUPER_REGISTER);

    DBG_INSTRUCTION_END("for_step");
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

    step();                                 /* krok */
    jump_cond(labels, cond_unit, INIT);
    labels->label_end = code_get_label();
    jump_true_false(labels, cond_unit, FINISH);
    jump_end(labels, cond_unit, FINISH);
    jump_cond(labels, cond_unit, FINISH);
    finish();                               /* koniec */
}

void CForDownto::step() {
    DBG_INSTRUCTION_BEGIN("for_downto_step");
    cond_unit->reg = cond_unit->reg_prev;
    int x = cond_unit->reg;

    // VALUE
    reg_const(SUPER_REGISTER, iter->offset);
    load(x, SUPER_REGISTER);
    dec(x);
    store(x, SUPER_REGISTER);

    // CONDITION
    inc(SUPER_REGISTER);
    load(x, SUPER_REGISTER);
    dec(x);
    store(x, SUPER_REGISTER);

    DBG_INSTRUCTION_END("for_downto_step");
}