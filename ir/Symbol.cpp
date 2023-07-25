#include "Symbol.h"

bool Symbol::push(std::string name, Base* base) {
    bool result;
    result = (symbol.insert({ name, base })).second;
    return result;
}

Base* Symbol::find(std::string name) {
    auto item = symbol.find(name);
    if (item != symbol.end()) {
        return item->second;
    }
    return nullptr;
}