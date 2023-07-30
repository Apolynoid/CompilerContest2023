# include "AllNodes.h"

ConstExpNode::ConstExpNode(Node* addexp)
{
    this->addexp = addexp;
}

void ConstExpNode::generateCode()
{

}

void ConstExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstExpNode\n");
    addexp->show(layer + 1);
}