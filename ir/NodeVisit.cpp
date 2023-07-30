#include<iostream>
#include<cstdlib>
#include "NodeVisit.h"

BasicBlock* BB = nullptr;
BasicBlock* return_BB = nullptr;
BasicBlock* while_cond_BB = nullptr;
BasicBlock* while_false_BB = nullptr;
BasicBlock* true_BB = nullptr;
BasicBlock* false_BB = nullptr;
Base* return_var = nullptr;
bool is_br = false;
bool is_new_function = false;
Function* FUNC = nullptr;


void change_del_type(Type* type, Base* &value, BasicBlock* BB);
bool change_var_type(Base* first_value, Base* second_value, BasicBlock* bb);
ConstArray* array_init(Type* type, NodeVisit* nodevisit, vector<int>& indexs, vector<ArrayType*>& arrType, vector<ConstInitValNode*>& arrays, int now_index);
void merge_before(vector<int>& indexs, vector<ArrayType*>& arrType, vector<Const*>& elements, vector<int>& index_element_count, int now_index, int before_index);
void merge_final(Type* type, vector<int>& indexs, vector<ArrayType*>& arrType, vector<Const*>& elements, vector<int>& index_element_count, int now_index);
void block_array_init(Type* type, NodeVisit* nodevisit, Base* p, vector<ConstInitValNode*>& arrays, vector<int>& index_mem, int now_index);
ConstArray* array_var_init(Type* type, NodeVisit* nodevisit, vector<int>& indexs, vector<ArrayType*>& arrType, vector<InitValNode*>& arrays, int now_index);
void block_array_var_init(Type* type, NodeVisit* nodevisit, Base* p, vector<InitValNode*>& arrays, vector<int>& index_mem, int now_index);

NodeVisit::NodeVisit() {
    module = new Module();
    this->Sym.push_back(new Symbol());

    auto func_type = new FuncType(intType32, {});
    this->Sym[0]->symbol.insert({ "getint", new Function(func_type, "getint", module) });
    this->Sym[0]->symbol.insert({ "getch", new Function(func_type, "getch", module) });

    func_type = new FuncType(floatType, {});
    this->Sym[0]->symbol.insert({ "getfloat", new Function(func_type, "getfloat", module) });

    vector<Type*> func_args;
    func_args.clear();
    func_args.push_back(get_ptype(intType32));
    func_type = new FuncType(intType32, func_args);
    this->Sym[0]->symbol.insert({ "getarray", new Function(func_type, "getarray", module) });

    func_args.clear();
    func_args.push_back(get_ptype(floatType));
    func_type = new FuncType(intType32, func_args);
    this->Sym[0]->symbol.insert({ "getfarray", new Function(func_type, "getfarray", module) });

    func_args.clear();
    func_args.push_back(intType32);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "putint", new Function(func_type, "putint", module) });
    this->Sym[0]->symbol.insert({ "putch", new Function(func_type, "putch", module) });

    func_args.clear();
    func_args.push_back(floatType);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "putfloat", new Function(func_type, "putfloat", module) });

    func_args.clear();
    func_args.push_back(intType32);
    func_args.push_back(get_ptype(intType32));
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "putarray", new Function(func_type, "putarray", module) });

    func_args.clear();
    func_args.push_back(intType32);
    func_args.push_back(get_ptype(floatType));
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "putfarray", new Function(func_type, "putfarray", module) });

    func_args.clear();
    func_args.push_back(intType32);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "_sysy_starttime", new Function(func_type, "_sysy_starttime", module) });
    this->Sym[0]->symbol.insert({ "_sysy_stoptime", new Function(func_type, "_sysy_stoptime", module) });

    func_args.clear();
    func_args.push_back(get_ptype(intType32));
    func_args.push_back(get_ptype(intType32));
    func_args.push_back(intType32);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "__aeabi_memcpy4", new Function(func_type, "__aeabi_memcpy4", module) });

    func_args.clear();
    func_args.push_back(get_ptype(intType32));
    func_args.push_back(intType32);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "__aeabi_memclr4", new Function(func_type, "__aeabi_memclr4", module) });

    func_args.push_back(intType32);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "__aeabi_memset4", new Function(func_type, "__aeabi_memset4", module) });

    func_args.clear();
    func_args.push_back(get_ptype(intType32));
    func_args.push_back(intType8);
    func_args.push_back(intType32);
    func_args.push_back(intType1);
    func_type = new FuncType(voidType, func_args);
    this->Sym[0]->symbol.insert({ "llvm.memset.p0.i32", new Function(func_type, "llvm.memset.p0.i32", module) });
}

Module* NodeVisit::getModule() {
    return this->module;
}

void NodeVisit::visit(RootNode* node) {
    this->visit(static_cast<CompUnitNode*>(node->node));
}

void NodeVisit::visit(CompUnitNode* node){
    if (node->decl != nullptr && node->next == nullptr) {
        this->visit(static_cast<DeclNode*>(node->decl));
    }else if(node->funcdef != nullptr && node->next == nullptr){
        this->visit(static_cast<FuncDefNode*>(node->funcdef));
    }else if(node->decl != nullptr && node->next != nullptr){
        this->visit(static_cast<DeclNode*>(node->decl));
        this->visit(static_cast<CompUnitNode*>(node->next));
    }else if(node->funcdef != nullptr && node->next != nullptr){
        this->visit(static_cast<FuncDefNode*>(node->funcdef));
        this->visit(static_cast<CompUnitNode*>(node->next));
    }
}

void NodeVisit::visit(DeclNode* node) {
    if (node->constdecl != nullptr) {
        this->visit(static_cast<ConstDeclNode*>(node->constdecl));
    }else if(node->vardecl != nullptr){
        this->visit(static_cast<VarDeclNode*>(node->vardecl));
    }
}

void NodeVisit::visit(ConstDeclNode* node){
    Type* type;
    if (node->type == INTTYPE) {
        type = intType32;
    }else if(node->type == FLOATTYPE){
        type = floatType;
    }
    this->visit(type, static_cast<ConstDefsNode*>(node->constdefs));
}

void NodeVisit::visit(Type* type, ConstDefsNode* node) {
    this->visit(type, static_cast<ConstDefNode*>(node->constdef));
    if (node->next != nullptr) {
        this->visit(type, static_cast<ConstDefsNode*>(node->next));
    }
}

void NodeVisit::visit(Type* type, ConstDefNode* node) {
    std::string name = node->id;
    int tag_ = this->Sym.size() - 1;
    if (this->Sym[tag_]->symbol.find(name) != this->Sym[tag_]->symbol.end()) {
        std::cout << "error: Identifier redefinition " << name << std::endl;
        std::exit(0);
    }
    if(tag_ == 0){
        if (node->constarray == nullptr) {
            Base* init = dynamic_cast<Base*>(this->visit(static_cast<ConstInitValNode*>(node->constinitval)));
            change_del_type(type, init, BB);
            this->Sym[tag_]->symbol.insert({name, init});
        }else{
            vector<int> indexs;
            this->visit(static_cast<ConstArrayListNode*>(node->constarray), indexs);

            int size_ = indexs.size();
            vector<ArrayType*> arrType(size_);
            for (int i = size_ - 1; i >= 0; i--) {
                if (i == size_ - 1) {
                    arrType[i] = get_atype(type, indexs[i]);
                }else{
                    arrType[i] = get_atype(arrType[i + 1], indexs[i]);
                }
            }

            if (node->constinitval == nullptr) {
                std::cout << "error:uninitialized const " << name << std::endl;
                std::exit(0);
            }
            if(static_cast<ConstInitValNode*>(node->constinitval)->constexp != nullptr){
                std::cout << "error:array must be initialized with a brace-enclosed initializer " << name << std::endl;
                std::exit(0);
            }

            //语法分析问题， 无法识别数组大括号初始化，例：const int a[10] = {};（待修改）
            if (static_cast<ConstInitValNode*>(node->constinitval)->constinitvals == nullptr) {
                this->Sym[tag_]->symbol.insert({name, new GlobalVar(name, module, arrType[0], true, new ConstZero(arrType[0])) });
            }else{
                vector<ConstInitValNode*> arrays;
                this->visit(static_cast<ConstInitValsNode*>(static_cast<ConstInitValNode*>(node->constinitval)->constinitvals), arrays);
                auto temp = array_init(type, this, indexs, arrType, arrays, 0);
                auto add_temp = new GlobalVar(name, module, arrType[0], true, temp);
                this->Sym[tag_]->symbol.insert({name, add_temp});
            }
        }
    }else{
        if (node->constarray == nullptr){
            auto temp = this->visit(static_cast<ConstInitValNode*>(node->constinitval));
            change_del_type(type, temp, BB);
            this->Sym[tag_]->symbol.insert({name, temp});
        }else{
            vector<int> indexs;
            this->visit(static_cast<ConstArrayListNode*>(node->constarray), indexs);

            int size_ = indexs.size();
            ArrayType* arrType;
            for (int i = size_ - 1; i >= 0; i--) {
                if (i == size_ - 1) {
                    arrType = get_atype(type, indexs[i]);
                }
                else {
                    arrType = get_atype(arrType, indexs[i]);
                }
            }
            Base* temp = new AllocaInst(arrType, BB);
            this->Sym[this->Sym.size() - 1]->symbol.insert({name, temp});

            if (node->constinitval == nullptr) {
                std::cout << "error:uninitialized const " << name << std::endl;
                std::exit(0);
            }
            Base* func = this->Sym[0]->symbol.find("__aeabi_memclr4")->second;
            Base* temp_p = new CastInst(BitCast, temp, get_ptype(intType32), BB);
            vector<int> index_mem(size_);
            int total_mem = 1;;
            for (int i = size_ - 1; i >= 0; i--) {
                total_mem = total_mem * indexs[i];
                index_mem[i] = total_mem;
            }
            total_mem = total_mem * 4;
            auto call_func = new CallInst(static_cast<Function*>(func), {temp_p, new ConstNumber(intType32, total_mem, true)}, BB);
            if (static_cast<ConstInitValNode*>(node->constinitval)->constinitvals == nullptr) {
                return;
            }
            else {
                vector<ConstInitValNode*> arrays;
                this->visit(static_cast<ConstInitValsNode*>(static_cast<ConstInitValNode*>(node->constinitval)->constinitvals), arrays);
                vector<Base*> array_location;
                for (int i = 0; i < size_ + 1; i++) {
                    array_location.push_back(new ConstNumber(intType32, 0, true));
                }
                Base* first_location = new GetElementPtrInst(temp, array_location, BB);
                block_array_init(type, this, first_location, arrays, index_mem, 1);
            }
        }
    }
}

Base* NodeVisit::visit(ConstInitValNode* node) {
    if (node->constexp != nullptr) {
        return this->visit(static_cast<ConstExpNode*>(node->constexp));
    }
    return nullptr;
}

void NodeVisit::visit(ConstInitValsNode* node, vector<ConstInitValNode*>& arrays) {
    if (node->constinitval != nullptr) {
        arrays.push_back(static_cast<ConstInitValNode*>(node->constinitval));
    }
    if (node->next != nullptr) {
        this->visit(static_cast<ConstInitValsNode*>(node->next), arrays);
    }
}

void NodeVisit::visit(ConstArrayListNode* node, vector<int>& indexs) {
    int num = dynamic_cast<ConstNumber*>(this->visit(static_cast<ConstExpNode*>(node->constexp)))->value;
    indexs.push_back(num);
    if (node->next != nullptr) {
        this->visit(static_cast<ConstArrayListNode*>(node->next), indexs);
    }
}

Base* NodeVisit::visit(ConstExpNode* node) {
    return this->visit(static_cast<AddExpNode*>(node->addexp), true);
}

Base* NodeVisit::visit(AddExpNode* node, bool is_const){
    if (node->addexp == nullptr) {
        return this->visit(static_cast<MulExpNode*>(node->mulexp), is_const);
    }else{
        auto first_value = this->visit(static_cast<AddExpNode*>(node->addexp), is_const);
        auto second_value = this->visit(static_cast<MulExpNode*>(node->mulexp), is_const);
        if(is_const){
            bool judge = static_cast<ConstNumber*>(first_value)->is_int && static_cast<ConstNumber*>(second_value)->is_int;
            float x1 = static_cast<ConstNumber*>(first_value)->value;
            float x2 = static_cast<ConstNumber*>(second_value)->value;
            float result;
            if(node->optype == ADDOP){
                result = x1 + x2;
            }else if(node->optype == MINUSOP){
                result = x1 - x2;
            }
            if (judge) {
                return new ConstNumber(intType32, (int)result, true);
            }else{
                return new ConstNumber(floatType, result, false);
            }
        }else{
            bool judge = change_var_type(first_value, second_value, BB);
            int choose_op = judge ? (node->optype == ADDOP ? Add : Sub) : (node->optype == ADDOP ? FAdd : FSub);
            if (judge) {
                return new BinaryInst(intType32, choose_op, first_value, second_value, BB);
            }else{
                return new BinaryInst(floatType, choose_op, first_value, second_value, BB);
            }
        }
    }
}

Base* NodeVisit::visit(MulExpNode* node, bool is_const) {
    if (node->mulexp == nullptr) {
        return this->visit(static_cast<UnaryExpNode*>(node->unaryexp), is_const);
    }
    else {
        auto first_value = this->visit(static_cast<MulExpNode*>(node->mulexp), is_const);
        auto second_value = this->visit(static_cast<UnaryExpNode*>(node->unaryexp), is_const);
        if (is_const) {
            bool judge = static_cast<ConstNumber*>(first_value)->is_int && static_cast<ConstNumber*>(second_value)->is_int;
            float x1 = static_cast<ConstNumber*>(first_value)->value;
            float x2 = static_cast<ConstNumber*>(second_value)->value;
            float result;
            if (node->optype == MULOP) {
                result = x1 * x2;
            }else if (node->optype == DIVOP) {
                result = x1 / x2;
            }else if(node->optype == MODOP){
                if (static_cast<ConstNumber*>(first_value)->type == floatType || static_cast<ConstNumber*>(second_value)->type == floatType) {
                    std::cout << "error:invalid operands of types to binary %" << std::endl;
                    std::exit(0);
                }
                result = (int)x1 % (int)x2;
            }
            if (judge) {
                return new ConstNumber(intType32, (int)result, true);
            }
            else {
                return new ConstNumber(floatType, result, false);
            }
        }
        else {
            bool judge = change_var_type(first_value, second_value, BB);
            if (judge == false && node->optype == MODOP) {
                std::cout << "error:invalid operands of types to binary %" << std::endl;
                std::exit(0);
            }
            int choose_op = judge ? (node->optype == MULOP ? Mul : (node->optype == DIVOP) ? SDiv : SRem) : (node->optype == MULOP ? FMul : FDiv);
            if (judge) {
                return new BinaryInst(intType32, choose_op, first_value, second_value, BB);
            }
            else {
                return new BinaryInst(floatType, choose_op, first_value, second_value, BB);
            }
        }
    }
}

Base* NodeVisit::visit(UnaryExpNode* node, bool is_const) {
    if (node->primaryexp != nullptr) {
        return this->visit(static_cast<PrimaryExpNode*>(node->primaryexp), is_const);
    }
    if (is_const) {
        if(node->unaryexp != nullptr){
            auto now_value = this->visit(static_cast<UnaryExpNode*>(node->unaryexp), is_const);
            if (node->optype == MINUSOP && dynamic_cast<ConstNumber*>(now_value)) {
                ConstNumber* temp = (ConstNumber*)now_value;
                temp->value = -(temp->value);
                return temp;
            }
            return now_value;
        }
    }else{
        if(node->unaryexp != nullptr){
            Base* now_value = this->visit(static_cast<UnaryExpNode*>(node->unaryexp), is_const);
            if (now_value->type == voidType || node->optype == ADDOP) {
                return now_value;
            }
            if(now_value->type == intType1){
                now_value = new CastInst(ZExt, now_value, intType32, BB);
            }
            if (node->optype == MINUSOP) {
                if (now_value->type == intType32) {
                    return new BinaryInst(intType32, Sub, new ConstNumber(intType32, 0, true), now_value, BB);
                }else{
                    return new BinaryInst(floatType, FSub, new ConstNumber(floatType, 0, false), now_value, BB);
                }
            }else if(node->optype == NOTOP){
                if (now_value->type == intType32) {
                    return new ICmpInst(IEQ, now_value, new ConstNumber(intType32, 0, true), BB);
                }else{
                    return new FCmpInst(FUEQ, now_value, new ConstNumber(floatType, 0, false), BB);
                }
            }
        }else if(node->isCallingFunc){
            int size_Sym = this->Sym.size();
            Function* now_function;
            bool judge = false;
            for (int i = size_Sym - 1;  i >= 0; i--) {
                auto temp = this->Sym[i]->symbol.find(node->id);
                if(temp != this->Sym[i]->symbol.end()){
                    judge = true;
                    now_function = (Function*)temp->second;
                    break;
                }
            }
            if (judge == false) {
                std::cout << "error:function was not declared in this scope" << std::endl;
                std::exit(0);
            }
            vector<Base*> args;
            if (node->funcrparams != nullptr) {
                this->visit(static_cast<FuncRParamsNode*>(node->funcrparams), args);
            }
            if (now_function->args.size() < args.size()) {
                std::cout << "error:too many arguments to function" << std::endl;
                std::exit(0);
            }else if(now_function->args.size() > args.size()){
                std::cout << "error:too few arguments to function" << std::endl;
                std::exit(0);
            }
            int size_now_function = now_function->args.size();
            for (int i = 0; i < size_now_function; i++) {
                if (args[i]->type == intType32 && now_function->args[i]->type == floatType) {
                    return new CastInst(SItoFP, args[i], floatType, BB);
                }else if(args[i]->type == floatType && now_function->args[i]->type == intType32){
                    return new CastInst(FPtoSI, args[i], intType32, BB);
                }
            }
            return new CallInst(now_function, args, BB);
        }
    }
    return nullptr;
}

Base* NodeVisit::visit(PrimaryExpNode* node, bool is_const) {
    if (node->exp != nullptr) {
        return this->visit(static_cast<ExpNode*>(node->exp), is_const);
    }else if(node->lval != nullptr){
        return this->visit(static_cast<LValNode*>(node->lval), false);
    }
    if(node->type == INTTYPE){
        return new ConstNumber(intType32, node->intval, true);
    }else if(node->type == FLOATTYPE){
        return new ConstNumber(floatType, node->floatval, false);
    }
    return nullptr;
}

void NodeVisit::visit(FuncRParamsNode* node, vector<Base*>& args){
    args.push_back(this->visit(static_cast<ExpNode*>(node->exp), false));
    if (node->next != nullptr) {
        this->visit(static_cast<FuncRParamsNode*>(node->next), args);
    }
}

Base* NodeVisit::visit(ExpNode* node, bool is_const) {
    return this->visit(static_cast<AddExpNode*>(node->addexp), is_const);
}

Base* NodeVisit::visit(LValNode* node, bool is_left_value) {
    int size_Sym = this->Sym.size();
    Base* value;
    bool judge = false;
    for (int i = size_Sym - 1; i >= 0; i--) {
        auto temp = this->Sym[i]->symbol.find(node->id);
        if (temp != this->Sym[i]->symbol.end()) {
            judge = true;
            value = (Base*)temp->second;
            break;
        }
    }
    if (judge == false) {
        std::cout << "error:" << node->id << "was not declared in this scope" << std::endl;
        std::exit(0);
    }
    if (size_Sym == 1) {
        if (node->array == nullptr) {
            return value;
        }
        vector<int> indexs;
        this->visit(static_cast<ArrayListNode*>(node->array), indexs, false);

        Base* return_value = ((GlobalVar*)value)->value;
        int size_ = indexs.size();
        for (int i = 0; i < size_; i++) {
            if (dynamic_cast<ConstZero*>(return_value)) {
                Type* type = return_value->type;
                while (dynamic_cast<ArrayType*>(type)) {
                    type = dynamic_cast<ArrayType*>(type)->contained;
                }
                if (type == intType32) {
                    return new ConstNumber(intType32, 0, true);
                }else{
                    return new ConstNumber(floatType, 0, false);
                }
            }
            if (dynamic_cast<ConstArray*>(return_value)) {
                return_value = ((ConstArray*)return_value)->carr[indexs[i]];
            }
        }
        return return_value;
    }
    if (value->type->type_id == INTTYPE || value->type->type_id == FLOATTYPE) {
        return value;
    }
    Type* type = static_cast<PType*>(value->type)->contained;
    if(node->array != nullptr){
        vector<Base*> indexs;
        this->visit(static_cast<ArrayListNode*>(node->array), indexs, false);
        if (type->type_id == POINTTYPE) {
            value = new LoadInst(value, BB);
        }else if(type->type_id == ARRAYTYPE){
            indexs.insert(indexs.begin(), new ConstNumber(intType32, 0, true));
        }
        value = new GetElementPtrInst(value, indexs, BB);
        type = ((PType*)value->type)->contained;
    }
    if (type->type_id == ARRAYTYPE) {
        return new GetElementPtrInst(value, { new ConstNumber(intType32, 0, true), new ConstNumber(intType32, 0, true)}, BB);
    }
    else if (is_left_value == false) {
        return new LoadInst(value, BB);
    }else{
        return value;
    }
    return nullptr;
}

void NodeVisit::visit(ArrayListNode* node, vector<int>& indexs, bool is_const) {
    int num = dynamic_cast<ConstNumber*>(this->visit(static_cast<ExpNode*>(node->exp), is_const))->value;
    indexs.push_back(num);
    if (node->next != nullptr) {
        this->visit(static_cast<ArrayListNode*>(node->next), indexs, is_const);
    }
}

void NodeVisit::visit(ArrayListNode* node, vector<Base*>& indexs, bool is_const) {
    Base* num = this->visit(static_cast<ExpNode*>(node->exp), is_const);
    indexs.push_back(num);
    if (node->next != nullptr) {
        this->visit(static_cast<ArrayListNode*>(node->next), indexs, is_const);
    }
}

void NodeVisit::visit(VarDeclNode* node) {
    Type* type;
    if (node->type == INTTYPE) {
        type = intType32;
    }
    else if (node->type == FLOATTYPE) {
        type = floatType;
    }
    this->visit(type, static_cast<VarDefsNode*>(node->vardefs));
}

void NodeVisit::visit(Type* type, VarDefsNode* node) {
    this->visit(type, static_cast<VarDefNode*>(node->vardef));
    if (node->next != nullptr) {
        this->visit(type, static_cast<VarDefsNode*>(node->next));
    }
}

void NodeVisit::visit(Type* type, VarDefNode* node) {
    std::string name = node->id;
    int tag_ = this->Sym.size() - 1;
    if (this->Sym[tag_]->symbol.find(name) != this->Sym[tag_]->symbol.end()) {
        std::cout << "error: Identifier redefinition " << name << std::endl;
        std::exit(0);
    }
    if (tag_ == 0) {
        if (node->constarray == nullptr) {
            if (node->initval == nullptr) {
                if (type == intType32) {
                    this->Sym[tag_]->symbol.insert({ name, new GlobalVar(name, module, type, false, new ConstNumber(intType32, 0, true)) });
                }else{
                    this->Sym[tag_]->symbol.insert({ name, new GlobalVar(name, module, type, false, new ConstNumber(floatType, 0, false)) });
                }
            }else{
                Base* init = this->visit(static_cast<InitValNode*>(node->initval), true);
                change_del_type(type, init, BB);
                auto now_init = static_cast<Const*>(init);
                this->Sym[tag_]->symbol.insert({ name, new GlobalVar(name, module, type, false, now_init) });
            }
        }else {
            vector<int> indexs;
            this->visit(static_cast<ConstArrayListNode*>(node->constarray), indexs);

            int size_ = indexs.size();
            vector<ArrayType*> arrType(size_);
            for (int i = size_ - 1; i >= 0; i--) {
                if (i == size_ - 1) {
                    arrType[i] = get_atype(type, indexs[i]);
                }
                else {
                    arrType[i] = get_atype(arrType[i + 1], indexs[i]);
                }
            }

            if (node->initval != nullptr && static_cast<InitValNode*>(node->initval)->exp != nullptr) {
                std::cout << "error:array must be initialized with a brace-enclosed initializer " << name << std::endl;
                std::exit(0);
            }
            //语法分析问题， 无法识别数组大括号初始化，例：const int a[10] = {};（待修改）
            if (node->initval == nullptr || static_cast<InitValNode*>(node->initval)->initvals == nullptr) {
                this->Sym[tag_]->symbol.insert({ name, new GlobalVar(name, module, arrType[0], false, new ConstZero(arrType[0])) });
            }
            else {
                vector<InitValNode*> arrays;
                this->visit(static_cast<InitValsNode*>(static_cast<InitValNode*>(node->initval)->initvals), arrays);
                auto temp = array_var_init(type, this, indexs, arrType, arrays, 0);
                auto add_temp = new GlobalVar(name, module, arrType[0], false, temp);
                this->Sym[tag_]->symbol.insert({ name, add_temp });
            }
        }
    }else {
        if (node->constarray == nullptr) {
            if (node->initval == nullptr) {
                this->Sym[tag_]->symbol.insert({name, new AllocaInst(type, BB)});
            }else{
                auto temp = this->visit(static_cast<InitValNode*>(node->initval), false);
                change_del_type(type, temp, BB);
                AllocaInst* alloca_ = new AllocaInst(type, BB);
                this->Sym[tag_]->symbol.insert({name, alloca_});
                auto store_var = new StoreInst(temp, alloca_, BB);
            }
        }
        else {
            vector<int> indexs;
            this->visit(static_cast<ConstArrayListNode*>(node->constarray), indexs);

            int size_ = indexs.size();
            ArrayType* arrType;
            for (int i = size_ - 1; i >= 0; i--) {
                if (i == size_ - 1) {
                    arrType = get_atype(type, indexs[i]);
                }
                else {
                    arrType = get_atype(arrType, indexs[i]);
                }
            }
            Base* temp = new AllocaInst(arrType, BB);
            this->Sym[0]->symbol.insert({ name, temp });

            if (node->initval == nullptr) {
                return;
            }
            Base* func = this->Sym[0]->symbol.find("__aeabi_memclr4")->second;
            Base* temp_p = new CastInst(BitCast, temp, get_ptype(intType32), BB);
            vector<int> index_mem(size_);
            int total_mem = 1;;
            for (int i = size_ - 1; i >= 0; i--) {
                total_mem = total_mem * indexs[i];
                index_mem[i] = total_mem;
            }
            total_mem = total_mem * 4;
            auto call_func = new CallInst(static_cast<Function*>(func), { temp_p, new ConstNumber(intType32, total_mem, true) }, BB);
            if (static_cast<InitValNode*>(node->initval)->initvals == nullptr) {
                return;
            }
            else {
                vector<InitValNode*> arrays;
                this->visit(static_cast<InitValsNode*>(static_cast<InitValNode*>(node->initval)->initvals), arrays);
                vector<Base*> array_location;
                for (int i = 0; i < size_ + 1; i++) {
                    array_location.push_back(new ConstNumber(intType32, 0, true));
                }
                Base* first_location = new GetElementPtrInst(temp, array_location, BB);
                block_array_var_init(type, this, first_location, arrays, index_mem, 1);
            }
        }
    }
}

Base* NodeVisit::visit(InitValNode* node, bool is_const) {
    if (node->exp != nullptr) {
        return this->visit(static_cast<ExpNode*>(node->exp), is_const);
    }
    return nullptr;
}

void NodeVisit::visit(InitValsNode* node, vector<InitValNode*>& arrays) {
    if (node->initval != nullptr) {
        arrays.push_back(static_cast<InitValNode*>(node->initval));
    }
    if (node->next != nullptr) {
        this->visit(static_cast<InitValsNode*>(node->next), arrays);
    }
}

void NodeVisit::visit(FuncDefNode* node) {
    std::string name = node->id;
    is_new_function = true;
    vector<pair<Type*, std::string>> params;
    if (node->funcfparams != nullptr) {
        this->visit(static_cast<FuncFParamsNode*>(node->funcfparams), params);
    }
    Type* return_type;
    if (node->type == VOIDTYPE) {
        return_type = voidType;
    }else if(node->type == INTTYPE){
        return_type = intType32;
    }else if(node->type == FLOATTYPE){
        return_type = floatType;
    }
    vector<Type*> func_params_type;
    int size_ = params.size();
    for (int i = 0; i < size_; i++) {
        func_params_type.push_back(params[i].first);
    }
    FuncType* func_type = new FuncType(return_type, func_params_type);
    Function* func = new Function(func_type, name, module);
    this->Sym[this->Sym.size() - 1]->symbol.insert({name, func});
    this->Sym.push_back(new Symbol());
    FUNC = func;

    BasicBlock* bb = new BasicBlock(module, "label_entry", func);
    BB = bb;

    size_ = params.size();
    for (int i = 0; i < size_; i++) {
        Base* temp = new AllocaInst(params[i].first, BB);
        auto store_temp = new StoreInst(func->args[i], temp, BB);
        this->Sym[this->Sym.size() - 1]->symbol.insert({params[i].second, temp});
    }
    return_BB = new BasicBlock(module, "label_ret", func);
    if (return_type == voidType) {
        BB = return_BB;
        auto temp = new ReturnInst(BB);
    }else{
        return_var = new AllocaInst(return_type, BB);
        BB = return_BB;
        auto ret = new ReturnInst(new LoadInst(return_var, BB), BB);
    }
    BB = bb;
    is_br = false;
    this->visit(static_cast<BlockNode*>(node->block));
    if (BB->get_last() == nullptr) {
        auto temp = new BranchInst(return_BB, BB);
    }
}

void NodeVisit::visit(FuncFParamsNode* node, vector<pair<Type*, std::string>>& params){
    if (node->funcfparam != nullptr) {
        this->visit(static_cast<FuncFParamNode*>(node->funcfparam), params);
    }
    if (node->next != nullptr) {
        this->visit(static_cast<FuncFParamsNode*>(node->next), params);
    }
}

void NodeVisit::visit(FuncFParamNode* node, vector<pair<Type*, std::string>>& params){
    std::string name = node->id;
    Type* type;
    if (node->type == INTTYPE) {
        type = intType32;
    }
    else if (node->type == FLOATTYPE) {
        type = floatType;
    }
    if (node->hasArray == true) {
        if (node->array != nullptr) {
            vector<int> indexs;
            this->visit(static_cast<ArrayListNode*>(node->array), indexs, true);
            int size_ = indexs.size();
            for (int i = size_ - 1; i >= 0; i--) {
                type = get_atype(type, indexs[i]);
            }
        }
        type = get_ptype(type);
    }
    params.push_back(std::make_pair(type, name));
}

void NodeVisit::visit(BlockNode* node){
    if (is_new_function == true) {
        is_new_function = false;
    }else{
        this->Sym.push_back(new Symbol());
    }
    if (node->blockitems != nullptr) {
        this->visit(static_cast<BlockItemsNode*>(node->blockitems));
    }
    this->Sym.pop_back();
}

void NodeVisit::visit(BlockItemsNode* node){
    if (node->blockitem != nullptr) {
        this->visit(static_cast<BlockItemNode*>(node->blockitem));
    }
    if (node->next != nullptr) {
        this->visit(static_cast<BlockItemsNode*>(node->next));
    }
}

void NodeVisit::visit(BlockItemNode* node) {
    if (node->decl != nullptr) {
        this->visit(static_cast<DeclNode*>(node->decl));
    }
    if (node->stmt != nullptr) {
        this->visit(static_cast<StmtNode*>(node->stmt));
    }
}

Base* NodeVisit::visit(StmtNode* node) {
    if (node->stmttype == ASSIGNSTMT) {
        Base* lval = this->visit(static_cast<LValNode*>(node->lval), true);
        Base* exp = this->visit(static_cast<ExpNode*>(node->exp), false);
        if (lval->type->type_id == FLOATTYPE && exp->type->type_id == INTTYPE) {
            exp = new CastInst(SItoFP, exp, floatType, BB);
        }else if(lval->type->type_id == INTTYPE && exp->type->type_id == FLOATTYPE){
            exp = new CastInst(FPtoSI, exp, intType32, BB);
        }
        auto temp = new StoreInst(exp, lval, BB);
        return nullptr;
    }
    if (node->stmttype == NULLSTMT) {
        return nullptr;
    }
    if (node->stmttype == EXPSTMT) {
        this->visit(static_cast<ExpNode*>(node->exp), false);
        return nullptr;
    }
    if (node->stmttype == BLOCKSTMT) {
        this->visit(static_cast<BlockNode*>(node->block));
        return nullptr;
    }
    if (node->stmttype == IFSTMT) {
        BasicBlock* temp_true_BB = true_BB;
        BasicBlock* temp_false_BB = false_BB;
        BasicBlock* next;

        true_BB = new BasicBlock(module, "", FUNC);
        false_BB = new BasicBlock(module, "", FUNC);
        if (node->elsestmt == nullptr) {
            next = false_BB;
        }else{
            next = new BasicBlock(module, "", FUNC);
        }
        Base* temp_cond = this->visit(static_cast<CondNode*>(node->cond));
        if (temp_cond->type == intType32) {
            temp_cond = new ICmpInst(INE, temp_cond, new ConstNumber(intType32, 0, true), BB);
        }else if(temp_cond->type == floatType){
            temp_cond = new FCmpInst(FUNE, temp_cond, new ConstNumber(floatType, 0, false), BB);
        }
        auto temp_br = new BranchInst(temp_cond, true_BB, false_BB, BB);
        BB = true_BB;
        is_br = false;

        this->visit(static_cast<StmtNode*>(node->stmt));
        if (BB->get_last() == nullptr) {
            auto temp = new BranchInst(next, BB);
        }
        if (node->elsestmt != nullptr) {
            BB = false_BB;
            is_br = false;
            this->visit(static_cast<StmtNode*>(node->elsestmt));
            if (BB->get_last() == nullptr) {
                auto temp = new BranchInst(next, BB);
            }
        }
        BB = next;
        is_br = false;
        true_BB = temp_true_BB;
        false_BB = temp_false_BB;
        return nullptr;
    }
    if (node->stmttype == WHILESTMT) {
        BasicBlock* temp_true_BB = true_BB;
        BasicBlock* temp_false_BB = false_BB;
        BasicBlock* temp_while_cond_BB = while_cond_BB;
        BasicBlock* temp_while_false_BB = while_false_BB;

        while_cond_BB = new BasicBlock(module, "", FUNC);
        true_BB = new BasicBlock(module, "", FUNC);
        false_BB = new BasicBlock(module, "", FUNC);
        while_false_BB = false_BB;

        auto temp = new BranchInst(while_cond_BB, BB);
        BB = while_cond_BB;
        is_br = false;
        Base* temp_cond = this->visit(static_cast<CondNode*>(node->cond));
        if (temp_cond->type == intType32) {
            temp_cond = new ICmpInst(INE, temp_cond, new ConstNumber(intType32, 0, true), BB);
        }
        else if (temp_cond->type == floatType) {
            temp_cond = new FCmpInst(FUNE, temp_cond, new ConstNumber(floatType, 0, false), BB);
        }
        auto temp_br = new BranchInst(temp_cond, true_BB, false_BB, BB);
        BB = true_BB;
        is_br = false;

        this->visit(static_cast<StmtNode*>(node->stmt));
        if (BB->get_last() == nullptr) {
            auto temp = new BranchInst(while_cond_BB, BB);
        }
        
        BB = false_BB;
        is_br = false;
        true_BB = temp_true_BB;
        false_BB = temp_false_BB;
        while_cond_BB = temp_while_cond_BB;
        while_false_BB = temp_while_false_BB;
        return nullptr;
    }
    if (node->stmttype == BREAKSTMT) {
        auto temp = new BranchInst(while_false_BB, BB);
        is_br = true;
        return nullptr;
    }
    if (node->stmttype == CONTSTMT) {
        auto temp = new BranchInst(while_cond_BB, BB);
        is_br = true;
        return nullptr;
    }
    if (node->stmttype == RETURNSTMT) {
        if (node->exp == nullptr) {
            auto temp = new BranchInst(return_BB, BB);
            is_br = true;
            return nullptr;
        }else{
            Base* exp = this->visit(static_cast<ExpNode*>(node->exp), false);
            if (exp->type == intType32 && FUNC->get_retype() == floatType) {
                auto temp = new CastInst(SItoFP, exp, floatType, BB);
                auto temp_store = new StoreInst(temp, return_var, BB);
            }
            else if (exp->type == floatType && FUNC->get_retype() == intType32) {
                auto temp = new CastInst(FPtoSI, exp, intType32, BB);
                auto temp_store = new StoreInst(temp, return_var, BB);
            }else{
                auto temp = new StoreInst(exp, return_var, BB);
            }
            is_br = true;
            return new BranchInst(return_BB, BB);
        }
    }
    return nullptr;
}

Base* NodeVisit::visit(CondNode* node){
    return this->visit(static_cast<LOrExpNode*>(node->lorexp));
}

Base* NodeVisit::visit(LOrExpNode* node){
    if (node->lorexp == nullptr) {
        return this->visit(static_cast<LAndExpNode*>(node->landexp));
    }
    BasicBlock* temp_false_BB = false_BB;
    false_BB = new BasicBlock(module, "", FUNC);

    Base* temp_value = this->visit(static_cast<LOrExpNode*>(node->lorexp));
    if (temp_value->type == intType32) {
        temp_value = new ICmpInst(INE, temp_value, new ConstNumber(intType32, 0, true), BB);
    }
    else if (temp_value->type == floatType) {
        temp_value = new FCmpInst(FUNE, temp_value, new ConstNumber(floatType, 0, false), BB);
    }
    auto temp = new BranchInst(temp_value, true_BB, false_BB, BB);
    BB = false_BB;
    is_br = false;
    false_BB = temp_false_BB;
    return this->visit(static_cast<LAndExpNode*>(node->landexp));
}

Base* NodeVisit::visit(LAndExpNode* node){
    if (node->landexp == nullptr) {
        return this->visit(static_cast<EqExpNode*>(node->eqexp));
    }
    BasicBlock* temp_true_BB = true_BB;
    true_BB = new BasicBlock(module, "", FUNC);

    Base* temp_value = this->visit(static_cast<LAndExpNode*>(node->landexp));
    if (temp_value->type == intType32) {
        temp_value = new ICmpInst(INE, temp_value, new ConstNumber(intType32, 0, true), BB);
    }
    else if (temp_value->type == floatType) {
        temp_value = new FCmpInst(FUNE, temp_value, new ConstNumber(floatType, 0, false), BB);
    }
    auto temp = new BranchInst(temp_value, true_BB, false_BB, BB);
    BB = true_BB;
    is_br = false;
    true_BB = temp_true_BB;
    return this->visit(static_cast<EqExpNode*>(node->eqexp));
}

Base* NodeVisit::visit(EqExpNode* node){
    if (node->eqexp == nullptr) {
        return this->visit(static_cast<RelExpNode*>(node->relexp));
    }
    Base* x1 = this->visit(static_cast<EqExpNode*>(node->eqexp));
    Base* x2 = this->visit(static_cast<RelExpNode*>(node->relexp));
    bool judge = change_var_type(x1, x2, BB);
    int choose = judge ? (node->optype == EQOP ? IEQ : INE) : (node->optype == EQOP ? FUEQ : FUNE);
    if (judge == true) {
        return new ICmpInst(choose, x1, x2, BB);
    }else{
        return new FCmpInst(choose, x1, x2, BB);
    }
}

Base* NodeVisit::visit(RelExpNode* node){
    if (node->relexp == nullptr) {
        return this->visit(static_cast<AddExpNode*>(node->addexp), false);
    }

    Base* x1 = this->visit(static_cast<RelExpNode*>(node->relexp));
    Base* x2 = this->visit(static_cast<AddExpNode*>(node->addexp), false);
    bool judge = change_var_type(x1, x2, BB);
    int choose = judge ? (node->optype == GTOP ? ISGT : (node->optype == GEOP ? ISGE : (node->optype == LTOP ? ISLT : ISLE))) : (node->optype == GTOP ? FUGT : (node->optype == GEOP ? FUGE : (node->optype == LTOP ? FULT : FULE)));
    if (judge == true) {
        return new ICmpInst(choose, x1, x2, BB);
    }
    else {
        return new FCmpInst(choose, x1, x2, BB);
    }
}

void change_del_type(Type* type, Base* &value, BasicBlock* BB) {
    if (type->type_id != value->type->type_id) {
        if (type->type_id == INTTYPE) {
            if (dynamic_cast<ConstNumber*>(value)) {
                value = new ConstNumber(intType32, dynamic_cast<ConstNumber*>(value)->value, true);
            }
            else {
                value = new CastInst(FPtoSI, value, intType32, BB);
            }
        }
        else if (type->type_id == FLOATTYPE) {
            if (dynamic_cast<ConstNumber*>(value)) {
                value = new ConstNumber(floatType, dynamic_cast<ConstNumber*>(value)->value, false);
            }
            else {
                value = new CastInst(FPtoSI, value, intType32, BB);
            }
        }
    }
}

bool change_var_type(Base* first_value, Base* second_value, BasicBlock* bb) {
    if (first_value->type == intType1) {
        first_value = new CastInst(ZExt, first_value, intType32, bb);
    }
    if (second_value->type == intType1) {
        second_value = new CastInst(ZExt, second_value, intType32, bb);
    }
    if (first_value->type == intType32 && second_value->type == floatType) {
        first_value = new CastInst(SItoFP, first_value, floatType, bb);
    }
    if (first_value->type == floatType && second_value->type == intType32) {
        second_value = new CastInst(SItoFP, second_value, floatType, bb);
    }
    if (first_value->type == intType32) {
        return true;
    }
    return false;
}

ConstArray* array_init(Type* type, NodeVisit* nodevisit, vector<int>& indexs, vector<ArrayType*>& arrType, vector<ConstInitValNode*>& arrays, int now_index) {
    int size_indexs = indexs.size();
    vector<int> index_element_count(size_indexs);
    vector<Const*> elements;
    int size_val = arrays.size();
    for (int i = 0; i < size_val; i++) {
        int before_index;
        if (arrays[i]->constexp != nullptr) {
            auto temp = nodevisit->visit(static_cast<ConstExpNode*>(arrays[i]->constexp));
            change_del_type(type, temp, BB);
            before_index = size_indexs - 1;
            elements.push_back((ConstNumber*)temp);
        }else {
            int next_indexs = now_index + 1;
            for (int i = index_element_count.size() - 1; i > now_index; i--) {
                if (index_element_count[i] != 0) {
                    next_indexs = i + 1;
                }
            }
            before_index = next_indexs - 1;
            vector<ConstInitValNode*> next_arrays;
            if (arrays[i]->constinitvals != nullptr) {
                nodevisit->visit(static_cast<ConstInitValsNode*>(arrays[i]->constinitvals), next_arrays);
            }
            if (next_arrays.empty()) {
                elements.push_back(new ConstZero(arrType[next_indexs]));
            }
            else {
                auto temp = array_init(type, nodevisit, indexs, arrType, next_arrays, next_indexs);
                elements.push_back(temp);
            }
        }
        index_element_count[before_index]++;
        merge_before(indexs, arrType, elements, index_element_count, now_index, before_index);
    }
    merge_final(type, indexs, arrType, elements, index_element_count, now_index);
    return static_cast<ConstArray*>(elements[0]);
}

void merge_before(vector<int>& indexs, vector<ArrayType*>& arrType, vector<Const*>& elements, vector<int>& index_element_count, int now_index, int before_index) {
    for (int i = before_index; i > now_index; i--) {
        if (index_element_count[i] == indexs[i]) {
            vector<Const*> temp;
            temp.assign(elements.end() - indexs[i], elements.end());
            elements.erase(elements.end() - indexs[i], elements.end());
            elements.push_back(new ConstArray(arrType[i], temp));
            index_element_count[i] = 0;
            index_element_count[i - 1]++;
        }
        else {
            break;
        }
    }
}

void merge_final(Type* type, vector<int>& indexs, vector<ArrayType*>& arrType, vector<Const*>& elements, vector<int>& index_element_count, int now_index) {
    int size_ = indexs.size();
    for (int i = size_ - 1; i >= now_index; i--) {
        while (index_element_count[i] < indexs[i] && index_element_count[i] != 0) {
            if (i == size_ - 1) {
                if (type == intType32) {
                    elements.push_back(new ConstNumber(intType32, 0, true));
                }
                else {
                    elements.push_back(new ConstNumber(floatType, 0, false));
                }
            }
            else {
                elements.push_back(new ConstZero(arrType[i + 1]));
            }
            index_element_count[i]++;
        }
        if (index_element_count[i] != 0) {
            vector<Const*> temp;
            temp.assign(elements.end() - indexs[i], elements.end());
            elements.erase(elements.end() - indexs[i], elements.end());
            elements.push_back(new ConstArray(arrType[i], temp));
            index_element_count[i] = 0;
            if (i != now_index) index_element_count[i - 1]++;
        }
    }
}

void block_array_init(Type* type, NodeVisit* nodevisit, Base* p, vector<ConstInitValNode*>& arrays, vector<int>& index_mem, int now_index) {
    int size_ = arrays.size();
    int num = 0;
    Base* temp = p;
    for (int i = 0; i < size_; i++) {
        if (arrays[i]->constexp != nullptr) {
            if (num != 0) {
                temp = new GetElementPtrInst(p, { new ConstNumber(intType32, num, true) }, BB);
            }
            num++;
            auto value = nodevisit->visit(static_cast<ConstExpNode*>(arrays[i]->constexp));
            change_del_type(type, value, BB);
            auto store_instr = new StoreInst(value, temp, BB);
        }
        else {
            int next_indexs = 0;
            for (int i = now_index; i < index_mem.size(); i++) {
                if (num % index_mem[i] == 0) {
                    next_indexs = i;
                    break;
                }
            }
            vector<ConstInitValNode*> next_arrays;
            if (arrays[i]->constinitvals != nullptr) {
                nodevisit->visit(static_cast<ConstInitValsNode*>(arrays[i]->constinitvals), next_arrays);
            }
            if (next_arrays.empty() == false) {
                if (num != 0) {
                    temp = new GetElementPtrInst(p, { new ConstNumber(intType32, num, true) }, BB);
                }
                block_array_init(type, nodevisit, temp, next_arrays, index_mem, next_indexs);
            }
            num = num + index_mem[next_indexs];
        }
    }
}

ConstArray* array_var_init(Type* type, NodeVisit* nodevisit, vector<int>& indexs, vector<ArrayType*>& arrType, vector<InitValNode*>& arrays, int now_index) {
    int size_indexs = indexs.size();
    vector<int> index_element_count(size_indexs);
    vector<Const*> elements;
    int size_val = arrays.size();
    for (int i = 0; i < size_val; i++) {
        int before_index;
        if (arrays[i]->exp != nullptr) {
            auto temp = nodevisit->visit(static_cast<ExpNode*>(arrays[i]->exp), true);
            change_del_type(type, temp, BB);
            before_index = size_indexs - 1;
            elements.push_back((ConstNumber*)temp);
        }
        else {
            int next_indexs = now_index + 1;
            for (int i = index_element_count.size() - 1; i > now_index; i--) {
                if (index_element_count[i] != 0) {
                    next_indexs = i + 1;
                }
            }
            before_index = next_indexs - 1;
            vector<InitValNode*> next_arrays;
            if (arrays[i]->initvals != nullptr) {
                nodevisit->visit(static_cast<InitValsNode*>(arrays[i]->initvals), next_arrays);
            }
            if (next_arrays.empty()) {
                elements.push_back(new ConstZero(arrType[next_indexs]));
            }
            else {
                auto temp = array_var_init(type, nodevisit, indexs, arrType, next_arrays, next_indexs);
                elements.push_back(temp);
            }
        }
        index_element_count[before_index]++;
        merge_before(indexs, arrType, elements, index_element_count, now_index, before_index);
    }
    merge_final(type, indexs, arrType, elements, index_element_count, now_index);
    return static_cast<ConstArray*>(elements[0]);
}

void block_array_var_init(Type* type, NodeVisit* nodevisit, Base* p, vector<InitValNode*>& arrays, vector<int>& index_mem, int now_index) {
    int size_ = arrays.size();
    int num = 0;
    Base* temp = p;
    for (int i = 0; i < size_; i++) {
        if (arrays[i]->exp != nullptr) {
            if (num != 0) {
                temp = new GetElementPtrInst(p, { new ConstNumber(intType32, num, true) }, BB);
            }
            num++;
            auto value = nodevisit->visit(static_cast<ExpNode*>(arrays[i]->exp), true);
            change_del_type(type, value, BB);
            auto store_instr = new StoreInst(value, temp, BB);
        }
        else {
            int next_indexs = 0;
            for (int i = now_index; i < index_mem.size(); i++) {
                if (num % index_mem[i] == 0) {
                    next_indexs = i;
                    break;
                }
            }
            vector<InitValNode*> next_arrays;
            if (arrays[i]->initvals != nullptr) {
                nodevisit->visit(static_cast<InitValsNode*>(arrays[i]->initvals), next_arrays);
            }
            if (next_arrays.empty() == false) {
                if (num != 0) {
                    temp = new GetElementPtrInst(p, { new ConstNumber(intType32, num, true) }, BB);
                }
                block_array_var_init(type, nodevisit, temp, next_arrays, index_mem, next_indexs);
            }
            num = num + index_mem[next_indexs];
        }
    }
}
