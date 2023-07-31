# include "AllNodes.h"

DeclNode::DeclNode(Node* constdecl, Node* vardecl)
{
    this->constdecl = constdecl;
    this->vardecl = vardecl;
}

void DeclNode::generateCode()
{

}

void DeclNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("DeclNode\n");
    if (constdecl)
    {
        constdecl->show(layer + 1);
    }
    if (vardecl)
    {
        vardecl->show(layer + 1);
    }
}