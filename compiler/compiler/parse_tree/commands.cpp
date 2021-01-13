#include "commands.hpp"
#include <iostream>

using std::cout;
using std::endl;

int DEPTH = 0;
const char* DEPTH_SIGN = "  ";

void print_depth() {
    for(int i = 0; i < DEPTH; i++)
        cout << DEPTH_SIGN;
}
void CommandVector::print_raw() {
    for (AbstractCommand* com: *this)
        com->print_raw();
};

void CWrite::print_raw() {
    print_depth();
    cout << "WRITE val;" << endl;
}

void CRead::print_raw() {
    print_depth();
    cout << "READ id;" << endl;
}

void CAssign::print_raw() {
    print_depth();
    cout << "id := expr;" << endl;
}

void CIfThen::print_raw() {
    print_depth();
    cout << "IF cond THEN" << endl;

    DEPTH++;
    cmd_true->print_raw();
    DEPTH--;

    print_depth();
    cout << "ENDIF" << endl;
}


void CWhile::print_raw() {
    print_depth();
    cout << "WHILE cond DO" << endl;

    DEPTH++;
    cmd_true->print_raw();
    DEPTH--;

    print_depth();
    cout << "ENDWHILE" << endl;
}

void CRepeat::print_raw() {
    print_depth();
    cout << "REPEAT" << endl;

    DEPTH++;
    cmd_true->print_raw();
    DEPTH--;

    print_depth();
    cout << "UNTIL cond;" << endl;
}

void CForTo::print_raw() {
    print_depth();
    cout << "FOR id FROM val TO val DO" << endl;

    DEPTH++;
    cmd_true->print_raw();
    DEPTH--;

    print_depth();
    cout << "ENDFOR" << endl;
}

void CForDownto::print_raw() {
    print_depth();
    cout << "FOR id FROM val DOWNTO val DO" << endl;

    DEPTH++;
    cmd_true->print_raw();
    DEPTH--;

    print_depth();
    cout << "ENDFOR" << endl;
}

// TEST
// int main() {
//     CommandVector* vec = new CommandVector();
//     vec->push_back(new AbstractCommand("first"));
//     vec->push_back(new AbstractCommand("second"));
//     vec->push_back(new AbstractCommand("third"));

//     vec->print_raw();
// }