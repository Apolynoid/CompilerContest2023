#pragma once
#include <vector>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include "enums.h"
#include "Type.h"

extern IntType* intType1;
extern IntType* intType8;
extern IntType* intType32;
extern Type* floatType;
extern Type* labelType;
extern Type* voidType;
extern std::map<Type*, PType*> pointer_map;
extern std::map<std::pair<Type*, int>, ArrayType*> array_map;

extern PType* get_ptype(Type* contained);
extern ArrayType* get_atype(Type* contained, int num);

class Module;
class BasicBlock;
class Instr;
class Function;
class Const;

class Base {
public:
    Type* type;
    std::string name;

    Base(Type* type, const std::string& name = "");
    virtual std::string print();
};

class GlobalVar : public Base {
public:
    bool is_const;
    Const* value;

    GlobalVar(std::string name, Module* module, Type* type, bool is_const, Const* value = nullptr);
    std::string print();
};

class Arg : public Base {
public:
    Function* parent;
    int no;

    Arg(Type* type, const std::string& name = "", Function* f = nullptr, int no = 0);
    std::string print();
};

class Function : public Base {
public:
    std::vector<BasicBlock*> basic_blocks;
    std::vector<Arg*> args;
    std::map<std::string, Base*> allocas;
    Module* parent;
    int label_cnt;
    int v_count;
    int arg_count;
    int alloca_num;

    Function(FuncType* type, const std::string& name, Module* parent);
    std::string print();
    void add_bb(BasicBlock* bb);
    Type* get_retype() const;
    bool is_decl();
    void remove_bb(BasicBlock* bb);
    BasicBlock* get_retbb();
};

class Instr : public Base {
public:
    BasicBlock* parent;
    int op_id;
    int num;
    std::vector<Base*> opes;

    Instr(Type* type, int id, int num, BasicBlock* parent);
    Instr(Type* type, int id, int num);
    Base* get_ope(int i) const;
    void set_ope(int i, Base* value);
    virtual std::string print();
};

class BasicBlock : public Base {
public:
    std::list<Instr*> instr_list;
    Function* parent;
    std::vector<BasicBlock*> pre_bbs;
    std::vector<BasicBlock*> succ_bbs;

    BasicBlock(Module* m, const std::string& name, Function* parent);

    void add_instr(Instr* instr);
    void add_instr_front(Instr* instr);
    bool add_instr_before_last(Instr* instr);

    void add_pre_bb(BasicBlock* bb);
    void add_succ_bb(BasicBlock* bb);

    void remove_pre_bb(BasicBlock* bb);
    void remove_succ_bb(BasicBlock* bb);

    Instr* get_last();

    std::string print();
    bool operator==(const BasicBlock& other) const{
        return name == other.name && instr_list == other.instr_list;
    }
};
namespace std {
    template<>
    struct hash<BasicBlock> {
        size_t operator()(const BasicBlock& bb) const {
            size_t h = hash<string>()(bb.name);
            for (auto instr : bb.instr_list) {
                h ^= hash<string>()(instr->print());
            }
            return h;
        }
    };
}

class Module {
public:
    std::vector<GlobalVar*> global_list;
    std::vector<Function*> func_list;

    Module();
    std::string print();
    void add_globalvar(GlobalVar* g);
    void add_func(Function* f);
    Function* get_main();
};

class Const : public Base {
public:
    Const(Type* type, const std::string& name = "");
};

class ConstNumber : public Const {
public:
    float value;
    bool is_int;

    ConstNumber(Type* type, float value, bool is_int);
    std::string print();
};

class ConstArray : public Const {
public:
    std::vector<Const*> carr;

    ConstArray(ArrayType* type, const std::vector<Const*>& value);
    std::string print();
};

class ConstZero : public Const {
public:
    ConstZero(Type* type);
    std::string print();
};

class BinaryInst : public Instr {
public:
    BinaryInst(Type* type, int op, Base* x1, Base* x2, BasicBlock* bb);
    std::string print();
};

class ICmpInst : public Instr {
public:
    int icmp_op;

    ICmpInst(int op, Base* x1, Base* x2, BasicBlock* bb);
    std::string print();
};

class FCmpInst : public Instr {
public:
    int fcmp_op;

    FCmpInst(int op, Base* x1, Base* x2, BasicBlock* bb);
    std::string print();
};

class CallInst : public Instr {
public:
    CallInst(Function* func, std::vector<Base*> args, BasicBlock* bb);
    std::string print();
};

class BranchInst : public Instr {
public:
    BranchInst(Base* cond, BasicBlock* if_true, BasicBlock* if_false, BasicBlock* bb);
    BranchInst(BasicBlock* if_true, BasicBlock* bb);
    std::string print();
};

class ReturnInst : public Instr {
public:
    ReturnInst(Base* value, BasicBlock* bb);
    ReturnInst(BasicBlock* bb);
    std::string print();
};

class GetElementPtrInst : public Instr {
public:
    GetElementPtrInst(Base* p, std::vector<Base*> indexs, BasicBlock* bb);
    std::string print();
};

class StoreInst : public Instr {
public:
    StoreInst(Base* value, Base* p, BasicBlock* bb);
    std::string print();
};

class LoadInst : public Instr {
public:
    LoadInst(Base* p, BasicBlock* bb);
    std::string print();
};

class AllocaInst : public Instr {
public:
    Type* alloc_type;

    AllocaInst(Type* type, BasicBlock* bb);
    std::string print();
};

class CastInst : public Instr {
public:
    Type* change_to_type;

    CastInst(int op, Base* value, Type* type, BasicBlock* bb);
    std::string print();
};