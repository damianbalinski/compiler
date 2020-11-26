main:
	bison --debug -d calculator.y
	flex calculator.l
	gcc -o calculator arythmetic.c calculator.tab.c lex.yy.c

clean:
	rm calculator calculator.tab.c calculator.tab.h lex.yy.c