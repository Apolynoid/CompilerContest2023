# include "AllNodes.h"

ConstInitValsNode::ConstInitValsNode(Node* constinitval, Node* next)
{
    this->constinitval = constinitval;
    this->next = next;
}

void ConstInitValsNode::generateCode()
{

}

void ConstInitValsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstInitValsNode\n");
    constinitval->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}