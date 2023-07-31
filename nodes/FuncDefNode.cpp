# include "AllNodes.h"

FuncDefNode::FuncDefNode(int type, std::string id, Node* funcfparams, Node* block)
{
    this->type = type;
    this->id = id;
    this->funcfparams = funcfparams;
    this->block = block;
}

void FuncDefNode::generateCode()
{

}

void FuncDefNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("FuncFParams %s %d\n", id.c_str(), type);
    if (funcfparams)
    {
        funcfparams->show(layer + 1);
    }
    block->show(layer + 1);
}