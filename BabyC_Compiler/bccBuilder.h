//bccBuilder Header File
//



#ifndef BCCBUILDER_H
#define BCCBUILDER_H

typedef enum{STMNT, ARITH_OP, LOGIC_OP, COMPARE, ASSIGN, IDENT, NUM, IF_ST, IFELSE_ST, WHILE_ST} ASTNodeType;

typedef enum{ADD_OP, MUL_OP, DIV_OP, SUB_OP, OR_OP, AND_OP, EQ_OP, NE_OP, LT_OP, GT_OP, LE_OP, GE_OP} ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type;
	ASTOp op;
	int num;
	char *name;
	int vreg;
	int offset;
	ASTNode* left;
	ASTNode* right;
	ASTNode* middle;
};
	


ASTNode* MakeAssignNode(ASTNode* target, ASTNode* rightNode);
ASTNode* MakeAddNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeSubNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeDivNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeMulNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeNumNode(int num);
ASTNode* MakeIdentNode(char* name);
ASTNode* MakeOrNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeAndNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeBoolNode(ASTNode* leftNode, ASTNode* middleNode, ASTNode* rightNode);
ASTNode* MakeIfNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeIfElseNode(ASTNode* leftNode, ASTNode* middleNode, ASTNode* rightNode);
ASTNode* MakeWhileNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeEqNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeNeNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeGtNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeLtNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeLeNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeGeNode(ASTNode* leftNode, ASTNode* rightNode);
ASTNode* MakeStatementNode(ASTNode* leftNode, ASTNode* rightNode);

void AddDeclaration(char* name);

void GenerateILOC(ASTNode* node);

#endif
