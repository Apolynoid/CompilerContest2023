#include "Ir.h"

IntType* intType1 = new IntType(1);
IntType* intType8 = new IntType(8);
IntType* intType32 = new IntType(32);
Type* floatType = new Type(FLOATTYPE);
Type* labelType = new Type(LABELTYPE);
Type* voidType = new Type(VOIDTYPE);
std::map<Type*, PType*> if_has_pointer;
std::map<std::pair<Type*, int>, ArrayType*> if_has_array;

std::map<int, std::string> instr_sign = { { Ret,"ret"},{ Br,"br"},{ FNeg,"fneg"},{ Add,"add"},{ Sub,"sub"},{ Mul,"mul"},{ SDiv,"sdiv"},{ SRem,"srem"},{ UDiv,"udiv"},{ URem,"urem"},{ FAdd,"fadd"},{ FSub,"fsub"},{ FMul,"fmul"},{ FDiv,"fdiv"},{ Shl,"shl"},{ LShr,"lshr"},{ AShr,"ashr"},{ And,"and"},{ Or,"or"},{ Xor,"xor"},{ Alloca,"alloca"},{ Load,"load"},{ Store,"store"},{ GetElementPtr,"getelementptr"},{ ZExt,"zext"},{ FPtoSI,"fptosi"},{ SItoFP,"sitofp"},{ BitCast, "bitcast"},{ ICmp,"icmp"},{ FCmp,"fcmp"},{ PHI,"phi"},{ Call,"call"} };
std::map<int, std::string> change_type = { {ZExt, " to i32"},{FPtoSI, " to i32"},{SItoFP, " to float"} };
std::map<int, std::string> change_cmp_instr = { { IEQ, "eq"}, { INE, "ne"},{ ISGT, "sgt"}, {ISGE, "sge"}, {ISLT, "slt"}, {ISLE, "sle"},{FUEQ, "ueq"}, {FUGT, "ugt"}, {FUGE, "uge"}, {FULT, "ult"}, {FULE, "ule"}, {FUNE, "une"} };

std::string print_sign(Base* base, bool is_type) {
    std::string temp;
    if(is_type == true){
        temp = temp + base->type->print() + " ";
    }
    if (dynamic_cast<GlobalVar*>(base) || dynamic_cast<Function*>(base)) {
        temp += "@" + base->name;
    }
    else if (dynamic_cast<Const*>(base)) {
        temp += base->print();
    }
    else {
        temp += "%" + base->name;
    }
    return temp;
}

PType* get_ptype(Type* contained) {
    if (!if_has_pointer.count(contained)) {
        if_has_pointer[contained] = new PType(contained);
    }
    return if_has_pointer[contained];
}

ArrayType* get_atype(Type* contained, int num) {
    if (!if_has_array.count({ contained, num })) {
        if_has_array[{ contained, num}] = new ArrayType(contained, num);
    }
    return if_has_array[{ contained, num}];
}

Type* get_rettype(Base* p, int size) {
    Type* type = p->type;
    while(type->type_id == POINTTYPE) {
        type = static_cast<PType*>(type)->contained;
    }
    if (type->type_id == ARRAYTYPE) {
        ArrayType* now_type = static_cast<ArrayType*>(type);
        for (int i = 1; i < size; i++) {
            type = now_type->contained;
            if (type->type_id == ARRAYTYPE) {
                now_type = static_cast<ArrayType*>(type);
            }
        }
    }
    return type;
}

Base::Base(Type* type, const std::string& name){
	this->type = type;
	this->name = name;
}

std::string Base::print() {
    return "";
}

GlobalVar::GlobalVar(std::string name, Module* module, Type* type, bool is_const, Const* value) : Base(get_ptype(type), name){
    this->is_const = is_const;
    this->value = value;
    module->add_globalvar(this); 
}

std::string GlobalVar::print() {
    return print_sign(this, false) + " = " + (this->is_const ? "constant " : "global ") + static_cast<PType*>(this->type)->contained->print() + " " + this->value->print();
}

Arg::Arg(Type* type, const std::string& name, Function* f, int no) : Base(type, name){
    this->parent = f;
    this->no = no;
}

std::string Arg::print() {
    return this->type->print() + " %" + this->name;
}

Function::Function(FuncType* type, const std::string& name, Module* parent) : Base(type, name){
    this->parent = parent;
    this->label_cnt = 0;
    this->v_count = 0;
    this->arg_count = 0;
    parent->add_func(this);
    int size_ = type->args.size();
    for (int i = 0; i < size_; i++) {
        std::string temp = "arg_" + std::to_string(this->arg_count);
        this->arg_count++;
        this->args.push_back(new Arg(type->args[i], temp, this, i));
    }
}

void Function::add_bb(BasicBlock* bb){
    if (bb->name.length() < 1) {
        bb->name = "label_" + std::to_string(this->label_cnt);
        this->label_cnt++;
    }
    basic_blocks.push_back(bb); 
}

Type* Function::get_retype() const{
    return static_cast<FuncType*>(this->type)->result;
}

bool Function::is_decl(){
    return basic_blocks.empty();
}

void Function::remove_bb(BasicBlock* bb) {
    this->basic_blocks.erase(std::remove(this->basic_blocks.begin(), this->basic_blocks.end(), bb), this->basic_blocks.end());
    for (auto pre : bb->pre_bbs) {
        pre->remove_succ_bb(bb);
    }
    for (auto succ : bb->succ_bbs) {
        succ->remove_pre_bb(bb);
    }
}

BasicBlock* Function::get_retbb() {
    for (auto bb : this->basic_blocks) {
        if (bb->get_last()->op_id == Ret) {
            return bb;
        }
    }
    return nullptr;
}

std::string Function::print() {
    std::string temp;
    bool judge = this->is_decl();
    temp = temp + (judge ? "declare " : "define") + " " + this->get_retype()->print() + " " + print_sign(this, false) + "(";

    int size_ = this->args.size();
    if(judge == true){
        for (int i = 0; i < size_; i++) {
            temp = temp + static_cast<FuncType*>(this->type)->args[i]->print();
            if (i != size_ - 1) {
                temp = temp + ", ";
            }
        }
    }
    else {
        for (int i = 0; i < size_; i++) {
            temp = temp + this->args[i]->print();
            if (i != size_ - 1) {
                temp = temp + ", ";
            }
        }
    }
    temp = temp + ")";

    size_ = this->basic_blocks.size();
    if (!judge) {
        temp = temp + "{" + "\n";
        for (int i = 0; i < size_; i++) {
            for (auto instr : this->basic_blocks[i]->instr_list) {
                if (instr->type->type_id != VOIDTYPE) {
                    if (instr->name == "") {
                        instr->name = "v" + std::to_string(this->v_count);
                        this->v_count++;
                    }
                }
            }
            temp = temp + this->basic_blocks[i]->print();
        }
        temp = temp + "}";
    }
    return temp;
}

Instr::Instr(Type* type, int id, int num, BasicBlock* parent) : Base(type, ""){
    this->op_id = id;
    this->num = num;
    this->parent = parent;
    this->opes.resize(num, nullptr);
    this->parent->add_instr(this);
}

Instr::Instr(Type* type, int id, int num) : Base(type, ""){
    this->op_id = id;
    this->num = num;
    this->parent = nullptr;
    this->opes.resize(num, nullptr);
}

Base* Instr::get_ope(int i) const {
    return this->opes[i];
}

void Instr::set_ope(int i, Base* value) {
    this->opes[i] = value;
}

std::string Instr::print() {
    return "";
}

BasicBlock::BasicBlock(Module* m, const std::string& name, Function* parent) : Base(labelType, name){
    this->parent = parent;
    this->parent->add_bb(this);
}

void BasicBlock::add_instr(Instr* instr) {
    this->instr_list.push_back(instr);
    instr->parent = this;
}

void BasicBlock::add_instr_front(Instr* instr) {
    this->instr_list.push_front(instr);
    instr->parent = this;
}

bool BasicBlock::add_instr_before_last(Instr* instr) {
    if (this->instr_list.empty()){
        return false;
    }
    else {
        auto temp = this->instr_list.back();
        this->instr_list.pop_back();
        this->instr_list.push_back(instr);
        this->instr_list.push_back(temp);
        instr->parent = this;
        return true;
    }
}

void BasicBlock::add_pre_bb(BasicBlock* bb){
    this->pre_bbs.push_back(bb);
}

void BasicBlock::add_succ_bb(BasicBlock* bb){
    this->succ_bbs.push_back(bb);
}

void BasicBlock::remove_pre_bb(BasicBlock* bb){
    this->pre_bbs.erase(std::remove(this->pre_bbs.begin(), this->pre_bbs.end(), bb), this->pre_bbs.end());
}

void BasicBlock::remove_succ_bb(BasicBlock* bb){
    this->succ_bbs.erase(std::remove(this->succ_bbs.begin(), this->succ_bbs.end(), bb), this->succ_bbs.end());
}

Instr* BasicBlock::get_last() {
    if (this->instr_list.empty()) {
        return nullptr;
    }
    if (this->instr_list.back()->op_id == Ret || this->instr_list.back()->op_id == Br) {
        return this->instr_list.back();
    }
    return nullptr;
}

std::string BasicBlock::print() {
    std::string temp;
    temp = temp + this->name + ":" + "\n";

    for (auto instr : this->instr_list) {
        temp += "  ";
        temp += instr->print();
        temp += "\n";
    }

    return temp;
}

Module::Module() {
}

std::string Module::print() {
    std::string temp;
    int size_ = this->global_list.size();
    for (int i = 0; i < size_; i++) {
        temp = temp + (this->global_list[i])->print() + "\n";
    }
    size_ = this->func_list.size();
    for (int i = 0; i < size_; i++) {
        temp = temp + this->func_list[i]->print() + "\n";
    }
    return temp;
}

void Module::add_globalvar(GlobalVar* g){
    this->global_list.push_back(g);
}

void Module::add_func(Function* f){
    this->func_list.push_back(f);
}

Const::Const(Type* type, const std::string& name) : Base(type, name) {
}

ConstNumber::ConstNumber(Type* type, float value, bool is_int) : Const(type, "") {
    this->value = value;
    this->is_int = is_int;
}

std::string ConstNumber::print() {
    if (this->is_int) {
        int value = this->value;
        return std::to_string(value == 0 ? value : (static_cast<IntType*>(this->type)->bits == 1 ? 1 : value));
    }else{
        double temp = this->value;
        std::stringstream s_print;
        std::string s;
        s_print << "0x" << std::hex << *(uint64_t*)&temp << std::endl;
        s_print >> s;
        return s;
    }
}

ConstArray::ConstArray(ArrayType* type, const std::vector<Const*>& value) : Const(type, "") {
    this->carr.assign(value.begin(), value.end());
}

std::string ConstArray::print() {
    std::string temp = "[";
    int size_ = this->carr.size();
    for (int i = 0; i < size_; i++) {
        temp = temp + static_cast<ArrayType*>(this->type)->contained->print() + " " + carr[i]->print();
        if (i != size_ - 1) {
            temp = temp + ", ";
        }
    }
    temp = temp + "]";
    return temp;
}

ConstZero::ConstZero(Type* type) : Const(type, "") {
}

std::string ConstZero::print() {
    return "zeroinitializer";
}

Function* Module::get_main() {
    int size_ = this->func_list.size();
    for (int i = 0; i < size_; i++) {
        if (this->func_list[i]->name == "main") {
            return this->func_list[i];
        }
    }
    return nullptr;
}

BinaryInst::BinaryInst(Type* type, int op, Base* x1, Base* x2, BasicBlock* bb) : Instr(type, op, 2, bb) {
    set_ope(0, x1);
    set_ope(1, x2);
}

std::string BinaryInst::print() {
    std::string temp = "%" + this->name + " = " + instr_sign[this->op_id] + " ";
    temp = temp + this->opes[0]->type->print() + " " + print_sign(this->get_ope(0), false) + ", ";
    temp = temp + print_sign(this->get_ope(1), false);
    return temp;
}

ICmpInst::ICmpInst(int op, Base* x1, Base* x2, BasicBlock* bb) : Instr(intType1, ICmp, 2, bb){
    this->icmp_op = op;
    this->set_ope(0, x1);
    this->set_ope(1, x2);
}

std::string ICmpInst::print() {
    std::string temp = "%" + this->name + " = " + instr_sign[this->op_id] + " " + change_cmp_instr[this->icmp_op] + " " + this->get_ope(0)->type->print() + " " + print_sign(this->get_ope(0), false);
    bool judge = (this->get_ope(0)->type->type_id == this->get_ope(1)->type->type_id);
    temp = temp + ", " + print_sign(this->get_ope(1), !judge);
    return temp;
}

FCmpInst::FCmpInst(int op, Base* x1, Base* x2, BasicBlock* bb) : Instr(intType1, FCmp, 2, bb){
    this->fcmp_op = op;
    this->set_ope(0, x1);
    this->set_ope(1, x2);
}

std::string FCmpInst::print() {
    std::string temp = "%" + this->name + " = " + instr_sign[this->op_id] + " " + change_cmp_instr[this->fcmp_op] + " " + this->get_ope(0)->type->print() + " " + print_sign(this->get_ope(0), false);
    bool judge = (this->get_ope(0)->type->type_id == this->get_ope(1)->type->type_id);
    temp = temp + ", " + print_sign(this->get_ope(1), !judge);
    return temp;
}

CallInst::CallInst(Function* func, std::vector<Base*> args, BasicBlock* bb) : Instr(static_cast<FuncType*>(func->type)->result, Call, args.size() + 1, bb) {
    int size_ = args.size();
    for (int i = 0; i < size_; i++) {
        set_ope(i, args[i]);
    }
    set_ope(size_, func);
}

std::string CallInst::print() {
    std::string temp = ((this->type->type_id == VOIDTYPE) ? "" : "%" + this->name + " = ");
    temp = temp + instr_sign[this->op_id] + " ";

    int size_ = this->num;
    temp = temp + static_cast<FuncType*>(this->get_ope(size_ - 1)->type)->result->print() + " ";

    temp = temp + print_sign(this->get_ope(size_ - 1), false) + "(";
    for (int i = 0;  i < size_ - 1; i++) {
        temp = temp + this->get_ope(i)->type->print() + " " + print_sign(this->get_ope(i), false);
        if (i != size_ - 2) {
            temp = temp + ", ";
        }
    }
    temp = temp + ")";
    return temp;
}

BranchInst::BranchInst(Base* cond, BasicBlock* if_true, BasicBlock* if_false, BasicBlock* bb) : Instr(voidType, Br, 3, bb) {
    if_true->add_pre_bb(bb);
    if_false->add_pre_bb(bb);
    bb->add_succ_bb(if_false);
    bb->add_succ_bb(if_true);
    set_ope(0, cond);
    set_ope(1, if_true);
    set_ope(2, if_false);
}

BranchInst::BranchInst(BasicBlock* if_true, BasicBlock* bb) : Instr(voidType, Br, 1, bb) {
    if_true->add_pre_bb(bb);
    bb->add_succ_bb(if_true);
    set_ope(0, if_true);
}

std::string BranchInst::print() {
    std::string temp = instr_sign[this->op_id] + " " + print_sign(this->get_ope(0), true);
    if (this->num == 3) {
        temp = temp + ", " + print_sign(this->get_ope(1), true) + ", " + print_sign(this->get_ope(2), true);
    }
    return temp;
}

ReturnInst::ReturnInst(Base* value, BasicBlock* bb) : Instr(voidType, Ret, 1, bb){
    set_ope(0, value);
}

ReturnInst::ReturnInst(BasicBlock* bb) : Instr(voidType, Ret, 0, bb){
}

std::string ReturnInst::print() {
    std::string temp = instr_sign[this->op_id] + " ";
    temp = temp + (this->num == 0 ? "void" : (this->get_ope(0)->type->print() + " " + print_sign(this->get_ope(0), false)));
    return temp;
}

GetElementPtrInst::GetElementPtrInst(Base* p, std::vector<Base*> indexs, BasicBlock* bb) : Instr(get_ptype(get_rettype(p, indexs.size())), GetElementPtr, indexs.size() + 1, bb){
    set_ope(0, p);
    int size_ = indexs.size();
    for (int i = 1; i < size_ + 1; i++) {
        set_ope(i, indexs[i - 1]);
    }
}

std::string GetElementPtrInst::print() {
    std::string temp = "%" + this->name + " = " + instr_sign[this->op_id] + " ";
    temp = temp + static_cast<PType*>(this->get_ope(0)->type)->contained->print() + ", ";
    for (int i = 0; i < this->num; i++) {
        temp = temp + print_sign(this->get_ope(i), true);
        if (i != this->num - 1) {
            temp = temp + ", ";
        }
    }
    return temp;
}

StoreInst::StoreInst(Base* value, Base* p, BasicBlock* bb) : Instr(voidType, Store, 2, bb){
    set_ope(0, value);
    set_ope(1, p);
}

std::string StoreInst::print() {
    std::string temp = instr_sign[this->op_id] + " " + print_sign(this->get_ope(0), true) + ", " + print_sign(this->get_ope(1), true);
    return temp;
}

LoadInst::LoadInst(Base* p, BasicBlock* bb) : Instr(static_cast<PType*>(p->type)->contained, Load, 1, bb){
    set_ope(0, p);
}

std::string LoadInst::print() {
    std::string temp = "%" + this->name + " = " + instr_sign[this->op_id] + " " + static_cast<PType*>(this->get_ope(0)->type)->contained->print() + ", " + print_sign(this->get_ope(0), true);
    return temp;
}

AllocaInst::AllocaInst(Type* type, BasicBlock* bb) : Instr(get_ptype(type), Alloca, 0, bb){
    this->alloc_type = type;
}

std::string AllocaInst::print() {
    std::string temp = "%" + this->name + " = " + instr_sign[this->op_id] + " " + this->alloc_type->print();
    return temp;
}

CastInst::CastInst(int op, Base * value, Type * type, BasicBlock * bb) : Instr(type, op, 1, bb) {
    this->change_to_type = type;
    set_ope(0, value);
}

std::string CastInst::print() {
    return "%" + this->name + " = " + instr_sign[this->op_id] + " " + print_sign(this->get_ope(0), true) + " to " + this->change_to_type->print();
}