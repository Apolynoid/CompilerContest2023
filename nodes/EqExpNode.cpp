# include "AllNodes.h"

EqExpNode::EqExpNode(Node* eqexp, int optype, Node* relexp)
{
    this->eqexp = eqexp;
    this->optype = optype;
    this->relexp = relexp;
}

void EqExpNode::generateCode()
{

}

void EqExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("EqExpNode %d\n", optype);
    if (eqexp)
    {
        eqexp->show(layer + 1);
    }
    relexp->show(layer + 1);
}