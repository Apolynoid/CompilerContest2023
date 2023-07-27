#include "register.h"
RegisterAllocator::RegisterAllocator(RVFunction* func){
    this->func = func;
    this->now_treg = 5;
}
Register RegisterAllocator::AllocateReg(){
    switch(now_treg){
        case 5:
        case 6:
        case 28:
        case 29:
        case 30:
            return Register(now_treg++);
        case 7:{
            now_treg=28;
            return Register(7);
        }
        case 31:{
            now_treg=5;
            return Register(31);
        }
    }
}

Register RegisterAllocator::GetRegFromIRV(string IRV) {
    if(IRV2Reg.find(IRV) == IRV2RVReg.end()) {
        IRV2Reg[IRV] = this->AllocateReg();
        Reg2IRV[IRV2Reg[IRV]] = IRV;
    }
    return IRV2Reg[IRV];
}

void RegisterAllocator::FreeReg(Register reg) {
    if(Reg2IRV.find(reg) != Reg2IRV.end()) {
        IRV2Reg.erase(Reg2IRV[reg]);
        Reg2IRV.erase(reg);
    }
}
