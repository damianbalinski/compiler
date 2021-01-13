CC=g++
FLAGS=-lm -lcln
FLAGS2=-Wall -Wpedantic

main: parser.o lexer.o symbol_table.o registers_machine.o code_generator.o instr_generator.o unit.o cond.o data_manager.o commands.o
	${CC} -o temp parser.o lexer.o symbol_table.o registers_machine.o code_generator.o instr_generator.o unit.o cond.o data_manager.o commands.o ${FLAGS}

symbol_table.o: symbol_table/symbol_table.cpp
	${CC} -c symbol_table/symbol_table.cpp

registers_machine.o: code_generator/registers_machine.cpp
	${CC} -c code_generator/registers_machine.cpp

code_generator.o: code_generator/code_generator.cpp
	${CC} -c code_generator/code_generator.cpp

instr_generator.o: code_generator/instr_generator.cpp
	${CC} -c code_generator/instr_generator.cpp

data_manager.o: symbol_table/data_manager.cpp
	${CC} -c symbol_table/data_manager.cpp

unit.o: others/unit.cpp
	${CC} -c others/unit.cpp

cond.o: others/cond.cpp
	${CC} -c others/cond.cpp

commands.o : parse_tree/commands.cpp
	$(CC) -c parse_tree/commands.cpp

lexer.o: lexer.cpp
	${CC} -c lexer.cpp

parser.o: parser.cpp
	${CC} -c parser.cpp

parser.cpp: compiler.y
	bison -o parser.cpp -d compiler.y

lexer.cpp: compiler.l
	flex -o lexer.cpp compiler.l

clean:
	rm *.o
	rm parser.cpp
	rm lexer.cpp
	rm parser.hpp

cleanf:
	rm *.o
	rm parser.cpp
	rm lexer.cpp
	rm parser.hpp
	rm temp
