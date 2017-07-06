#Makefile


all: Parser Scanner BCCBuilder
	gcc babyC.tab.o lex.yy.o driver.o bccBuilder.o -o bcc

BCCBuilder: bccBuilder.o driver.o

Scanner: babyC.lex
	flex babyC.lex
	gcc -c lex.yy.c

Parser: babyC.y
	bison -d babyC.y
	gcc -c babyC.tab.c

clean:
	rm -f *.o

%.o: %.c 
	gcc -c $<
