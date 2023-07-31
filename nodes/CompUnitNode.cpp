# include "AllNodes.h"

CompUnitNode::CompUnitNode(Node* decl, Node* funcdef, Node* next)
{
    this->decl = decl;
    this->funcdef = funcdef;
    this->next = next;
}

void CompUnitNode::generateCode()
{

}

void CompUnitNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("CompUnitNode\n");
    if (decl)
    {
        decl->show(layer + 1);
    }
    if (funcdef)
    {
        funcdef->show(layer + 1);
    }
    if (next)
    {
        next->show(layer);
    }
}