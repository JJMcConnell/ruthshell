EXECNAME = shell

all: y.tab.o lex.yy.o util.o ruthshell.o arglist.o
	gcc -o $(EXECNAME) y.tab.o lex.yy.o util.o ruthshell.o \
		arglist.o

y.tab.o: y.tab.c y.tab.h ruthshell.o arglist.o
	gcc -c y.tab.c

y.tab.h: y.tab.c

y.tab.c: parser.y
	bison -dy parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: lexer.l
	flex lexer.l

util.o: util.c
	gcc -c util.c

arglist.o: arglist.c
	gcc -c arglist.c

ruthshell.o: ruthshell.c
	gcc -c ruthshell.c

.PHONY: clean
clean:
	rm -f *.o *.yy.* *.tab.* $(EXECNAME) *~
