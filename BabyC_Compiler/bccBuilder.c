#include "heading.h"
#include "bccBuilder.h"

char SymTbl[100][10];
int i;
int numSym = 0;
int numNodes = 0;
int vregCount = 0;
int labelCount = 0;
int rootNodeFlg = 0;

void AddDeclaration(char* name){

	for(i=0;i<numSym;i++){
		if(strcmp(&SymTbl[i][0],name)==0){
			yyerror("Symbol already in use!\n");
		}
	}
	strcpy(&SymTbl[numSym][0],name);
	numSym++;
}

ASTNode* MakeAssignNode(ASTNode* target, ASTNode* assign){

	int symMatch = 0;

	for(i=0;i<numSym;i++){
		if(strcmp(&SymTbl[i][0],target->name)==0){
			symMatch = 1;
		}
	}
	if(symMatch != 1)
		yyerror("Symbol undeclared!\n");

	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ASSIGN;
	node->right = assign;
	node->left = target;
	node->middle = NULL;
	numNodes++;
	return node;
}

ASTNode* MakeAddNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ARITH_OP;
	node->op = ADD_OP;
	node->name = "add";
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;
	numNodes++;
	return node;
}

ASTNode* MakeSubNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ARITH_OP;
	node->op = SUB_OP;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;
	numNodes++;
	return node;
}

ASTNode* MakeDivNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ARITH_OP;
	node->op = DIV_OP;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;
	numNodes++;
	return node;
}

ASTNode* MakeMulNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = ARITH_OP;
	node->op = MUL_OP;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;
	numNodes++;
	return node;
}

ASTNode* MakeNumNode(int num){
	int temp;
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = NUM;
	node->num = num;
	node->left = NULL;
	node->right = NULL;
	node->middle = NULL;
	return node;
}

ASTNode* MakeIdentNode(char* name){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = IDENT;
	node->name = name;
	node->left = NULL;
	node->right = NULL;
	node->middle = NULL;	
	for(i=0;i<numSym;i++){
		if(strcmp(&SymTbl[i][0],name)==0){
			node->offset = (int)&SymTbl[i][5];	//allows 5 chars for name, next 5 for values. passing address allows easy writing of values to address.
		}
	}
	numNodes++;
	return node;
}
	
ASTNode* MakeOrNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = LOGIC_OP;
	node->op = OR_OP;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;	
	numNodes++;
	return node;
}	

ASTNode* MakeAndNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = LOGIC_OP;
	node->op = AND_OP;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;	
	numNodes++;
	return node;
}

/*
ASTNode* MakeBoolNode(ASTNode* leftNode, ASTNode* middleNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = middleNode;
	numNodes++;
	return node;
}
*/

ASTNode* MakeIfNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = IF_ST;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;	
	numNodes++;
	return node;
}

ASTNode* MakeIfElseNode(ASTNode* leftNode, ASTNode* middleNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = IFELSE_ST;
	node->left = leftNode;
	node->middle = middleNode;
	node->right = rightNode;
	numNodes++;
	return node;
}

ASTNode* MakeWhileNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = WHILE_ST;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;		
	numNodes++;
	return node;
}

ASTNode* MakeEqNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->op = EQ_OP;
	node->left = leftNode;
	node->right = rightNode; 
	node->middle = NULL;	
	numNodes++;
	return node;
}

ASTNode* MakeNeNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->op = NE_OP;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL; 
	numNodes++;
	return node;
}

ASTNode* MakeGtNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->op = GT_OP;
	node->left = leftNode;
	node->right = rightNode; 
	node->middle = NULL;	
	numNodes++;
	return node;
}

ASTNode* MakeLtNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->op = LT_OP;
	node->left = leftNode;
	node->right = rightNode; 
	node->middle = NULL;	
	numNodes++;
	return node;
}

ASTNode* MakeLeNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->op = LE_OP;
	node->left = leftNode;
	node->right = rightNode; 
	node->middle = NULL;	
	numNodes++;
	return node;
}

ASTNode* MakeGeNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = COMPARE;
	node->op = GE_OP;
	node->left = leftNode;
	node->right = rightNode; 
	node->middle = NULL;
	numNodes++;
	return node;
}

ASTNode* MakeStatementNode(ASTNode* leftNode, ASTNode* rightNode){
	ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
	node->type = STMNT;
	node->left = leftNode;
	node->right = rightNode;
	node->middle = NULL;
	numNodes++;
	return node;
}


void GenerateILOC(ASTNode* node){
	
	int t1;
	int t2;
	int result;

	if(node == NULL)
		return;
	/*
	if(rootNodeFlg==0){
		rootNodeFlg++;
		GenerateILOC(node->left);
		GenerateILOC(node->middle);
		GenerateILOC(node->right);
	}*/

	switch(node->type){
	case STMNT:
		GenerateILOC(node->left);
		GenerateILOC(node->right);
		break;

	case ARITH_OP:
		switch(node->op){
		case ADD_OP:
			GenerateILOC(node->left);
			GenerateILOC(node->right);
			result = GetNextReg();
			node->vreg = result;
			printf("add r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
			break;

		case SUB_OP:
			GenerateILOC(node->left);
			GenerateILOC(node->right);
			result = GetNextReg();
			node->vreg = result;
			printf("sub r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
			break;
			
		case DIV_OP:
			GenerateILOC(node->left);
			GenerateILOC(node->right);
			result = GetNextReg();
			node->vreg = result;
			printf("div r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
			break;

		case MUL_OP:
			GenerateILOC(node->left);
			GenerateILOC(node->right);
			result = GetNextReg();
			node->vreg = result;
			printf("mul r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
			break;
		}
		break;

	case ASSIGN:
		GenerateILOC(node->right);
		printf("Store r%d -> rarp @%d\n", node->right->vreg,node->left->offset);
		break;
	
	case NUM:
		result = GetNextReg();
		node->vreg = result;
		printf("LoadI %d -> r%d\n",node->num,result);
		break;
		
	case IDENT:
		result = GetNextReg();
		node->vreg = result;
		printf("Load rarp,@%d -> r%d\n",node->offset,node->vreg);
		break;
	
	case LOGIC_OP:
		switch(node->op){
		case OR_OP:
			GenerateILOC(node->left);
			GenerateILOC(node->right);
			result = GetNextReg();
			node->vreg = result;
			printf("or r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
			break;

		case AND_OP:
			GenerateILOC(node->left);
			GenerateILOC(node->right);
			result = GetNextReg();
			node->vreg = result;
			printf("and r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
			break;
		}
		break;

	case IF_ST:
		GenerateILOC(node->left);
		printf("cbr r%d -> L%d,L%d\n",node->left->vreg,labelCount,labelCount+1);
		printf("L%d:\n",labelCount);
		labelCount+=2;
		t1 = labelCount-1;			//bookkeeping in case nested loops/ifs
		GenerateILOC(node->right);
		printf("L%d:\n",t1);
		break;

	case IFELSE_ST:
		GenerateILOC(node->left);
		printf("cbr r%d -> L%d,L%d\n",node->left->vreg,labelCount,labelCount+1);
		printf("L%d:\n",labelCount);
		labelCount+=3;
		t1 = labelCount-2;
		t2 = labelCount-1;
		GenerateILOC(node->middle);
		printf("jmpI L%d\n",t2);
		printf("L%d:\n",t1);
		GenerateILOC(node->right);
		printf("L%d:\n",t2);
		break;

	case WHILE_ST:
		printf("L%d:\n",labelCount);
		t1 = labelCount;
		labelCount++;
		GenerateILOC(node->left);
		printf("cbr r%d -> L%d,L%d\n",node->left->vreg,labelCount,labelCount+1);
		printf("L%d:\n",labelCount);
		labelCount+=2;
		t2 = labelCount-1;
		GenerateILOC(node->right);
		printf("jmpI L%d\n",t1);
		printf("L%d:\n",t2);
		break;

	case COMPARE:
		switch(node->op){
			case EQ_OP:
				GenerateILOC(node->left);
				GenerateILOC(node->right);
				result = GetNextReg();
				node->vreg = result;
				printf("cmp_EQ r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
				break;

			case NE_OP:
				GenerateILOC(node->left);
				GenerateILOC(node->right);
				result = GetNextReg();
				node->vreg = result;
				printf("cmp_NE r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
				break;

			case GT_OP:
				GenerateILOC(node->left);
				GenerateILOC(node->right);
				result = GetNextReg();
				node->vreg = result;
				printf("cmp_GT r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
				break;

			case LT_OP:
				GenerateILOC(node->left);
				GenerateILOC(node->right);
				result = GetNextReg();
				node->vreg = result;
				printf("cmp_LT r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
				break;

			case LE_OP:
				GenerateILOC(node->left);
				GenerateILOC(node->right);
				result = GetNextReg();
				node->vreg = result;
				printf("cmp_LE r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
				break;

			case GE_OP:
				GenerateILOC(node->left);
				GenerateILOC(node->right);
				result = GetNextReg();
				node->vreg = result;
				printf("cmp_GE r%d,r%d -> r%d\n",node->left->vreg,node->right->vreg,result);
				break;			
		}
		break;	
	}
}	

 
int GetNextReg(){
	return vregCount++; 
}


