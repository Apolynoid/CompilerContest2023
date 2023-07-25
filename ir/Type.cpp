#include"Type.h"

std::map<int, std::string> change_type_to_string = { {INTTYPE, "i"}, {FLOATTYPE, "float"}, {VOIDTYPE, "void"}, {LABELTYPE, "label"}};

Type::Type(int type_id){
    this->type_id = type_id;
}

std::string Type::print() {
    return change_type_to_string[this->type_id];
}

IntType::IntType(int bits) : Type(INTTYPE){
    this->bits = bits;
}

std::string IntType::print() {
    return change_type_to_string[this->type_id] + std::to_string(this->bits);
}

ArrayType::ArrayType(Type* contained, int num) : Type(ARRAYTYPE){
    this->num = num;
    this->contained = contained;
}

std::string ArrayType::print() {
    return "[" + std::to_string(this->num) + " x " + this->contained->print() + "]";
}

PType::PType(Type* contained) : Type(POINTTYPE) {
    this->contained = contained;
}

std::string PType::print() {
    return this->contained->print() + "*";
}

FuncType::FuncType(Type* result, std::vector<Type*> args) : Type(FUNCTIONTYPE) {
    this->result = result;
    int size_ = args.size();
    for (int i = 0; i < size_; i++) {
        this->args.push_back(args[i]);
    }
}

std::string FuncType::print() {
    std::string temp = this->result->print() + "(";
    int size_ = this->args.size();
    for (int i = 0; i < size_; i++) {
        temp = temp + this->args[i]->print();
        if (i != size_) {
            temp = temp + ", ";
        }
    }
    return temp + ")";
}