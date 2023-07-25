# include "AllNodes.h"

MulExpNode::MulExpNode(Node* mulexp, int optype, Node* unaryexp)
{
    this->mulexp = mulexp;
    this->optype = optype;
    this->unaryexp = unaryexp;
}

void MulExpNode::generateCode()
{

}

void MulExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("MulExpNode %d\n", optype);
    if (mulexp)
    {
        mulexp->show(layer + 1);
    }
    unaryexp->show(layer + 1);
}