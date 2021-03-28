import ply.yacc as yacc

from lexer import tokens
from myarithmetic import pzero, pone, pnorm, pnorm_pow
from myarithmetic import padd, psub, pmul, pdiv, ppow

precedence = (
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE'),
    ('right', 'UMINUS'),
    ('nonassoc', 'EXPONENT'),
)

formula = []

def p_input(p):
    'input : line'
    p[0] = p[1]

def p_line_empty(p):
    'line : NEWLINE'
    p[0] = None

def p_line_expr(p):
    'line : expr NEWLINE'
    p[0] = pnorm(p[1])

def p_expr(p):
    'expr : NUMBER'
    p[0] = pnorm(p[1])
    formula.append(p[0])

def p_expr_uminus(p):
    'expr : MINUS NUMBER %prec UMINUS'
    p[0] = pnorm(-p[2])
    formula.append(p[0])

def p_expr_add(p):
    'expr : expr PLUS expr'
    p[0] = padd(p[1], p[3])
    formula.append('+')

def p_expr_sub(p):
    'expr : expr MINUS expr'
    p[0] = psub(p[1], p[3])
    formula.append('-')

def p_expr_mul(p):
    'expr : expr TIMES expr'
    p[0] = pmul(p[1], p[3])
    formula.append('*')

def p_expr_div(p):
    'expr : expr DIVIDE expr'
    if pzero(p[3]) == 1:
        print("Dzielenie przez 0!")
        raise ValueError
    p[0] = pdiv(p[1], p[3])
    formula.append('/')

def p_expr_pow(p):
    'expr : expr EXPONENT NUMBER'
    p[0] = ppow(p[1], p[3])
    formula.append(pnorm_pow(p[3]))
    formula.append('^')

def p_expr_pow_minus(p):
    'expr : expr EXPONENT MINUS NUMBER'
    p[0] = ppow(p[1], -p[4])
    formula.append(pnorm_pow(-p[4]))
    formula.append('^')

def p_expr_paren(p):
    'expr : LPAREN expr RPAREN'
    p[0] = p[2]

def p_error(p):
    print("Blad skladniowy!")

def print_formula():
    for a in formula:
        print(a, end=" ")
    print()


# build parser
parser = yacc.yacc()


def read_line():
    str = input('> ')

    if str == '':
        return True, str
    elif str[-1] == '\\':
        return True, str + '\n'
    else:
        return False, str + '\n'


while True:
    try:
        inp = read_line()
        str = inp[1]

        while inp[0]:
            inp = read_line()
            str += inp[1]

    except EOFError:
        break

    try:
        result = parser.parse(str)
        if result:
            print_formula()
            print("  Wynik: ", result)
    except Exception:
        pass

    formula = []
    parser.restart()

