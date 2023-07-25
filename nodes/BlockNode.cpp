# include "AllNodes.h"

BlockNode::BlockNode(Node* blockitems)
{
    this->blockitems = blockitems;
}

void BlockNode::generateCode()
{

}

void BlockNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("BlockNode\n");
    if (blockitems)
    {
        blockitems->show(layer + 1);
    }
}