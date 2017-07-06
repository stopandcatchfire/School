/*Scanner for a toy C language 
/*Nick Wantz CSc151 Fall 2016*/

%{
#include "heading.h"
#include "bccBuilder.h"
#include "babyC.tab.h"

void yyerror (const char *s){
	printf("Error on line %d: %s.\n", yylineno, s);
	exit(1);
}

%}

 
%option yylineno

%option noyywrap

%%

"," return ',';
";" return ';';
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"<" return '<';
">" return '>';
"=" return '=';
"(" return '(';
")" return ')';
"{" return '{';
"}" return '}';

"||" return OR;
"&&" return AND; 
"==" return EQ;
"!=" return NE;
"<=" return LE;
">=" return GE;

"int" return INT;
"main" return MAIN;
"if"  return IF;
"else" return ELSE;
"while" return WHILE;

[a-z|A-Z]([a-z]|[A-Z]|[0-9])*  yylval.string = strdup(yytext); return IDENTIFIER; //Identifier

0|[1-9][0-9]*	yylval.num = atoi(yytext); return NUMBER; //Number

[ \t\n]+		//Whitespace is ignored

.           printf( "ERROR on Line %d: Unrecognized token \n", yylineno ); exit(1); //No match. Fatal error

%%
