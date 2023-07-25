#include "RVBlock.hpp"
#include "Ir.h"
#include "generator.h"
#include "register.h"
#include <unordered_map> // Add this header file
//unordered_map<BasicBlock*,RVBlock*> IRB2RVB;
//unordered_map<RVBlock*,BasicBlock*> RVB2IRB;
extern int now_reg;
extern int GetRegFromIRV(string IRV);
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

public:
    RVFunction(string name, Function* IRfunc,Generator* gene):name(name){
        start = new RVBlock(IRfunc->name + "_start");
        blocks.emplace_back(start);
        for(auto bb: IRfunc->basic_blocks){
            unique_ptr<RVBlock> new_block(new RVBlock(".B"+to_string(gene->num_block++)));
            IRB2RVB[bb] = new_block.get();
            RVB2IRB[new_block.get()] = bb;
            blocks.push_back(move(new_block));
        }
        int argcnt = IRfunc->args.size();

        for(int i = 0;i < argcnt;i++) {
            Register new_reg = Register(now_reg++);
            if(i<MAX_REG_FOR_FUNC_ARGU) {
                start->addInstruction(make_unique<MoveInstr>(new_reg, REG_ARGU[i]));
            } else {
                // todo 分配到堆栈
                std::cerr<<"too many args\n"<<endl;
            }
            argu_regs.push_back(new_reg);
        }

        RVBlock* real_start = IRB2RVB[IRfunc->basic_blocks[0]]; // todo 0号块真是入口块吗？
        if(blocks[1].get() != real_start) { // todo 应该一定不一样吧
            start->addInstruction(make_unique<JmpInstr>(real_start));
        }
        start->succ.insert(real_start);
        real_start->prev.insert(start);
        for(int i = 0;i<blocks.size();i++) {
            if(blocks[i].get()!=start) {
                auto IRBlock = RVB2IRB[blocks[i].get()];
                for(auto &instr: IRBlock->instr_list) {
                    switch(instr->op_id) {
                        case Br:{
                            if(instr->num == 1){ // 无条件跳转
                                RVBlock* jmp_target = IRB2RVB[IRBlock->succ_bbs[0]];
                                blocks[i]->addInstruction(make_unique<JmpInstr>(jmp_target));
                                blocks[i]->succ.insert(jmp_target);
                                jmp_target->prev.insert(blocks[i].get());
                            }else{ // 有条件跳转
                                CMP_Context cond;
                                RVBlock* true_target = IRB2RVB[IRBlock->args[1]];
                                RVBlock* false_target = IRB2RVB[IRBlock->args[2]];
                                if(gene->cmp_context.find(IRBlock->args[0]->name)!=gene->cmp_context.end()){
                                    cond = gene->cmp_context[IRBlock->args[0]->name];
                                }else{
                                    std::cerr<<"cmp context not found\n"<<endl;
                                }
                                if(true_target==blocks[i+1].get()){
                                    blocks[i]->addInstruction(make_unique<BrInstr>(false_target, cond.r1, cond.r2, cond.type));
                                }else if(false_target==blocks[i+1].get()) {
                                    blocks[i]->addInstruction(make_unique<BrInstr>(true_target, cond.r1, cond.r2, cond.type));
                                }else{
                                    blocks[i]->addInstruction(make_unique<BrInstr>(true_target, cond.r1, cond.r2, cond.type));
                                    blocks[i]->addInstruction(make_unique<JmpInstr>(false_target));
                                }
                                blocks[i]->succ.insert(true_target);
                                blocks[i]->succ.insert(false_target);
                                true_target->prev.insert(blocks[i].get());
                                false_target->prev.insert(blocks[i].get());
                            }
                            break;
                        }
                        case ICmp:{
                            CMP_Context new_cmp;
                            switch(static_cast<ICmpInst*>(instr)->icmp_op) {
                                case IEQ:{
                                    new_cmp.type = CMP_Type::eq;
                                    break;
                                }
                                case INE:{
                                    new_cmp.type = CMP_Type::ne;
                                    break;
                                }
                                case ISGT:{
                                    new_cmp.type = CMP_Type::sgt;
                                    break;
                                }
                                case ISGE:{
                                    new_cmp.type = CMP_Type::sge;
                                    break;
                                }
                                case ISLT:{
                                    new_cmp.type = CMP_Type::slt;
                                    break;
                                }
                                case ISLE:{
                                    new_cmp.type = CMP_Type::sle;
                                    break;
                                }
                            }
                            new_cmp.r1 = Register(GetRegFromIRV(instr->opes[0]->name));
                            new_cmp.r2 = Register(GetRegFromIRV(instr->opes[1]->name));
                            gene->cmp_context[instr->name] = new_cmp;
                            // todo 比较指令，应该压入一条什么？
                            break;
                        }
                        case Add:
                        case Sub:
                        case Mul:
                        case SDiv:
                        case SRem:
                        case UDiv:
                        case URem:
                        case Shl:
                        case LShr:
                        case AShr:
                        case And:
                        case Or:
                        case Xor:{
                            auto ins = static_cast<BinaryInst*>(instr);
                            Register rd = Register(GetRegFromIRV(instr->name));
                            bool is_rr = dynamic_cast<ConstNumber*>(instr->args[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->args[1])!=nullptr;
                            if(!is_rr) {
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->val;
                                    Register r2 = Register(GetRegFromIRV(instr->opes[1]->name));
                                    blocks[i]->addInstruction(make_unique<RIInstr>(ins->op_id, rd, r2, imm));
                                    break;
                                }else if(dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[1])->val;
                                    Register r1 = Register(GetRegFromIRV(instr->opes[0]->name));
                                    blocks[i]->addInstruction(make_unique<RIInstr>(ins->op_id, rd, r1, imm));
                                    break;
                                }
                            }
                            Register r1 = Register(GetRegFromIRV(instr->opes[0]->name));
                            Register r2 = Register(GetRegFromIRV(instr->opes[1]->name));
                            blocks[i]->addInstruction(make_unique<RRInstr>(ins->op_id, rd, r1, r2));
                            break;
                        }
                        case Call:{
                            // todo
                            auto ins = static_cast<CallInst*>(instr);
                            if(ins->opes.size()<=MAX_REG_FOR_FUNC_ARGU){
                                for(int i=0;i<ins->opes.size()-1;i++) {
                                    blocks[i]->addInstruction(make_unique<MoveInstr>(REG_ARGU[i], GetRegFromIRV(ins->opes[i]->name)));
                                }

                                blocks[i]->addInstruction(make_unique<CallInstr>(ins->opes[ins->opes.size()-1]->name));
                            } else{
                                // todo 分配到堆栈
                                std::cerr<<"too many args\n"<<endl;

                            }
                        }
                    }
                }
            }
        }

    }
};