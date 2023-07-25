# include "AllNodes.h"

ArrayListNode::ArrayListNode(Node* exp, Node* next)
{
    this->exp = exp;
    this->next = next;
}

void ArrayListNode::generateCode()
{

}

void ArrayListNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ArrayListNode\n");
    exp->show(layer + 1);
    if (next)
    {
        next->show(layer + 1);
    }
}