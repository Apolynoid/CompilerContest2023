# include "AllNodes.h"

FuncFParamNode::FuncFParamNode(int type, std::string id, Node* array, bool hasArray)
{
    this->type = type;
    this->id = id;
    this->array = array;
    this->hasArray = hasArray;
}

void FuncFParamNode::generateCode()
{

}

void FuncFParamNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("FuncFParamNode %d %s %d\n", type, id.c_str(), hasArray);
    if (array)
    {
        array->show(layer + 1);
    }
}