#ifndef DEF_GENERATOR
#define DEF_GENERATOR

#include "Ir.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "RVBlock.h"

using namespace std;

extern int GetRegFromIRV(string IRV);
struct Generator;
enum CMP_Type {
    eq, ne, sgt, sge, slt, sle
};
struct CMP_Context {
    CMP_Type type;
    Register r1,r2;
    RVBlock* true_bb;
    RVBlock* false_bb;
};

class RVFunction {
private:
    string name;
    RVBlock* start;
    vector<unique_ptr<RVBlock>> blocks;
    vector<Register> argu_regs;
    unordered_map<string,StackObj*> name2stackobj;
    unordered_map<StackObj*, std::string> stackobj2name;
    std::unordered_map<Register,StackObj*> reg2stack;
    int stack_size = 0;

public:
    void GenerateRiscv(stringstream &out){
        out<<name<<":\n";
       // start->GenerateRiscv(out);
        for(int i = 1;i<blocks.size();i++){
            out<<blocks[i]->name<<":\n";
            blocks[i]->GenerateRiscv(out);
        }
    }
    RVFunction(string name, Function* IRfunc,Generator* gene);
    void pushIfSave(Register reg,int i);
    void pop(int i);
    void pushTemp(int i);
    void popTemp(int i);
};
class Generator {
private:
    Module *module;
    vector<unique_ptr<RVFunction>> functions;
 
    unordered_map<string,CMP_Context> cmp_context;
    int num_block;
    void GenerateFunctionCode();
    void GenerateGlobalVarCode();
    void GenerateLibCode();
    void GenerateArrayCode(ConstArray* array, int& size);
    void CaculateUninitArraySize(ArrayType* array, int& size);
public:
    Generator(Module *module): module(module) {};
    vector<string> targetCode;
    void GenerateRisc_V();
    string print();
    friend class RVFunction;
};

#endif
