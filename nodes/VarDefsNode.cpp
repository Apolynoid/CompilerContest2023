# include "AllNodes.h"

VarDefsNode::VarDefsNode(Node* vardef, Node* next)
{
    this->vardef = vardef;
    this->next = next;
}

void VarDefsNode::generateCode()
{

}

void VarDefsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("VarDefsNode\n");
    vardef->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}