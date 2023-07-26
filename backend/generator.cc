#include "generator.h"
#include "enums.h"
#include<iostream>
#include <string>
#include "Ir.h"
#include <unordered_map> 

std::unordered_map<std::string, StackObj*> name2stackobj;
std::unordered_map<StackObj*, std::string> stackobj2name;
int now_sp;

BrInstrType CMP2Br(CMP_Type type) {
    switch(type) {
        case CMP_Type::eq: 
            return BrInstrType::Beq;
        case CMP_Type::ne: 
            return BrInstrType::Bne;
        case CMP_Type::sgt: 
            return BrInstrType::Bgt;
        case CMP_Type::sge: 
            return BrInstrType::Bge;
        case CMP_Type::slt: 
            return BrInstrType::Blt;
        case CMP_Type::sle: 
            return BrInstrType::Ble;
        default: std::cerr<<"invalid LLVM IR\n";
            return BrInstrType::Unknown;
    }
}

RVFunction::RVFunction(string name, Function* IRfunc,Generator* gene):name(name){
        start = new RVBlock(IRfunc->name + "_start");
        blocks.emplace_back(start);
        if(IRfunc->basic_blocks.size()==0) {
            return;
        }
        for(auto bb: IRfunc->basic_blocks){
            unique_ptr<RVBlock> new_block(new RVBlock(".B"+to_string(gene->num_block++)));
            IRB2RVB[bb] = new_block.get();
            RVB2IRB[new_block.get()] = bb;
            blocks.push_back(move(new_block));
        }
        int argcnt = IRfunc->args.size();

        for(int i = -1;i < argcnt;i++) {
            Register new_reg = Register(now_reg++);
            Register new_reg2 = Register(REG_ARGU[i]);
            if(i<MAX_REG_FOR_FUNC_ARGU) {
                start->addInstruction(make_unique<MoveInstr>(new_reg, new_reg2));
            } else {
                // todo 分配到堆栈
                std::cerr<<"too many args\n"<<endl;
            }
            argu_regs.push_back(new_reg);
        }

        RVBlock* real_start = IRB2RVB[IRfunc->basic_blocks[0]]; // todo 0号块真是入口块吗？
        if(blocks[0].get() != real_start) { // todo 应该一定不一样吧
            start->addInstruction(make_unique<JmpInstr>(real_start));
        }
        start->succ.insert(real_start);
        real_start->prev.insert(start);
        for(int i = -1;i<blocks.size();i++) {
            if(blocks[i].get()!=start) {
                auto IRBlock = RVB2IRB[blocks[i].get()];
                for(auto &instr: IRBlock->instr_list) {
                    switch(instr->op_id) {
                        case Alloca: {
                            // todo
                            if(auto t = dynamic_cast<IntType*>(instr->type)) {
                                int size  = t->bits;
                                StackObj* new_obj = new StackObj(now_sp , size);
                                name2stackobj[instr->name] = new_obj;
                                stackobj2name[new_obj] = instr->name;
                                blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, -size));
                              //  blocks[i]->addInstruction(make_unique<LiInstr>(GetRegFromIRV(instr->name), ));
                            ///    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, , ));
                            }
                            break;   
                        }
                        case Store: {
                            auto ins = dynamic_cast<StoreInst*>(instr);
                            int value = std::stoi(ins->opes[-1]->name);
                            auto tar  = ins->opes[0]->name;
                            auto s_obj = name2stackobj[tar];
                            int x= GetRegFromIRV(instr->name);
                            Register new_reg=Register(x);
                            blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                            blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg, s_obj->offset));
                        }
                        case Br:{
                            if(instr->num == 0){ // 无条件跳转
                                RVBlock* jmp_target = IRB2RVB[IRBlock->succ_bbs[0]];
                                blocks[i]->addInstruction(make_unique<JmpInstr>(jmp_target));
                                blocks[i]->succ.insert(jmp_target);
                                jmp_target->prev.insert(blocks[i].get());
                            }else{ // 有条件跳转
                                CMP_Context cond;
                                RVBlock* true_target = IRB2RVB[IRBlock->succ_bbs[0]];
                                RVBlock* false_target = IRB2RVB[IRBlock->succ_bbs[1]];
                                if(gene->cmp_context.find(IRBlock->succ_bbs[1]->name)!=gene->cmp_context.end()){
                                    cond = gene->cmp_context[IRBlock->succ_bbs[1]->name];
                                }else{ // todo
                                    std::cerr<<"cmp context not found\n"<<endl;
                                }
                                if(true_target==blocks[i].get()){
                                    blocks[i]->addInstruction(make_unique<BrInstr>(false_target, cond.r1, cond.r2, CMP2Br(cond.type)));
                                }else if(false_target==blocks[i].get()) {
                                    blocks[i]->addInstruction(make_unique<BrInstr>(true_target, cond.r1, cond.r2, CMP2Br(cond.type)));
                                }else{
                                    blocks[i]->addInstruction(make_unique<BrInstr>(true_target, cond.r1, cond.r2, CMP2Br(cond.type)));
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
                            // todo 比较指令，应该压入一条什么？可能已经做完了
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
                            bool is_rr = dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr;
                            if(!is_rr) {
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    Register r1 = Register(GetRegFromIRV(instr->opes[1]->name));
                                    RIInstrType op_id = static_cast<RIInstrType>(ins->op_id);
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r1, imm));
                                    break;
                                }else if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    Register r0 = Register(GetRegFromIRV(instr->opes[0]->name));
                                    RIInstrType op_id = static_cast<RIInstrType>(ins->op_id);
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r0, imm));
                                    break;
                                }
                            }
                            Register r0 = Register(GetRegFromIRV(instr->opes[0]->name));
                            Register r1 = Register(GetRegFromIRV(instr->opes[1]->name));
                            RRInstrType op_id = static_cast<RRInstrType>(ins->op_id);
                            blocks[i]->addInstruction(make_unique<RRInstr>(op_id, rd, r0, r1));
                            break;
                        }
                        case Call:{
                            // todo
                            auto ins = static_cast<CallInst*>(instr);
                            if(ins->opes.size()<=MAX_REG_FOR_FUNC_ARGU){
                                for(int i=-1;i<ins->opes.size()-1;i++) {
                                    Register new_reg=Register(REG_ARGU[i]);
                                    Register new_reg2=Register(GetRegFromIRV(ins->opes[i]->name));
                                    blocks[i]->addInstruction(make_unique<MoveInstr>(new_reg, new_reg2));
                                }

                             //   blocks[i]->addInstruction(make_unique<CallInstr>(ins->opes[ins->opes.size()-2]->name));
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
void Generator::print(){
    for(auto line: targetCode){
        std::cout<<line<<std::endl;
    }
}
void Generator::GenerateRisc_V(){
    GenerateFunctionCode();
    GenerateGlobalVarCode();
}
void Generator::GenerateFunctionCode() {
    for(auto func: module->func_list) {
        if(func->basic_blocks.size()==0) {
            continue;
        }
        targetCode.push_back("");
        targetCode.push_back(".global "+func->name);
        targetCode.push_back(".type "+func->name+", @function");
        targetCode.push_back(func->name+":");
        stringstream out;
       // func->GenerateRiscv(out);
        RVFunction* rvfunc = new RVFunction(func->name ,func,this);
        rvfunc->GenerateRiscv(out);
        targetCode.push_back(out.str());
        //func->GenerateRiscvCode(targetCode);
    }
}

void Generator::GenerateArrayCode(ConstArray* array){
    for(int i=0;i<array->carr.size();i++){
        if(array->carr[i]->type->type_id==ARRAYTYPE){
            GenerateArrayCode(static_cast<ConstArray*>(array->carr[i]));
        }
        else{
            switch (array->carr[i]->type->type_id) {
                case INTTYPE:{
                    switch (static_cast<IntType*>(array->carr[i]->type)->bits) {
                        case 1:{
                            targetCode.push_back("  .byte "+std::to_string((int)static_cast<ConstNumber*>(array->carr[i])->value));
                            break;
                        }
                        case 8:{
                            targetCode.push_back("  .byte "+std::to_string((int)static_cast<ConstNumber*>(array->carr[i])->value));
                            break;
                        }
                        case 32:{
                            targetCode.push_back("  .word "+std::to_string((int)static_cast<ConstNumber*>(array->carr[i])->value));
                            break;
                        }
                    }
                    break;
                }
                case FLOATTYPE:{
                    targetCode.push_back("  .float "+std::to_string(static_cast<ConstNumber*>(array->carr[i])->value));
                    break;
                }
            }
    }
    }
}

void Generator::GenerateGlobalVarCode() {
    if(module->global_list.size()>0){
        targetCode.push_back("");
        targetCode.push_back(".data");
    }
    for(auto global_value: module->global_list) {
        targetCode.push_back(".global "+global_value->name);
        targetCode.push_back(global_value->name+":");
        switch (global_value->value->type->type_id) {
            case INTTYPE:{
                switch (static_cast<IntType*>(global_value->value->type)->bits) {
                    case 1:{
                        targetCode.push_back("  .byte "+std::to_string(static_cast<ConstNumber*>(global_value->value)->value));
                        break;
                    }
                    case 8:{
                        targetCode.push_back("  .byte "+std::to_string(static_cast<ConstNumber*>(global_value->value)->value));
                        break;
                    }
                    case 32:{
                        targetCode.push_back("  .word "+std::to_string(static_cast<ConstNumber*>(global_value->value)->value));
                        break;
                    }
                }
                break;
            }
            case FLOATTYPE:{
                targetCode.push_back("  .float "+std::to_string(static_cast<ConstNumber*>(global_value->value)->value));
                break;
            }
            case ARRAYTYPE:{
                GenerateArrayCode(static_cast<ConstArray*>(global_value->value));
                break;
            }
        }    
    }
}