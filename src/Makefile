EXECNAME = ruthshell

all: y.tab.o lex.yy.o ruthshell.o
	gcc -o $(EXECNAME) y.tab.o lex.yy.o ruthshell.o

y.tab.o: y.tab.c y.tab.h
	gcc -c y.tab.c

y.tab.h: y.tab.c

y.tab.c: parser.y
	bison -dy parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: lexer.l
	flex lexer.l

ruthshell.o: ruthshell.c
	gcc -c ruthshell.c

.PHONY: clean
clean:
	rm -f *.o *.yy.* *.tab.* $(EXECNAME) *~
