# include "AllNodes.h"

VarDefNode::VarDefNode(std::string id, Node* constarray, Node* initval)
{
    this->id = id;
    this->constarray = constarray;
    this->initval = initval;
}

void VarDefNode::generateCode()
{

}

void VarDefNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("VarDefNode %s\n", id.c_str());
    if (constarray)
    {
        constarray->show(layer + 1);
    }
    if (initval)
    {
        initval->show(layer + 1);
    }
}