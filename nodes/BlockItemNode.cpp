# include "AllNodes.h"

BlockItemNode::BlockItemNode(Node* decl, Node* stmt)
{
    this->decl = decl;
    this->stmt = stmt;
}

void BlockItemNode::generateCode()
{

}

void BlockItemNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("BlockItemNode\n");
    if (decl)
    {
        decl->show(layer + 1);
    }
    if (stmt)
    {
        stmt->show(layer + 1);
    }
}