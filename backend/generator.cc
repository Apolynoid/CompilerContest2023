#include "generator.h"
#include "enums.h"
#include<iostream>
#include <string>
#include "Ir.h"
#include <string>
#include <unordered_map> 
#include <unordered_set>

// std::unordered_map<std::string, StackObj*> name2stackobj;

std::unordered_set<std::string> global_var;

const unordered_set<Register> SavedRegisters = {s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10,s11};
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
void RVFunction::pushTemp(int i){
    now_sp -= 24;
    blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, -24));
    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, t0, 0));
    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, t1, 4));
    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, t2, 8));
    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, t3, 12));
    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, t4, 16));
    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, t5, 20));
    return ;
}
void RVFunction::popTemp(int i){
    now_sp += 24;
    blocks[i]->addInstruction(make_unique<loadAddr>(t0, sp, 0));
    blocks[i]->addInstruction(make_unique<loadAddr>(t1, sp, 4));
    blocks[i]->addInstruction(make_unique<loadAddr>(t2, sp, 8));
    blocks[i]->addInstruction(make_unique<loadAddr>(t3, sp, 12));
    blocks[i]->addInstruction(make_unique<loadAddr>(t4, sp, 16));
    blocks[i]->addInstruction(make_unique<loadAddr>(t5, sp, 20));
    blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, 24));
    return ;
}

void RVFunction::pushIfSave(Register reg,int i){
    if(SavedRegisters.find(reg)!=SavedRegisters.end()){
        StackObj* new_obj = new StackObj(now_sp , 4);
        now_sp -= 4;
        stack_size += 4;
        reg2stack[reg] = new_obj;
        blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, -4));
        blocks[i]->addInstruction(make_unique<StoreInstr>(sp, reg,0));
    }
}
void RVFunction::pop(int i){
    for(auto it = reg2stack.begin();it!=reg2stack.end();it++){
        blocks[i]->addInstruction(make_unique<loadAddr>(it->first,sp,it->second->offset-now_sp-it->second->size));
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
            Register new_reg = reg_alloc->GetRegForFuncArgu(i);
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
                        case GetElementPtr: {
                            auto instr_gep = dynamic_cast<GetElementPtrInst*>(instr);
                             int index = 0;
                                ArrayType* arr=new ArrayType(nullptr,-1);
                                auto point = static_cast<PType*>(instr_gep->opes[0]->type);
                                int size = 0;
                                for(int i=1;i<instr_gep->opes.size();i++) {
                                    if(i==1) {
                                        // todo 
                                        int value = static_cast<ConstNumber*>(instr_gep->opes[i])->value;
                                        if(point->contained->type_id == INTTYPE) {
                                            switch (static_cast<IntType*>(point->contained)->bits) {
                                                case 1:
                                                case 8:{
                                                    size = 1;
                                                    index = value*size;
                                                    break;
                                                }
                                                case 32:{
                                                    size = 4;
                                                    index = value*size;
                                                    break;
                                                }
                                            }
                                        }
                                        else if(point->contained->type_id == FLOATTYPE) {
                                            size = 4;
                                            index = value*size;
                                        }
                                        else {
                                            arr=static_cast<ArrayType*>(point->contained);
                                            continue;
                                        }
                                        break;
                                    }
                                    int value = static_cast<ConstNumber*>(instr_gep->opes[i])->value;
                                    index += value * arr->size/arr->num;
                                    if(dynamic_cast<ArrayType*>(arr->contained)) {
                                        arr = static_cast<ArrayType*>(arr->contained);
                                        continue;
                                    }
                                    else {  
                                        switch (arr->contained->type_id) {
                                            case INTTYPE:{
                                                switch (static_cast<IntType*>(arr->contained)->bits) {
                                                     case 1:
                                                     case 8:{
                                                        size = 1;
                                                         break;
                                                     }
                                                     case 32:{
                                                        size = 4;
                                                        
                                                        break;
                                                     }
                                                 }
                                                 break;
                                             }
                                             case FLOATTYPE:{
                                                size = 4;
                                                break;
                                             }
                                        }
                                    }
                                }
                            if(name2stackobj.find(instr_gep->opes[0]->name)!=name2stackobj.end()) {
                                auto sobj = name2stackobj[instr_gep->opes[0]->name];
                              //  name2stackobj[instr_gep->name] = sobj;
                            //    Register newreg = reg_alloc->GetRegFromIRV(instr_gep->name);
                              //  blocks[i]->addInstruction(make_unique<RIInstr>(Addi, newreg, sp, sobj->offset-now_sp-sobj->size));
                               
                               // index /=size;
                                StackObj* new_obj = new StackObj(sobj->offset - index , size);
                                name2stackobj[instr_gep->name] = new_obj;
                            } else {
                                if(global_var.find(instr_gep->opes[0]->name)!=global_var.end()) {
                                    auto new_reg = reg_alloc->GetRegFromIRV(instr_gep->name);
                                    pushIfSave(new_reg,i);
                                    blocks[i]->addInstruction(make_unique<LaInstr>(new_reg, instr_gep->opes[0]->name));
                                    blocks[i]->addInstruction(make_unique<RIInstr>(Addi, new_reg, new_reg, index));
                                
                                }
                            }
                            break;
                        }
                        case BitCast: {
                            auto instr_cast = dynamic_cast<CastInst*>(instr);
                            if(name2stackobj.find(instr_cast->opes[0]->name)!=name2stackobj.end()) {
                                auto sobj = name2stackobj[instr_cast->opes[0]->name];
                                name2stackobj[instr_cast->name] = sobj;
                                auto newreg = reg_alloc->GetRegFromIRV(instr_cast->name);
                                blocks[i]->addInstruction(make_unique<RIInstr>(Addi, newreg, sp, sobj->offset-now_sp-sobj->size));
                              //  blocks[i]->addInstruction(make_unique<MvInstr>(newreg, ));
                            }
                            else {
                                std::cerr<<"Get a bitcast from a non-stackobj\n";
                                exit(0);
                             //   name2stackobj[instr_cast->name] = name2stackobj[instr_cast->opes[0]->name];
                             //   stackobj2name[name2stackobj[instr_cast->opes[0]->name]] = instr_cast->name;
                            }
                            break;
                        }
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
                                else if (auto tt = dynamic_cast<ArrayType*>(contained)) {
                                    int size = tt->size;
                                    StackObj* new_obj = new StackObj(now_sp , size);
                                    now_sp -= size;
                                    stack_size += size;
                                    name2stackobj[instr->name] = new_obj;
                                    stackobj2name[new_obj] = instr->name;
                                    // todo 数组初始化
                                    blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, -size));
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
                                new_reg = reg_alloc->GetRegForFuncArgu(x);
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
                                new_reg = reg_alloc->GetImmReg();
                                auto tar  = ins->opes[1]->name;
                                if(name2stackobj.find(tar)!=name2stackobj.end()){
                                    auto s_obj = name2stackobj[tar];
                                    blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg, s_obj->offset-now_sp-s_obj->size));
                                }
                                else{
                                    if(global_var.find(tar)!=global_var.end()){
                                        Register new_reg2 = reg_alloc->GetRegFromIRV(tar);
                                        pushIfSave(new_reg2,i);
                                        blocks[i]->addInstruction(make_unique<LaInstr>(new_reg2, tar));
                                        blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                        blocks[i]->addInstruction(make_unique<StoreInstr>(new_reg2, new_reg,0));
                                    }
                                }
                            }
                            else{
                                new_reg = reg_alloc->GetRegFromIRV(src);
                                // if(SavedRegisters.find(new_reg)!=SavedRegisters.end()){
                                //     StackObj* new_obj = new StackObj(now_sp , 4);
                                //     now_sp -= 4;
                                //     stack_size += 4;
                                //     reg2stack[new_reg] = new_obj;
                                //     blocks[i]->addInstruction(make_unique<RIInstr>(Addi, sp, sp, -4));
                                //     blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg,0));
                                // }
                                pushIfSave(new_reg, i);
                                auto tar  = ins->opes[1]->name;
                                if(name2stackobj.find(tar)!=name2stackobj.end()){
                                    auto s_obj = name2stackobj[tar];
                                    //blocks[i]->addInstruction(make_unique<LiInstr>(new_reg, value));
                                    blocks[i]->addInstruction(make_unique<StoreInstr>(sp, new_reg, s_obj->offset-now_sp-s_obj->size));
                                }
                                else{
                                    if(global_var.find(tar)!=global_var.end()){
                                        Register new_reg2 = reg_alloc->GetRegFromIRV(tar);
                                        pushIfSave(new_reg2,i);
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
                            pushIfSave(new_reg,i);
                            if(name2stackobj.find(src)!=name2stackobj.end()){
                                auto s_obj = name2stackobj[src];
                                blocks[i]->addInstruction(make_unique<loadAddr>( new_reg, sp, s_obj->offset-now_sp-s_obj->size));
                            }else if(global_var.find(src)!=global_var.end()){
                                Register new_reg2 = reg_alloc->GetRegFromIRV(src);
                                pushIfSave(new_reg2,i);
                                blocks[i]->addInstruction(make_unique<LaInstr>(new_reg2, src));
                                blocks[i]->addInstruction(make_unique<loadAddr>( new_reg, new_reg2, 0));
                            }else {
                                auto new_reg2 = reg_alloc->GetRegFromIRV(src);
                                pushIfSave(new_reg2,i);
                                blocks[i]->addInstruction(make_unique<loadAddr>(new_reg, new_reg2 ,0));
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
                                RVBlock* true_target = IRB2RVB[static_cast<BasicBlock*>(instr->opes[1])];
                                RVBlock* false_target = IRB2RVB[static_cast<BasicBlock*>(instr->opes[2])];
                                if(gene->cmp_context.find(instr->opes[0]->name)!=gene->cmp_context.end()){
                                    cond = gene->cmp_context[instr->opes[0]->name];
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
                            if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr){
                                int result = false;
                                auto op1 = dynamic_cast<ConstNumber*>(instr->opes[0])->value;
                                auto op2 = dynamic_cast<ConstNumber*>(instr->opes[1])->value;
                                switch (new_cmp.type) {
                                case CMP_Type::eq:
                                    /* code */
                                    result = op1==op2;
                                    break;
                                case CMP_Type::ne:
                                    result = op1!=op2;
                                    break;
                                case CMP_Type::sgt:
                                    result = op1>op2;
                                    break;
                                case CMP_Type::sge:
                                    result = op1>=op2;
                                    break;
                                case CMP_Type::slt:
                                    result = op1<op2;
                                    break;
                                case CMP_Type::sle:
                                    result = op1<=op2;
                                    break;
                                default:
                                    break;
                                }
                                blocks[i]->addInstruction(make_unique<LiInstr>(t6, result));
                                new_cmp.r1 = t6;
                                new_cmp.r2 = zero;
                                new_cmp.type = CMP_Type::ne;
                            } else if(dynamic_cast<ConstNumber*>(instr->opes[0])==nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])==nullptr) {
                                new_cmp.r1 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                                pushIfSave(new_cmp.r1,i);
                                new_cmp.r2 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                                pushIfSave(new_cmp.r2,i);
                            } else if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                blocks[i]->addInstruction(make_unique<LiInstr>(t6, dynamic_cast<ConstNumber*>(instr->opes[0])->value));
                                new_cmp.r1 = t6;
                                new_cmp.r2 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                                pushIfSave(new_cmp.r2,i);
                            } else {
                                blocks[i]->addInstruction(make_unique<LiInstr>(t6, dynamic_cast<ConstNumber*>(instr->opes[1])->value));
                                new_cmp.r1 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                                pushIfSave(new_cmp.r1,i);
                                new_cmp.r2 = t6;
                            }
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
                            pushIfSave(rd,i);
                            bool is_rri = dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr||dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr;
                            if(is_rri) {
                                // todo
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm1 = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    int imm2 = static_cast<ConstNumber*>(instr->opes[1])->value;
                                    auto op_id = RRInstr::IR2RiscV(ins->op_id);
                                    int finalval;
                                    switch(op_id) {
                                        case ADD:
                                            finalval = imm1+imm2;
                                            break;
                                        case SUB:
                                            finalval = imm1-imm2;
                                            break;
                                        case MUL:
                                            finalval = imm1*imm2;
                                            break;
                                        case SDIV:
                                            finalval = imm1/imm2;
                                            break;
                                        case SREM:
                                            finalval = imm1%imm2;
                                            break;
                                        case UDIV:
                                            finalval = (unsigned int)imm1/(unsigned int)imm2;
                                            break;
                                        case UREM:
                                            finalval = (unsigned int)imm1%(unsigned int)imm2;
                                            break;
                                        case AND:
                                            finalval = imm1&imm2;
                                            break;
                                        case OR:
                                            finalval = imm1|imm2;
                                            break;
                                        case XOR:
                                            finalval = imm1^imm2;
                                            break;
                                        case Sll:
                                            finalval = imm1<<imm2;
                                            break;
                                        case Srl:
                                            finalval = (unsigned int)imm1>>(unsigned int)imm2;
                                            break;
                                        case Sra:
                                            finalval = imm1>>imm2;
                                            break;
                                    }
                                    auto reg = reg_alloc->GetRegFromIRV(instr->name);
                                    blocks[i]->addInstruction(make_unique<LiInstr>(reg, finalval));
                                    pushIfSave(reg,i);
                                    break;
                                }
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    blocks[i]->addInstruction(make_unique<LiInstr>(t6, imm));
                                    Register r1 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                                    pushIfSave(r1,i);
                                    RRInstrType op_id = static_cast<RRInstrType>(ins->op_id);
                                    blocks[i]->addInstruction(make_unique<RRInstr>(op_id, rd, r1, t6));
                                    break;
                                }else if(dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[1])->value;
                                    blocks[i]->addInstruction(make_unique<LiInstr>(t6, imm));
                                    Register r0 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                                    pushIfSave(r0,i);
                                    RRInstrType op_id = static_cast<RRInstrType>(ins->op_id);
                                    blocks[i]->addInstruction(make_unique<RRInstr>(op_id, rd, r0, t6));
                                    break;
                                }
                            }
                            Register r0 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                            pushIfSave(r0,i);
                            Register r1 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                            pushIfSave(r1,i);
                            RRInstrType op_id = static_cast<RRInstrType>(ins->op_id);
                            blocks[i]->addInstruction(make_unique<RRInstr>(op_id, rd, r0, r1));
                            break;
                        }
                        case Sub:{
                            auto ins = static_cast<BinaryInst*>(instr);
                            Register rd = reg_alloc->GetRegFromIRV(instr->name);
                            pushIfSave(rd,i);
                            bool is_rri = dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr||dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr;
                            if(is_rri){
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr&&dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm0 = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    int imm1 = static_cast<ConstNumber*>(instr->opes[1])->value;
                                    int imm = imm0-imm1;
                                    auto reg = reg_alloc->GetRegFromIRV(instr->name);
                                    blocks[i]->addInstruction(make_unique<LiInstr>(reg, imm));
                                    pushIfSave(reg,i);
                                    break;
                                }
                                if(dynamic_cast<ConstNumber*>(instr->opes[0])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[0])->value;
                                    imm=-imm;
                                    Register r1 = reg_alloc->GetRegFromIRV(instr->opes[1]->name);
                                    pushIfSave(r1,i);
                                    RIInstrType op_id = RIInstrType::Addi;
                                    blocks[i]->addInstruction(make_unique<RIInstr>(op_id, rd, r1, -imm));
                                    break;
                                }
                                else if(dynamic_cast<ConstNumber*>(instr->opes[1])!=nullptr) {
                                    int imm = static_cast<ConstNumber*>(instr->opes[1])->value;
                                    imm=-imm;
                                    Register r0 = reg_alloc->GetRegFromIRV(instr->opes[0]->name);
                                    pushIfSave(r0,i);
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
                                    Register new_reg=reg_alloc->GetRegForFuncArgu(j);
                                    if(dynamic_cast<ConstNumber*>(ins->opes[j])){
                                        blocks[i]->addInstruction(make_unique<LiInstr>(new_reg,static_cast<ConstNumber*>(ins->opes[j])->value));
                                    }
                                    else{
                                        Register new_reg2=reg_alloc->GetRegFromIRV(ins->opes[j]->name);
                                        blocks[i]->addInstruction(make_unique<MoveInstr>(new_reg, reg_alloc->GetRegFromIRV(ins->opes[j]->name)));
                                    }
                                }
                                pushTemp(i);
                                blocks[i]->addInstruction(make_unique<CallInstr>(ins->opes[ins->opes.size()-1]->name));
                                popTemp(i);
                             //   blocks[i]->addInstruction(make_unique<CallInstr>(ins->opes[ins->opes.size()-2]->name));
                            } else{
                                // todo 分配到堆栈
                                std::cerr<<"too many args\n"<<endl;

                            }
                            if(instr->name.size())
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
                                pushIfSave(new_reg,i);
                                pop(i);
                                blocks[i]->addInstruction(make_unique<MoveInstr>(a0, new_reg));
                                blocks[i]->addInstruction(make_unique<RetInstr>());
                            }
                        //    now_sp+=stack_size;
                            break;
                        }
                    }
                }
            }
        }
        now_sp+=stack_size;

    }
string Generator::print(){
    string s;
    for(auto line: targetCode){
        s+=line;
        s+='\n';
    }
    return s;
}
void Generator::GenerateRisc_V(){
    for(auto global_value: module->global_list) {
        global_var.insert(global_value->name);
    }
    GenerateFunctionCode();
    GenerateGlobalVarCode();
    //GenerateLibCode();
}
void Generator::GenerateLibCode(){
    for(auto func:module->func_list){
        if(func->name=="__aeabi_memclr4"){
            targetCode.push_back("  .global __aeabi_memclr4");
            targetCode.push_back("  .type __aeabi_memclr4, @function");
            targetCode.push_back("__aeabi_memclr4:");
            targetCode.push_back("__aeabi_memclr4_loop:");
            targetCode.push_back("  sw zero, 0(a0)");
            targetCode.push_back("  addi a0, a0, 4");
            targetCode.push_back("  addi a1, a1, -4");
            targetCode.push_back("  bnez a1, __aeabi_memclr4_loop");
            targetCode.push_back("  ret\n");
        }
        else if(func->name=="__aeabi_memcpy4"){
            targetCode.push_back("  .global __aeabi_memcpy4");
            targetCode.push_back("  .type __aeabi_memcpy4, @function");
            targetCode.push_back("__aeabi_memcpy4:");
            targetCode.push_back("__aeabi_memcpy4_loop:");
            targetCode.push_back("  lw a3, 0(a1)");
            targetCode.push_back("  sw a3, 0(a0)");
            targetCode.push_back("  addi a0, a0, 4");
            targetCode.push_back("  addi a1, a1, 4");
            targetCode.push_back("  addi a2, a2, -4");
            targetCode.push_back("  bnez a2, __aeabi_memcpy4_loop");
            targetCode.push_back("  ret\n");
        }
        else if(func->name=="__aeabi_memset4"){
            targetCode.push_back("  .global __aeabi_memset4");
            targetCode.push_back("  .type __aeabi_memset4, @function");
            targetCode.push_back("__aeabi_memset4:");
            targetCode.push_back("__aeabi_memset4_loop:");
            targetCode.push_back("  sw a1, 0(a0)");
            targetCode.push_back("  addi a0, a0, 4");
            targetCode.push_back("  addi a2, a2, -4");
            targetCode.push_back("  bnez a2, __aeabi_memset4_loop");
            targetCode.push_back("  ret\n");
        }
    }
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

void Generator::GenerateArrayCode(ConstArray* array, int& global_size){
    for(int i=0;i<array->carr.size();i++){
        if(array->carr[i] == nullptr) {
            targetCode.push_back("  .word 0");
            continue;
        }
        if(array->carr[i]->type->type_id==ARRAYTYPE){
            GenerateArrayCode(static_cast<ConstArray*>(array->carr[i]),global_size);
        }
        else{
            switch (array->carr[i]->type->type_id) {
                case INTTYPE:{
                    switch (static_cast<IntType*>(array->carr[i]->type)->bits) {
                        case 1:{
                            global_size += 1;
                            targetCode.push_back("  .byte "+std::to_string((int)static_cast<ConstNumber*>(array->carr[i])->value));
                            break;
                        }
                        case 8:{
                            global_size += 1;
                            targetCode.push_back("  .byte "+std::to_string((int)static_cast<ConstNumber*>(array->carr[i])->value));
                            break;
                        }
                        case 32:{
                            global_size += 4;
                            targetCode.push_back("  .word "+std::to_string((int)static_cast<ConstNumber*>(array->carr[i])->value));
                            break;
                        }
                    }
                    break;
                }
                case FLOATTYPE:{
                    global_size += 4;
                    targetCode.push_back("  .float "+std::to_string(static_cast<ConstNumber*>(array->carr[i])->value));
                    break;
                }
            }
    }
    }
}


void Generator::CaculateUninitArraySize(ArrayType* array, int &size) {
    auto sub = dynamic_cast<ArrayType*>(array->contained);
    size*=array->num;
    if(sub==nullptr) {
        if(auto x = dynamic_cast<IntType*>(array->contained)){
            switch (x->bits) {
                case 1:{
                    size*=1;
                    break;
                }
                case 8:{
                    size*=1;
                    break;
                }
                case 32:{
                    size*=4;
                    break;
                }
            }
        } 
        //else if(auto x = dynamic_cast<FloatType*>(array->contained)){
         //   size*=4;
       // }
    } else {
      //  size*=array->num;
        CaculateUninitArraySize(sub,size);
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
                if(dynamic_cast<ConstZero*>(global_value->value)){
                    int size = 1;
                    CaculateUninitArraySize(static_cast<ArrayType*>(static_cast<PType*>(global_value->type)->contained),size);
                    targetCode.push_back("  .zero "+std::to_string(size));
                    targetCode.push_back("  .size "+global_value->name+", "+std::to_string(size));
                    break;
                }
                int size = 0;
                GenerateArrayCode(static_cast<ConstArray*>(global_value->value), size);
                targetCode.push_back("  .size "+global_value->name+", "+std::to_string(size));
                break;
            }
        }    
    }
}