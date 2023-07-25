# include "AllNodes.h"

ConstInitValNode::ConstInitValNode(Node* constexp, Node* constinitvals)
{
    this->constexp = constexp;
    this->constinitvals = constinitvals;
}

void ConstInitValNode::generateCode()
{

}

void ConstInitValNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstInitValNode\n");
    if (constexp)
    {
        constexp->show(layer + 1);
    }
    if (constinitvals)
    {
        constinitvals->show(layer + 1);
    }
}