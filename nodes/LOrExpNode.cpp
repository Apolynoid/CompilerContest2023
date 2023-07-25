# include "AllNodes.h"

LOrExpNode::LOrExpNode(Node* lorexp, Node* landexp)
{
    this->lorexp = lorexp;
    this->landexp = landexp;
}

void LOrExpNode::generateCode()
{

}

void LOrExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("LOrExpNode\n");
    if (lorexp)
    {
        lorexp->show(layer + 1);
    }
    landexp->show(layer + 1);
}