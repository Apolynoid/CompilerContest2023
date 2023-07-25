#include "generator.h"
#include "enums.h"
#include<iostream>
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
        targetCode.push_back("");
        targetCode.push_back(".global "+func->name);
        targetCode.push_back(".type "+func->name+", @function");
        targetCode.push_back(func->name+":");
        for(auto basic_block: func->basic_blocks) {
            
        }
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