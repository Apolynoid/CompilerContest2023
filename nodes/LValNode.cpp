# include "AllNodes.h"

LValNode::LValNode(std::string id, Node* array)
{
    this->id = id;
    this->array = array;
}

void LValNode::generateCode()
{

}

void LValNode::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("LValNode %s\n", id.c_str());
    if (array)
    {
        array->show(layer + 1);
    }
}