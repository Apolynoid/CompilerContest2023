# include "AllNodes.h"

ConstArrayListNode::ConstArrayListNode(Node* constexp, Node* next)
{
    this->constexp = constexp;
    this->next = next;
}

void ConstArrayListNode::generateCode()
{

}

void ConstArrayListNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstArrayListNode\n");
    constexp->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}