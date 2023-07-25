# include "AllNodes.h"

RootNode::RootNode(Node* cun)
{
    node = cun;
}

void RootNode::generateCode()
{

}

void RootNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("RootNode\n");
    node->show(layer + 1);
}