# include "AllNodes.h"

CondNode::CondNode(Node* lorexp)
{
    this->lorexp = lorexp;
}

void CondNode::generateCode()
{

}

void CondNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("CondNode\n");
    lorexp->show(layer + 1);
}