#ifndef DEF_RVBLOCK
#define DEF_RVBLOCK

#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "Ir.h"
#include "enums.h"
#include "instruction.h"

using namespace std;

class RVBlock{
public:
    string name;
    vector<unique_ptr<instruction> > instructions;
    unordered_set<RVBlock*> prev,succ;
    unordered_set<Register> liveIn,liveOut,liveDef,liveUse;
    RVBlock(string name):name(name){};
    void addInstruction(unique_ptr<instruction> inst){
        instructions.push_back(move(inst));
    }
    void addInstruction(vector<unique_ptr<instruction>> insts){
        for(auto &inst:insts){
            instructions.push_back(move(inst));
        }
    }
    void GenerateRiscv(stringstream &out){
        for(auto &inst:instructions){
            inst->GeneratorRiscvCode(out);
        }
    }
    void Fillinfo(BasicBlock *IRBlock, RVBlock *nextBlock){
        for(auto &instr: IRBlock->instr_list) {
            if(instr->type->type_id == Br){
                if(instr->num == 1) { // 无条件跳转

                } else { // 有条件跳转

                }
            }
        }
    }
    bool operator==(const RVBlock& other) const {
        return name == other.name && instructions == other.instructions;
    }
};
namespace std {
    template<>
    struct hash<RVBlock> {
        size_t operator()(const RVBlock& rvb) const {
            size_t h = hash<string>()(rvb.name);
            return h;
        }
    };
}

#endif