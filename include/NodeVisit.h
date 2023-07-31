#pragma once
#include <vector>

#include "AllNodes.h"
#include "Symbol.h"

using std::vector;
using std::pair;

class NodeVisit{
public:
    Module* module;
    vector<Symbol*> Sym;

    NodeVisit();

    Module* getModule();

    void visit(RootNode* node);
    void visit(CompUnitNode* node);
    void visit(DeclNode* node);
    void visit(ConstDeclNode* node);
    void visit(Type* type, ConstDefsNode* node);
    void visit(Type* type, ConstDefNode* node);
    Base* visit(ConstInitValNode* node);
    void visit(ConstInitValsNode* node, vector<ConstInitValNode*>& arrays);
    void visit(ConstArrayListNode* node, vector<int>& indexs);
    Base* visit(ConstExpNode* node);
    Base* visit(AddExpNode* node, bool is_const);
    Base* visit(MulExpNode* node, bool is_const);
    Base* visit(UnaryExpNode* node, bool is_const);
    Base* visit(PrimaryExpNode* node, bool is_const);
    void visit(FuncRParamsNode* node, vector<Base*>& args);
    Base* visit(ExpNode* node, bool is_const);
    Base* visit(LValNode* node, bool is_left_value);
    void visit(ArrayListNode* node, vector<int>& indexs, bool is_const);
    void visit(ArrayListNode* node, vector<Base*>& indexs, bool is_const);
    void visit(VarDeclNode* node);
    void visit(Type* type, VarDefsNode* node);
    void visit(Type* type, VarDefNode* node);
    Base* visit(InitValNode* node, bool is_const);
    void visit(InitValsNode* node, vector<InitValNode*>& arrays);
    void visit(FuncDefNode* node);
    void visit(FuncFParamsNode* node, vector<pair<Type*, std::string>>& params);
    void visit(FuncFParamNode* node, vector<pair<Type*, std::string>>& params);
    void visit(BlockNode* node);
    void visit(BlockItemsNode* node);
    void visit(BlockItemNode* node);
    Base* visit(StmtNode* node);
    Base*visit(CondNode* node);
    Base*visit(LOrExpNode* node);
    Base*visit(LAndExpNode* node);
    Base*visit(EqExpNode* node);
    Base*visit(RelExpNode* node);
};