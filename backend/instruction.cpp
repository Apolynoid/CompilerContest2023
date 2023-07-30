// #include "instruction.h"
#include "RVBlock.h"

using namespace std;

const unordered_map<RRInstrType, string> RRInstr::RRInstrTypeMap = {
    {ADD, "add"}, {SUB, "sub"}, {MUL, "mul"}, {SDIV, "div"}, {SREM, "rem"}, {UREM, "remu"}, {UDIV, "divu"},
    {Sll, "sll"}, {Sra, "sra"}, {Srl, "srl"},
    {AND, "and"}, {OR, "or"}, {XOR, "xor"},
    {Seq, "seqz"}, {Sne, "snez"}, {Sgt, "sgtz"}, {Sge, "sgez"}, {Slt, "sltz"}, {Sle, "slez"}
};

const unordered_map<RIInstrType, string> RIInstr::RIInstrTypeMap = {
    {Addi, "addi"}, {Slli, "slli"}, {Srli, "srli"}, {Srai, "srai"}, {Slti, "slti"}, {Sltiu, "sltiu"}, 
    {Xori, "xori"}, {Ori, "ori"}, {Andi, "andi"}
};

void JmpInstr::GeneratorRiscvCode(stringstream &out){
    out<<'\t'<<"j\t"<<target->name<<'\n';
}

void BrInstr::GeneratorRiscvCode(stringstream &out){
    out<<'\t'<<"beq\t"<<rs1<<", "<<rs2<<", "<<target->name<<'\n';
}