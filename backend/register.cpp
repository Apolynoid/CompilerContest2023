#include "register.h"
RegisterAllocator::RegisterAllocator(RVFunction* func){
    this->func = func;
    this->now_treg = 0;
}
Register RegisterAllocator::AllocateReg(){
    for(int i = 0; i < 16 ;i++){
        AllocRegister temp = (AllocRegister)(i);
        Register reg = Alloc2reg(temp);
        if(Reg2IRV.find(reg) == Reg2IRV.end()){
            return reg;
        }
    }
}
Register RegisterAllocator::GetRegForFuncArgu(int i){
    return (Register)REG_ARGU[i];
}
Register RegisterAllocator::GetImmReg(){
    return Register::t6;
}
Register RegisterAllocator::GetRegFromIRV(string IRV) {
    if(IRV2Reg.find(IRV) == IRV2Reg.end()) {
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
Register Alloc2reg(AllocRegister temp){
    switch(temp){
        case T0: return Register::t0;
        case T1: return Register::t1;
        case T2: return Register::t2;
        case T3: return Register::t3;
        case S0: return Register::s0;
        case S1: return Register::s1;
        case S2: return Register::s2;
        case S3: return Register::s3;
        case S4: return Register::s4;
        case S5: return Register::s5;
        case S6: return Register::s6;
        case S7: return Register::s7;
        case S8: return Register::s8;
        case S9: return Register::s9;
        case S10: return Register::s10;
        case S11: return Register::s11;
        default: return Register::zero;
    }
}