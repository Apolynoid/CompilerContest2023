# include "AllNodes.h"

LAndExpNode::LAndExpNode(Node* landexp, Node* eqexp)
{
    this->landexp = landexp;
    this->eqexp = eqexp;
}

void LAndExpNode::generateCode()
{

}

void LAndExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("LAndExpNode\n");
    if (landexp)
    {
        landexp->show(layer + 1);
    }
    eqexp->show(layer + 1);
}