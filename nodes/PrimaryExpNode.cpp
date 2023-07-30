# include "AllNodes.h"

PrimaryExpNode::PrimaryExpNode(Node* exp, Node* lval, int intval, float floatval, int type)
{
    this->exp = exp;
    this->lval = lval;
    this->intval = intval;
    this->floatval = floatval;
    this->type = type;
}

void PrimaryExpNode::generateCode()
{

}

void PrimaryExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("PrimaryExpNode %d %f %d\n", intval, floatval, type);
    if (exp)
    {
        exp->show(layer + 1);
    }
    if (lval)
    {
        lval->show(layer + 1);
    }
}