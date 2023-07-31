# include "AllNodes.h"

ConstDeclNode::ConstDeclNode(Node* constdefs, int type)
{
    this->constdefs = constdefs;
    this->type = type;
}

void ConstDeclNode::generateCode()
{

}

void ConstDeclNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("ConstDeclNode type:%d\n", type);
    constdefs->show(layer + 1);
}