# include "AllNodes.h"

UnaryExpNode::UnaryExpNode(Node* primaryexp, std::string id, Node* funcrparams, int optype, Node* unaryexp)
{
    this->primaryexp = primaryexp;
    this->id = id;
    this->funcrparams = funcrparams;
    this->optype = optype;
    this->unaryexp = unaryexp;
    if(id == "")
    {
        isCallingFunc = false;
    }
    else
    {
        isCallingFunc = true;
    }
}

void UnaryExpNode::generateCode()
{

}

void UnaryExpNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("UnaryExpNode %s %d\n", id.c_str(), optype);
    if (primaryexp)
    {
        primaryexp->show(layer + 1);
    }
    if (funcrparams)
    {
        funcrparams->show(layer + 1);
    }
    if (unaryexp)
    {
        unaryexp->show(layer + 1);
    }
}