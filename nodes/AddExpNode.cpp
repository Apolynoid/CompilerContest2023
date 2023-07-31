# include "AllNodes.h"

AddExpNode::AddExpNode(Node* addexp, int optype, Node* mulexp)
{
    this->addexp = addexp;
    this->optype = optype;
    this->mulexp = mulexp;
}

void AddExpNode::generateCode()
{

}

void AddExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("AddExpNode %d\n", optype);
    if (addexp)
    {
        addexp->show(layer + 1);
    }
    mulexp->show(layer + 1);
}