CC=gcc
FLAGS=-lm

main: parser.o lexer.o symbol_table.o registers_machine.o code_generator.o instr_generator.o unit.o cond.o data_manager.o
	gcc -o temp parser.o lexer.o symbol_table.o registers_machine.o code_generator.o instr_generator.o unit.o cond.o data_manager.o ${FLAGS}

symbol_table.o: symbol_table/symbol_table.c
	${CC} -c symbol_table/symbol_table.c

registers_machine.o: code_generator/registers_machine.c
	${CC} -c code_generator/registers_machine.c

code_generator.o: code_generator/code_generator.c
	${CC} -c code_generator/code_generator.c

instr_generator.o: code_generator/instr_generator.c
	${CC} -c code_generator/instr_generator.c

data_manager.o: symbol_table/data_manager.c
	${CC} -c symbol_table/data_manager.c

unit.o: others/unit.c
	${CC} -c others/unit.c

cond.o: others/cond.c
	${CC} -c others/cond.c

lexer.o: lexer.c
	gcc -c lexer.c

parser.o: parser.c
	gcc -c parser.c

parser.c: compiler.y
	bison -o parser.c -d compiler.y

lexer.c: compiler.l
	flex -o lexer.c compiler.l

clean:
	rm *.o
	rm parser.c
	rm lexer.c
	rm parser.h
