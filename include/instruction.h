#ifndef DEF_INSTRUCTION
#define DEF_INSTRUCTION

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "register.h"
#include "enums.h"

class RVBlock;

using namespace std;

struct StackObj {
    int offset;
    int size;
    StackObj(int offset, int size) : offset(offset), size(size) {};
};
enum RRInstrType {
    ADD, SUB, MUL, SDIV, SREM, UDIV, UREM, Sll, Sra, Srl, AND, OR, XOR, Seq, Sne, Sgt, Sge, Slt, Sle
};
enum RIInstrType {
    Addi, Slli, Srli, Srai, Slti, Sltiu, Xori, Ori, Andi
};
inline ostream &operator<<(ostream& out, const Register Reg) {
    switch(Reg) {
        case zero: out << "zero"; break;
        case ra: out << "ra"; break;
        case sp: out << "sp"; break;
        case gp: out << "gp"; break;
        case tp: out << "tp"; break;
        case t0: out << "t0"; break;
        case t1: out << "t1"; break;
        case t2: out << "t2"; break;
        case s0: out << "s0"; break;
        case s1: out << "s1"; break;
        case a0: out << "a0"; break;
        case a1: out << "a1"; break;   
        case a2: out << "a2"; break;
        case a3: out << "a3"; break;
        case a4: out << "a4"; break;
        case a5: out << "a5"; break;
        case a6: out << "a6"; break;
        case a7: out << "a7"; break;
        case s2: out << "s2"; break;
        case s3: out << "s3"; break;
        case s4: out << "s4"; break;
        case s5: out << "s5"; break;
        case s6: out << "s6"; break;
        case s7: out << "s7"; break;
        case s8: out << "s8"; break;
        case s9: out << "s9"; break;
        case s10: out << "s10"; break;
        case s11: out << "s11"; break;
        case t3: out << "t3"; break;
        case t4: out << "t4"; break;
        case t5: out << "t5"; break;
        case t6: out << "t6"; break;
        default: std::cerr<<"invalid register\n";
    }
    return out;
}

class instruction {
protected:
    virtual vector<Register> getUseRegs() = 0;
    virtual vector<Register> getDefRegs() = 0;
public:
    virtual void GeneratorRiscvCode(stringstream &out) = 0;
    virtual void print(stringstream &out) {
        GeneratorRiscvCode(out);
    }
};

class RRInstr : public instruction {
private:
    static const unordered_map<RRInstrType, string> RRInstrTypeMap;
    RRInstrType type;
    Register rd, rs1, rs2;
public:
    RRInstr(RRInstrType type, Register rd, Register rs1, Register rs2) : type(type), rd(rd), rs1(rs1), rs2(rs2) {
    };
    vector<Register> getUseRegs()override {
        return {rs1, rs2};
    }
    vector<Register> getDefRegs()override {
        return {rd};
    }
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<RRInstrTypeMap.find(type)->second<<'\t'<<rd<<", "<<rs1<<", "<<rs2<<'\n';
    }
    static RRInstrType IR2RiscV(int IRType){
        switch(IRType) {
            case Add: return RRInstrType::ADD;
            case Sub: return RRInstrType::SUB;
            case Mul: return RRInstrType::MUL;
            case SDiv: return RRInstrType::SDIV;
            case SRem: return RRInstrType::SREM;
            case UDiv: return RRInstrType::UDIV;
            case URem: return RRInstrType::UREM;
          //  case Div: return RRInstrType::Div;
          //  case REM: return RRInstrType::Rem;
          //  case SLL: return RRInstrType::Sll;
          //  case SRA: return RRInstrType::Sra;
          //  case SRL: return RRInstrType::Srl;
             case And: return RRInstrType::AND;
             case Or: return RRInstrType::OR;
             case Xor: return RRInstrType::XOR;
             case Shl: return RRInstrType::Sll;
             case AShr: return RRInstrType::Sra;
             case LShr: return RRInstrType::Srl;
          //  case SEQ: return RRInstrType::Seq;
          //  case SNE: return RRInstrType::Sne;
         //   case SGT: return RRInstrType::Sgt;
         //   case SGE: return RRInstrType::Sge;
         //   case SLT: return RRInstrType::Slt;
         //   case SLE: return RRInstrType::Sle;
            default: std::cerr<<"invalid LLVM IR\n";
        }
    }
};

class RIInstr : public instruction {
private:
    static const unordered_map<RIInstrType, string> RIInstrTypeMap;
    RIInstrType type;
    Register rd, rs1;
    int imm;
public:
    RIInstr(RIInstrType type, Register rd, Register rs1, int imm) : type(type), rd(rd), rs1(rs1), imm(imm) {
    };
    vector<Register> getUseRegs()override {
        return {rs1};
    }
    vector<Register> getDefRegs()override {
        return {rd};
    }
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<RIInstrTypeMap.find(type)->second<<'\t'<<rd<<", "<<rs1<<", "<<imm<<'\n';
    }
};


class loadAddr: public instruction {
private:
    Register rd, rs1;
    int imm;
public:
    loadAddr(Register rd, Register rs1, int imm) : rd(rd), rs1(rs1), imm(imm) {
    };
    vector<Register> getUseRegs()override {
        return {rs1};
    }
    vector<Register> getDefRegs()override {
        return {rd};
    }
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<"lw\t"<<rd<<", "<<imm<<"("<<rs1<<')'<<'\n';
    }
};

class StoreInstr : public instruction {
private:
    Register rs1, rs2;
    int imm;
public:
    StoreInstr(Register rs1, Register rs2, int imm) : rs1(rs1), rs2(rs2), imm(imm) {
    };
    vector<Register> getUseRegs()override {
        return {rs1, rs2};
    }
    vector<Register> getDefRegs()override {
        return {};
    }
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<"sw\t"<<rs2<<", "<<imm<<"("<<rs1<<')'<<'\n';
    }
};
// class StoreGlobalInstr : public instruction {
// private:
//     Register rs1;
//     string name;
// public:
//     StoreGlobalInstr(Register rs1, string name) : rs1(rs1), name(name) {
//     };
//     vector<Register> getUseRegs()override {
//         return {rs1};
//     }
//     vector<Register> getDefRegs()override {
//         return {};
//     }
//     void GeneratorRiscvCode(stringstream &out) override{
//         out<<'\t'<<"sw\t"<<rs1<<", "<<name<<'\n';
//     }
// };
class JmpInstr : public instruction {
private:
    RVBlock *target;
public:
    vector<Register> getUseRegs()override {
        return {};
    }
    vector<Register> getDefRegs()override {
        return {};
    }
    JmpInstr(RVBlock *target) : target(target) {
    };
    void GeneratorRiscvCode(stringstream &out) override;
};
enum BrInstrType {
    Unknown, Beq, Bne, Bgt, Bge, Blt, Ble
};

inline stringstream& operator<<(stringstream &out, BrInstrType type) {
    switch(type) {
        case Beq: out<<"beq"; break;
        case Bne: out<<"bne"; break;
        case Bge: out<<"bge"; break;
        case Bgt: out<<"bgt"; break;
        case Ble: out<<"ble"; break;
        case Blt: out<<"blt"; break;
        default: std::cerr<<"invalid LLVM IR\n";
    }
    return out;
}
class BrInstr : public instruction {
private:
    RVBlock *target;
    Register rs1, rs2;
 //   int imm;
    BrInstrType type;
public:
    BrInstr(RVBlock *target, Register rs1, Register rs2, BrInstrType type) : target(target), rs1(rs1), rs2(rs2), type(type) {};
    vector<Register> getUseRegs()override {
        return {rs1, rs2};
    }
    vector<Register> getDefRegs()override {
        return {};
    }
    void GeneratorRiscvCode(stringstream &out) override;
};

class CallInstr: public instruction {
private:
    string name;
public:
    CallInstr(string name) : name(name) {};
    void GeneratorRiscvCode(stringstream &out) override {
        // todo
        out<<"\tcall "<<name<<endl;
    }
    vector<Register> getUseRegs()override {
        return {};
    }
    vector<Register> getDefRegs()override {
        return {};
    }
};

class MoveInstr: public instruction {
private:
    Register rd, rs;
public:
    MoveInstr(Register rd, Register rs) : rd(rd), rs(rs) {};
    vector<Register> getUseRegs()override {
        return {rs};
    }
    vector<Register> getDefRegs()override {
        return {rd};
    }
    // Context?
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<"mv\t"<<rd<<", "<<rs<<'\n';
    }
};


class LoadStackInstr: public instruction {
private:
    Register rd;
    StackObj *obj;
    int offset;
public:
    LoadStackInstr(Register rd, StackObj *obj, int offset) : rd(rd), obj(obj), offset(offset) {};
    std::vector<Register> getDefRegs()override {
        return {rd};
    }
};

class StoreStackInstr: public instruction {
private:
    Register rs;
    StackObj *obj;
    int offset;
public:
    StoreStackInstr(Register rs, StackObj *obj, int offset) : rs(rs), obj(obj), offset(offset) {};
    std::vector<Register> getUseRegs()override {
        return {rs};
    }
};


class RetInstr: public instruction {
private:
  //  bool withvalue;
public:
//    RetInstr(bool wi) : withvalue(withvalue) {};
    // Context?
    vector<Register> getUseRegs()override {
        return {};
    }
    vector<Register> getDefRegs()override {
        return {};
    }
    void GeneratorRiscvCode(stringstream &out) override{
      //  if(withvalue) {
            out<<'\t'<<"ret"<<'\n';
      //  } else {
       //     out<<'\t'<<"ret"<<'\n';
      //  }
    }
};

class LiInstr: public instruction {
private:
    Register rd;
    int imm;
public:
    LiInstr(Register rd, int imm) : rd(rd), imm(imm) {};
    vector<Register> getDefRegs()override {
        return {rd};
    }
    vector<Register> getUseRegs()override {
        return {};
    }
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<"li\t"<<rd<<", "<<imm<<'\n';
    }
};

class LaInstr: public instruction {
private:
    Register rd;
    string symbol;
public:
    LaInstr(Register rd, string symbol) : rd(rd), symbol(symbol) {};
    vector<Register> getDefRegs()override {
        return {rd};
    }
    vector<Register> getUseRegs()override {
        return {};
    }
    void GeneratorRiscvCode(stringstream &out) override{
        out<<'\t'<<"la\t"<<rd<<", "<<symbol<<'\n';
    }
};
#endif
