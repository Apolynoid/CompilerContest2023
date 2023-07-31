# include "AllNodes.h"

InitValsNode::InitValsNode(Node* initval, Node* next)
{
    this->initval = initval;
    this->next = next;
}

void InitValsNode::generateCode()
{

}

void InitValsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("InitValsNode\n");
    initval->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}