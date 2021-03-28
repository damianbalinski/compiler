CC=g++
FLAGS=-lm -lcln
DBG=debugger/debugger.hpp
OPT=optimizer/optimizer.hpp

main: parser.o lexer.o symbol_table.o registers_machine.o code_generator.o unit.o jumps.o data_manager.o commands.o values.o expressions.o conditions.o ${DBG} ${OPT}
	${CC} -o compiler parser.o lexer.o symbol_table.o registers_machine.o code_generator.o unit.o jumps.o data_manager.o commands.o values.o expressions.o conditions.o ${FLAGS} ${FLG}

symbol_table.o: symbol_table/symbol_table.cpp ${DBG} ${OPT}
	${CC} -c symbol_table/symbol_table.cpp ${FLG}

registers_machine.o: code_generator/registers_machine.cpp ${DBG} ${OPT}
	${CC} -c code_generator/registers_machine.cpp ${FLG}

code_generator.o: code_generator/code_generator.cpp ${DBG} ${OPT}
	${CC} -c code_generator/code_generator.cpp ${FLG}

data_manager.o: symbol_table/data_manager.cpp ${DBG} ${OPT}
	${CC} -c symbol_table/data_manager.cpp ${FLG}

unit.o: others/unit.cpp ${DBG} ${OPT}
	${CC} -c others/unit.cpp ${FLG}

jumps.o: parse_tree/jumps.cpp ${DBG} ${OPT}
	${CC} -c parse_tree/jumps.cpp ${FLG}

commands.o : parse_tree/commands.cpp ${DBG} ${OPT}
	$(CC) -c parse_tree/commands.cpp ${FLG}

values.o : parse_tree/values.cpp ${DBG} ${OPT}
	$(CC) -c parse_tree/values.cpp ${FLG}

expressions.o : parse_tree/expressions.cpp ${DBG} ${OPT}
	$(CC) -c parse_tree/expressions.cpp ${FLG}

conditions.o : parse_tree/conditions.cpp ${DBG} ${OPT}
	$(CC) -c parse_tree/conditions.cpp ${FLG}

lexer.o: lexer.cpp ${DBG} ${OPT}
	${CC} -c lexer.cpp ${FLG}

parser.o: parser.cpp ${DBG} ${OPT}
	${CC} -c parser.cpp -Wno-write-strings ${FLG}

parser.cpp: parser.y ${DBG} ${OPT}
	bison -o parser.cpp -d parser.y

lexer.cpp: lexer.l ${DBG} ${OPT}
	flex -o lexer.cpp lexer.l

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
