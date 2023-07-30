# include "AllNodes.h"

InitValNode::InitValNode(Node* exp, Node* initvals)
{
    this->exp = exp;
    this->initvals = initvals;
}

void InitValNode::generateCode()
{

}

void InitValNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("InitValNode\n");
    if (exp)
    {
        exp->show(layer+1);
    }
    if (initvals)
    {
        initvals->show(layer + 1);
    }
}