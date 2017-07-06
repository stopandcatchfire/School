//Driver file to call parser and Iloc generator
//


#include "heading.h"
#include "bccBuilder.h"


extern FILE *yyin;
extern int yyparse(void);

ASTNode* gASTRoot;

int main(int argc, char** argv){


	//rhobustness checks
	if(argc != 2){
		printf("USAGE: bcc File_name.bc \n");
		exit(1);
	}

	yyin = fopen(argv[1], "r");

	if(yyin == NULL){
		printf("ERROR: Failed to open input file\n");
		exit(1);
	}	

	yyparse();
	fclose(yyin);
	GenerateILOC(gASTRoot);	
}

