import ply.lex as lex

# tokens
tokens = (
    'NUMBER',
    'PLUS',
    'MINUS',
    'TIMES',
    'DIVIDE',
    'EXPONENT',
    'LPAREN',
    'RPAREN',
    'NEWLINE',
)

# regular expressions strings
t_PLUS     = r'\+'
t_MINUS    = r'-'
t_TIMES    = r'\*'
t_DIVIDE   = r'/'
t_EXPONENT = r'\^'
t_LPAREN   = r'\('
t_RPAREN   = r'\)'
t_ignore   = ' \t'

def t_COMMENT(t):
    r'\#.*'
    pass

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_ESCAPE(t):
    r'\\\n'
    pass

def t_NEWLINE(t):
    r'\n'
    t.lexer.lineno += len(t.value)
    return t

def t_error(t):
    print("Nierozpoznany znak '%s'" % t.value[0])
    raise Exception()

# build lexer
lexer = lex.lex()

if __name__ == '__main__':
     lex.runmain()
