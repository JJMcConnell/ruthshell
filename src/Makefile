EXECNAME = shell

all: y.tab.o lex.yy.o util.o ruthshell.o arglist.o linkedlist.o
	gcc -g -o $(EXECNAME) y.tab.o lex.yy.o util.o ruthshell.o \
		arglist.o linkedlist.o

y.tab.o: y.tab.c y.tab.h ruthshell.o arglist.o
	gcc -g -c y.tab.c

y.tab.h: y.tab.c

y.tab.c: parser.y
	bison -dy parser.y

lex.yy.o: lex.yy.c
	gcc -g -c lex.yy.c

lex.yy.h: lex.yy.c

lex.yy.c: lexer.l
	flex --header-file='lex.yy.h' lexer.l

util.o: util.c lex.yy.h
	gcc -g -c util.c

lex.yy.h: lex.yy.o

arglist.o: arglist.c
	gcc -g -c arglist.c

ruthshell.o: ruthshell.c linkedlist.o
	gcc -g -c ruthshell.c

linkedlist.o: linkedlist.c
	gcc -g -c linkedlist.c

.PHONY: clean
clean:
	rm -f *.o *.yy.* *.tab.* $(EXECNAME) *~
