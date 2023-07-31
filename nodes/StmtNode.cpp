# include "AllNodes.h"

StmtNode::StmtNode(Node* lval, Node* exp, Node* block, Node* cond, Node* stmt, Node* elsestmt, int stmttype)
{
    this->lval = lval;
    this->exp = exp;
    this->block = block;
    this->cond = cond;
    this->stmt = stmt;
    this->elsestmt = elsestmt;
    this->stmttype = stmttype;
}

void StmtNode::generateCode()
{

}

void StmtNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("StmtNode %d\n", stmttype);
    if (lval)
    {
        lval->show(layer + 1);
    }
    if (exp)
    {
        exp->show(layer + 1);
    }
    if (block)
    {
        block->show(layer + 1);
    }
    if (cond)
    {
        cond->show(layer + 1);
    }
    if (stmt)
    {
        stmt->show(layer + 1);
    }
    if (elsestmt)
    {
        elsestmt->show(layer + 1);
    }
}