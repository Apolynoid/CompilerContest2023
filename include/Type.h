#pragma once
#include "enums.h"
#include <vector>
#include <string>
#include <map>

class Type {
public:
    int type_id;

    Type(int type_id);
    virtual std::string print();
};

class IntType : public Type {
public:
    int bits;

    IntType(int bits);
    std::string print();
};

class ArrayType : public Type {
public:
    int size;
    int num;
    Type* contained;

    ArrayType(Type* contained, int num);
    std::string print();
};

class PType : public Type {
public:
    Type* contained;

    PType(Type* contained);
    std::string print();
};

class FuncType : public Type {
public:
    Type* result;
    std::vector<Type*> args;

    FuncType(Type* result, std::vector<Type*> args);
    std::string print();
};