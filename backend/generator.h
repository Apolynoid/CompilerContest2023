#include "Ir.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "RVBlock.hpp"// Add this header file
using namespace std;
extern unordered_map<BasicBlock*,RVBlock*> IRB2RVB;
extern unordered_map<RVBlock*,BasicBlock*> RVB2IRB;
extern int now_reg;
extern int GetRegFromIRV(string IRV);
std::unordered_map<std::string, StackObj*> name2stackobj;
std::unordered_map<StackObj*, std::string> stackobj2name;
int now_sp;
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
BrInstrType CMP2Br(CMP_Type type) {
    switch(type) {
        case CMP_Type::eq: return BrInstrType::Beq;
        case CMP_Type::ne: return BrInstrType::Bne;
        case CMP_Type::sgt: return BrInstrType::Bgt;
        case CMP_Type::sge: return BrInstrType::Bge;
        case CMP_Type::slt: return BrInstrType::Blt;
        case CMP_Type::sle: return BrInstrType::Ble;
        default: std::cerr<<"invalid LLVM IR\n";
    }
}
class RVFunction {
private:
    string name;
    RVBlock* start;
    vector<unique_ptr<RVBlock>> blocks;
    vector<Register> argu_regs;

public:
    void GenerateRiscv(stringstream &out){
        out<<name<<":\n";
       // start->GenerateRiscv(out);
        for(int i = 1;i<blocks.size();i++){
            blocks[i]->GenerateRiscv(out);
        }
    }
    RVFunction(string name, Function* IRfunc,Generator* gene);
};
class Generator {
private:
    Module *module;
    vector<unique_ptr<RVFunction>> functions;
    vector<string> targetCode;
    unordered_map<string,CMP_Context> cmp_context;
    int num_block;
    void GenerateFunctionCode();
    void GenerateGlobalVarCode();
    void GenerateArrayCode(ConstArray* array);
public:
    Generator(Module *module): module(module) {};
    void GenerateRisc_V();
    void print();
    friend class RVFunction;
};
