# include "AllNodes.h"

FuncRParamsNode::FuncRParamsNode(Node* exp, Node* next)
{
    this->exp = exp;
    this->next = next;
}

void FuncRParamsNode::generateCode()
{

}

void FuncRParamsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("FuncRParams\n");
    exp->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}