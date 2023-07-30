# include "AllNodes.h"

FuncFParamsNode::FuncFParamsNode(Node* funcfparam, Node* next)
{
    this->funcfparam = funcfparam;
    this->next = next;
}

void FuncFParamsNode::generateCode()
{

}

void FuncFParamsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("FuncFParams\n");
    funcfparam->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}