# include "AllNodes.h"

ConstDefNode::ConstDefNode(std::string id, Node* constarray, Node* constinitval)
{
    this->id = id;
    this->constarray = constarray;
    this->constinitval = constinitval;
}

void ConstDefNode::generateCode()
{

}

void ConstDefNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstDefNode %s\n", id.c_str());
    if (constarray)
    {
        constarray->show(layer + 1);
    }
    constinitval->show(layer + 1);
}