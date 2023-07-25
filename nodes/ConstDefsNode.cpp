# include "AllNodes.h"

ConstDefsNode::ConstDefsNode(Node* constdef, Node* Next)
{
    this->constdef = constdef;
    this->next = next;
}

void ConstDefsNode::generateCode()
{

}

void ConstDefsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstDefsNode\n");
    constdef->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}