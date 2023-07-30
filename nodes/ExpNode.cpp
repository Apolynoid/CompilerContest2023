# include "AllNodes.h"

ExpNode::ExpNode(Node* addexp)
{
    this->addexp = addexp;
}

void ExpNode::generateCode()
{

}

void ExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ExpNode\n");
    addexp->show(layer + 1);
}