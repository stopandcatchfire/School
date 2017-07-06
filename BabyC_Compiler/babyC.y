/*///////////////////////////////////////////////////
Written by Nick Wantz
CSc 151
Assignment 5 - BabyC Compiler

11/28/16

///////////////////////////////////////////////////*/



%{
#include "heading.h"
#include "bccBuilder.h"
extern int yyerror(const char *);
extern int yylex();
extern ASTNode* gASTRoot;
%}

%token EQ "=="
%token NE "!="
%token LE "<="
%token GE ">="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"


%union
{
	ASTNode* node;
	int num;
	char* string;
}

%token <string> IDENTIFIER
%token <num> NUMBER

//type for non-terminals
%type <node> DeclarationList
%type <node> Declaration
%type <node> StatementList
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> If
%type <node> Condition
%type <node> Compare
%type <node> While
%type <node> Logic
%type <node> Test

%%

//Grammar for BabyC

Goal: MAIN '(' ')' '{' DeclarationList StatementList '}'	{gASTRoot = $6;} 
;

DeclarationList: 				{$$ = NULL;}				
		| Declaration DeclarationList 			
;

Declaration: "int" IDENTIFIER ';' {AddDeclaration($2);}
;

StatementList: 					{$$ = NULL;}			
		| Statement StatementList	{$$ = MakeStatementNode($1,$2);}
;

Statement: Assignment		{$$ = $1;}
	| If			{$$ = $1;}	
	| While			{$$ = $1;}
;

Assignment: IDENTIFIER '=' Expr ';' {$$ = MakeAssignNode(MakeIdentNode($1),$3);}
;

Expr: 	Term			{$$ = $1}
	| Expr '+' Term		{$$ = MakeAddNode($1,$3);}
	| Expr '-' Term		{$$ = MakeSubNode($1,$3);}
;

Term: 	Factor			{$$ = $1;}
	| Term '*' Factor	{$$ = MakeMulNode($1,$3);}
	| Term '/' Factor	{$$ = MakeDivNode($1,$3);}
;

Factor:	'(' Expr ')'		{$$ = $2;}
	| NUMBER		{$$ = MakeNumNode($1);}
	| IDENTIFIER		{$$ = MakeIdentNode($1);}
;

If:	"if" '(' Condition ')' '{' StatementList '}'					{$$ = MakeIfNode($3,$6);}
	| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}'	{$$ = MakeIfElseNode($3,$6,$10);}
;

Condition: Compare				{$$ = $1;}
	|  Condition OR Compare			{$$ = MakeOrNode($1,$3);}
/*	| '(' Condition ')' OR '(' Compare ')'	{$$ = MakeOrNode($2,$6);}*/
;

Compare: Logic					{$$ = $1;}
	| Compare AND Logic			{$$ = MakeAndNode($1,$3);}
/*	| '(' Compare ')' AND '(' Logic ')'	{$$ = MakeAndNode($2,$6);}*/
;

Logic: '(' Test ')'		{$$ = $2;}
	| Test			{$$ = $1;}
;

Test: Expr EQ Expr		{$$ = MakeEqNode($1,$3);}
	| Expr NE Expr		{$$ = MakeNeNode($1,$3);}
	| Expr '>' Expr		{$$ = MakeGtNode($1,$3);}
	| Expr '<' Expr		{$$ = MakeLtNode($1,$3);}
	| Expr LE Expr		{$$ = MakeLeNode($1,$3);}
	| Expr GE Expr		{$$ = MakeGeNode($1,$3);}
;

While: "while" '(' Condition ')' '{' StatementList '}' {$$ = MakeWhileNode($3,$6);}
;


