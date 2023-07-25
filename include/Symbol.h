#pragma once
#include<map>
#include "Ir.h"

class Symbol {
public:
    std::map<std::string, Base*> symbol;
    bool push(std::string name, Base* value);
    Base* find(std::string name);
};