#include "generator.h"
#include "enums.h"
#include<iostream>
#include <string>
#include "Ir.h"
#include <string>
#include <unordered_map> 
#include <unordered_set>

// std::unordered_map<std::string, StackObj*> name2stackobj;
std::unordered_map<StackObj*, std::string> stackobj2name;
std::unordered_set<std::string> global_var;
int now_sp;
class RegisterAllocator;

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
     //   name2stackobj.clear();
        RegisterAllocator* reg_alloc = new RegisterAllocator(this);
        start = new RVBlock(IRfunc->name + "_start");
        blocks.emplace_back(start);
        if(IRfunc->basic_blocks.size()==0) {
            return;
        }
        for(auto bb: IRfunc->basic_blocks){
            unique_ptr<RVBlock> new_block(new RVBlock(IRfunc->name+"_"+bb->name));
            IRB2RVB[bb] = new_block.get();
            RVB2IRB[new_block.get()] = bb;
            blocks.push_back(move(new_block));
        }
        int argcnt = IRfunc->args.size();

        for(int i = 0;i < argcnt;i++) {
            Register new_reg = Register(REG_ARGU[i]);
            if(i>=MAX_REG_FOR_FUNC_ARGU) 
                // todo 分配到堆栈
                std::cerr<<"too many args\n"<<endl;
            argu_regs.push_back(new_reg);
        }

        RVBlock* real_start = IRB2RVB[IRfunc->basic_blocks[0]]; // todo 0号块真是入口块吗？
        if(blocks[0].get() != real_start) { // todo 应该一定不一样吧
            start->addInstruction(make_unique<JmpInstr>(real_start));
        }
        start->succ.insert(real_start);
        real_start->prev.insert(start);
        for(int i = 0;i<blocks.size();i++) {

            if(blocks[i].get()!=start) {
                auto IRBlock = RVB2IRB[blocks[i].get()];
                for(auto &instr: IRBlock->instr_list) {
                    switch(instr->op_id) {
                        case Alloca: {
                            // todo
                            if(auto t = dynamic_cast<PType*>(instr->type)) {
                                Type *contained = t->contained;
                                if(auto tt = dynamic_cast<IntType*>(contained)) {
                                    int size = tt->bits/8;
                                    StackObj* new_obj = new StackObj(now_sp , size);
                                    now_sp -= size;
                                    stack_size += size;
                                    name2stackobj[instr->name] = new_obj;
                                    stackobj2name[new_obj] = instr->name;
                                    blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, -size));
                              //  blocks[i]->addInstruction(make_unique<LiInstr>(GetRegFromIRV(instr->name), ));
                            ///    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, , ));
                                }
                            }
                            break;   
                        }
                        case Store: {
                            auto ins = dynamic_cast<StoreInst*>(instr);
                            string src = ins->opes[0]->name;
                            Register new_reg;
                            if(src.substr(0,4)=="arg_"){
                                int x = src[4]-'0';
                                new_reg = Register(REG_ARGU[x]);
                                auto tar  = ins->opes[1]->name;
                                if(name2stackobj.find(tar)!=name2stackobj.end()){
                                    auto s_obj = name2stackobj[tar];
                                    //blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg, s_obj->offset-now_sp-s_obj->size));
                                }else{
                                    
                                }
                            }
                            else if(dynamic_cast<Const*>(ins->opes[0])){
                                int value = static_cast<ConstNumber*>(instr->opes[0])->value;
                                new_reg = reg_alloc->AllocateReg();
                                auto tar  = ins->opes[1]->name;
                                if(name2stackobj.find(tar)!=name2stackobj.end()){
                                    auto s_obj = name2stackobj[tar];
                                    blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg, s_obj->offset-now_sp-s_obj->size));
                                    reg_alloc->FreeReg(new_reg);
                                }
                                else{
                                    if(global_var.find(tar)!=global_var.end()){
                                        Register new_reg2 = reg_alloc->GetRegFromIRV(tar);
                                        blocks[i]->addInstruction(make_unique<LaInstr>(new_reg2, tar));
                                        blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                        blocks[i]->addInstruction(make_unique<StoreInstr>(new_reg2, new_reg,0));
                                    }
                                }
                            }
                            else{
                                new_reg = reg_alloc->GetRegFromIRV(src);
                                auto tar  = ins->opes[1]->name;
                                if(name2stackobj.find(tar)!=name2stackobj.end()){
                                    auto s_obj = name2stackobj[tar];
                                    //blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg, s_obj->offset-now_sp-s_obj->size));
                                }
                                else{
                                    if(global_var.find(tar)!=global_var.end()){
                                        Register new_reg2 = reg_alloc->GetRegFromIRV(tar);
                                        blocks[i]->addInstruction(make_unique<LaInstr>(new_reg2, tar));
                                        blocks[i]->addInstruction(make_unique<StoreInstr>(new_reg2, new_reg,0));
                                    }
                                }
                            }
                            break;
                        }
                        case Load: {
                            auto ins = dynamic_cast<LoadInst*>(instr);
                            string dest = ins->name;
                            string src = ins->opes[0]->name;
                            Register new_reg = reg_alloc->GetRegFromIRV(dest);
                            if(name2stackobj.find(src)!=name2stackobj.end()){
                                auto s_obj = name2stackobj[src];
                                blocks[i]->addInstruction(make_unique<loadAddr>( new_reg, sp, s_obj->offset-now_sp-s_obj->size));
                            }else if(global_var.find(src)!=global_var.end()){
                                Register new_reg2 = reg_alloc->GetRegFromIRV(src);
                                blocks[i]->addInstruction(make_unique<loadAddr>(new_reg, new_reg2,0));
                            }
                            break;
                        }
                        case Br:{
                            if(instr->num == 1){ // 无条件跳转
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
                            new_cmp.r1 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                            new_cmp.r2 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                            gene->cmp_context[instr->name] = new_cmp;
                            // todo 比较指令，应该压入一条什么？可能已经做完了
                            break;
                        }
                        case Add:
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
                            Register rd = reg_alloc->GetRegFromIRV(instr->name);
                            bool is_rr = dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr;
                            if(!is_rr) {
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    Register r1 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                                    RIInstrType op_id = static_cast<RIInstrType>(ins->op_id);
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r1, imm));
                                    break;
                                }else if(dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[1])->value;
                                    Register r0 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                                    RIInstrType op_id = static_cast<RIInstrType>(ins->op_id);
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r0, imm));
                                    break;
                                }
                            }
                            Register r0 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                            Register r1 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                            RRInstrType op_id = static_cast<RRInstrType>(ins->op_id);
                            blocks[i]->addInstruction(make_unique<RRInstr>(op_id, rd, r0, r1));
                            break;
                        }
                        case Sub:{
                            auto ins = static_cast<BinaryInst*>(instr);
                            Register rd = reg_alloc->GetRegFromIRV(instr->name);
                            bool is_rr = dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr;
                            if(!is_rr){
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    imm=-imm;
                                    Register r1 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                                    RIInstrType op_id = RIInstrType::Addi;
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r1, -imm));
                                    break;
                                }
                                else if(dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[1])->value;
                                    imm=-imm;
                                    Register r0 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                                    RIInstrType op_id = RIInstrType::Addi;
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r0, imm));
                                    break;
                                }
                            }
                            break;
                        }
                        case Call:{
                            // todo
                            auto ins = static_cast<CallInst*>(instr);
                            if(ins->opes.size()<=MAX_REG_FOR_FUNC_ARGU){
                                for(int j=0;j<ins->opes.size()-1;j++) {
                                    Register new_reg=Register(REG_ARGU[j]);
                                //    Register new_reg2=reg_alloc->GetRegFromIRV(ins->opes[i]->name);
                                    blocks[i]->addInstruction(make_unique<MoveInstr>(new_reg, reg_alloc->GetRegFromIRV(ins->opes[j]->name)));
                                }
                                blocks[i]->addInstruction(make_unique<CallInstr>(ins->opes[ins->opes.size()-1]->name));

                             //   blocks[i]->addInstruction(make_unique<CallInstr>(ins->opes[ins->opes.size()-2]->name));
                            } else{
                                // todo 分配到堆栈
                                std::cerr<<"too many args\n"<<endl;

                            }
                            blocks[i]->addInstruction(make_unique<MoveInstr>(reg_alloc->GetRegFromIRV(instr->name), a0));
                            break;
                        }
                        case Ret:{
                            auto ins = static_cast<ReturnInst*>(instr);
                            if(ins->opes.size()==0){
                                blocks[i]->addInstruction(make_unique<RetInstr>());
                                // todo succ
                            }else{
                                auto new_reg = reg_alloc->GetRegFromIRV(ins->opes[0]->name);
                                blocks[i]->addInstruction(make_unique<MoveInstr>(a0, new_reg));
                                blocks[i]->addInstruction(make_unique<RetInstr>());
                            }
                            now_sp+=stack_size;
                            break;
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
    for(auto global_value: module->global_list) {
        global_var.insert(global_value->name);
    }
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
        //targetCode.push_back(func->name+":");
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
                        targetCode.push_back("  .byte "+std::to_string((int)(static_cast<ConstNumber*>(global_value->value)->value)));
                        targetCode.push_back("  .size "+global_value->name+", 1");
                        break;
                    }
                    case 8:{
                        targetCode.push_back("  .byte "+std::to_string((int)(static_cast<ConstNumber*>(global_value->value)->value)));
                        targetCode.push_back("  .size "+global_value->name+", 1");
                        break;
                    }
                    case 32:{
                        targetCode.push_back("  .word "+std::to_string((int)(static_cast<ConstNumber*>(global_value->value)->value))); 
                        targetCode.push_back("  .size "+global_value->name+", 4");
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