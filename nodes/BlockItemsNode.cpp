# include "AllNodes.h"

BlockItemsNode::BlockItemsNode(Node* blockitem, Node* next)
{
    this->blockitem = blockitem;
    this->next = next;
}

void BlockItemsNode::generateCode()
{

}

void BlockItemsNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("BlockItems\n");
    blockitem->show(layer + 1);
    if (next)
    {
        next->show(layer);
    }
}