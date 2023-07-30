# include "AllNodes.h"

VarDeclNode::VarDeclNode(Node* vardefs, int type)
{
    this->vardefs = vardefs;
    this->type = type;
}

void VarDeclNode::generateCode()
{

}

void VarDeclNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("VarDeclNode %d\n", type);
    vardefs->show(layer + 1);
}