EXECNAME = shell

all: y.tab.o lex.yy.o util.o ruthshell.o arglist.o alias.o \
	 variable.o
	gcc -g -o $(EXECNAME) y.tab.o lex.yy.o util.o ruthshell.o \
		arglist.o alias.o variable.o

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

ruthshell.o: ruthshell.c alias.o
	gcc -g -c ruthshell.c

alias.o: alias.c
	gcc -g -c alias.c

variable.o: variable.c
	gcc -g -c variable.c


.PHONY: clean
clean:
	rm -f *.o *.yy.* *.tab.* $(EXECNAME) *~
