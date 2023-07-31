# include "AllNodes.h"

RelExpNode::RelExpNode(Node* relexp, int optype, Node* addexp)
{
    this->relexp = relexp;
    this->optype = optype;
    this->addexp = addexp;
}

void RelExpNode::generateCode()
{

}

void RelExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("RelExpNode\n");
    if (relexp)
    {
        relexp->show(layer + 1);
    }
    addexp->show(layer + 1);
}