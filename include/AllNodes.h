# ifndef DEF_NODE
# define DEF_NODE

# include <string>
# include <cstdio>

# include "enums.h"

class Node{
protected:
    std::string code;
    bool isCodeGenerated;
public:
    Node();
    std::string getCode();
    void virtual generateCode() = 0;
    void virtual show(int layer);
};

class RootNode:public Node {
public:
	Node* node;

	RootNode(Node* cun);
	void generateCode();
	void show(int layer);
};

class CompUnitNode:public Node {
public:
	Node* decl;
	Node* funcdef;
	Node* next;

	CompUnitNode(Node* decl, Node* funcdef, Node* next);
	void generateCode();
	void show(int layer);
};

class DeclNode:public Node {
public:
	Node* constdecl;
	Node* vardecl;

	DeclNode(Node* constdecl, Node* vardecl);
	void generateCode();
	void show(int layer);
};

class ConstDeclNode:public Node {
public:
	int type;
	Node* constdefs;

	ConstDeclNode(Node* constdefs, int type);
	void generateCode();
	void show(int layer);
};

class ConstDefsNode:public Node {
public:
	Node* constdef;
	Node* next;

	ConstDefsNode(Node* constdef, Node* Next);
	void generateCode();
	void show(int layer);
};

class ConstDefNode:public Node {
public:
	std::string id;
	Node* constarray;
	Node* constinitval;

	ConstDefNode(std::string id, Node* constarray, Node* constinitval);
	void generateCode();
	void show(int layer);
};

class ConstInitValNode:public Node {
public:
	Node* constexp;
	Node* constinitvals;

	ConstInitValNode(Node* constexp, Node* constinitvals);
	void generateCode();
	void show(int layer);
};

class ConstInitValsNode:public Node {
public:
	Node* constinitval;
	Node* next;

	ConstInitValsNode(Node* constinitval, Node* next);
	void generateCode();
	void show(int layer);
};

class ConstArrayListNode:public Node {
public:
	Node* constexp;
	Node* next;

	ConstArrayListNode(Node* constexp, Node* next);
	void generateCode();
	void show(int layer);
};

class ConstExpNode:public Node {
public:
	Node* addexp;

	ConstExpNode(Node* addexp);
	void generateCode();
	void show(int layer);
};

class AddExpNode:public Node {
public:
	Node* addexp;
	int optype;
	Node* mulexp;

	AddExpNode(Node* addexp, int optype, Node* mulexp);
	void generateCode();
	void show(int layer);
};

class MulExpNode:public Node {
public:
	Node* mulexp;
	Node* unaryexp;
	int optype;

	MulExpNode(Node* mulexp, int optype, Node* unaryexp);
	void generateCode();
	void show(int layer);
};

class UnaryExpNode:public Node {
public:
	Node* primaryexp;
	Node* unaryexp;
	Node* funcrparams;
	std::string id;
	int optype;
	bool isCallingFunc;

	UnaryExpNode(Node* primaryexp, std::string id, Node* funcrparams, int optype, Node* unaryexp);
	void generateCode();
	void show(int layer);
};

class PrimaryExpNode:public Node {
public:
	Node* exp;
	Node* lval;
	int intval;
	float floatval;
	int type;

	PrimaryExpNode(Node* exp, Node* lval, int intval, float floatval, int type);
	void generateCode();
	void show(int layer);
};

class FuncRParamsNode:public Node {
public:
	Node* exp;
	Node* next;

	FuncRParamsNode(Node* exp, Node* next);
	void generateCode();
	void show(int layer);
};

class ExpNode:public Node {
public:
	Node* addexp;

	ExpNode(Node* addexp);
	void generateCode();
	void show(int layer);
};

class LValNode:public Node {
public:
	Node* array;
	std::string id;

	LValNode(std::string id, Node* array);
	void generateCode();
	void show(int layer);
};

class ArrayListNode:public Node {
public:
	Node* exp;
	Node* next;

	ArrayListNode(Node* exp, Node* next);
	void generateCode();
	void show(int layer);
};

class VarDeclNode:public Node {
public:
	Node* vardefs;
	int type;

	VarDeclNode(Node* vardefs, int type);
	void generateCode();
	void show(int layer);
};

class VarDefsNode:public Node {
public:
	Node* vardef;
	Node* next;

	VarDefsNode(Node* vardef, Node* next);
	void generateCode();
	void show(int layer);
};

class VarDefNode:public Node {
public:
	Node* constarray;
	Node* initval;
	std::string id;

	VarDefNode(std::string id, Node* constarray, Node* initval);
	void generateCode();
	void show(int layer);
};

class InitValNode:public Node {
public:
	Node* exp;
	Node* initvals;

	InitValNode(Node* exp, Node* initvals);
	void generateCode();
	void show(int layer);
};

class InitValsNode:public Node {
public:
	Node* initval;
	Node* next;

	InitValsNode(Node* initval, Node* next);
	void generateCode();
	void show(int layer);
};

class FuncDefNode:public Node {
public:
	Node* funcfparams;
	Node* block;
	std::string id;
	int type;

	FuncDefNode(int type, std::string id, Node* funcfparams, Node* block);
	void generateCode();
	void show(int layer);
};

class FuncFParamsNode:public Node {
public:
	Node* funcfparam;
	Node* next;

	FuncFParamsNode(Node* funcfparam, Node* next);
	void generateCode();
	void show(int layer);
};

class FuncFParamNode:public Node {
public:
	Node* array;
	std::string id;
	int type;
	bool hasArray;

	FuncFParamNode(int type, std::string id, Node* array, bool hasArray);
	void generateCode();
	void show(int layer);
};

class BlockNode:public Node {
public:
	Node* blockitems;

	BlockNode(Node* blockitems);
	void generateCode();
	void show(int layer);
};

class BlockItemsNode:public Node {
public:
	Node* blockitem;
	Node* next;

	BlockItemsNode(Node* blockitem, Node* next);
	void generateCode();
	void show(int layer);
};

class BlockItemNode:public Node {
public:
	Node* decl;
	Node* stmt;

	BlockItemNode(Node* decl, Node* stmt);
	void generateCode();
	void show(int layer);
};

class StmtNode:public Node {
public:
	Node* lval;
	Node* exp;
	Node* block;
	Node* cond;
	Node* stmt;
	Node* elsestmt;
	int stmttype;

	StmtNode(Node* lval, Node* exp, Node* block, Node* cond, Node* stmt, Node* elsestmt, int stmttype);
	void generateCode();
	void show(int layer);
};

class CondNode:public Node {
public:
	Node* lorexp;

	CondNode(Node* lorexp);
	void generateCode();
	void show(int layer);
};

class LOrExpNode:public Node {
public:
	Node* lorexp;
	Node* landexp;

	LOrExpNode(Node* lorexp, Node* landexp);
	void generateCode();
	void show(int layer);
};

class LAndExpNode:public Node {
public:
	Node* landexp;
	Node* eqexp;

	LAndExpNode(Node* landexp, Node* eqexp);
	void generateCode();
	void show(int layer);
};

class EqExpNode:public Node {
public:
	Node* eqexp;
	Node* relexp;
	int optype;

	EqExpNode(Node* eqexp, int optype, Node* relexp);
	void generateCode();
	void show(int layer);
};

class RelExpNode:public Node {
public:
	Node* relexp;
	Node* addexp;
	int optype;

	RelExpNode(Node* relexp, int optype, Node* addexp);
	void generateCode();
	void show(int layer);
};

# endif