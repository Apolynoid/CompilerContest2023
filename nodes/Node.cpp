# include "AllNodes.h"

Node::Node()
{
    code = "";
    isCodeGenerated = false;
}

std::string Node::getCode()
{
    if (isCodeGenerated)
    {
        return code;
    }
    generateCode();
    return code;
}

void Node::show(int layer)
{
    for(int i=0;i<layer;i++)
    {
        printf("%s", TAB);
    }
    printf("Node\n");
}