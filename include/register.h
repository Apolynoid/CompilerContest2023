// #pragma once
#ifndef REGISTER_H
#define REGISTER_H
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;
struct RVFunction;
const int MAX_REG_FOR_FUNC_ARGU = 8;
const int REG_ARGU[MAX_REG_FOR_FUNC_ARGU] = {10, 11, 12, 13, 14, 15, 16, 17};
enum Register:int{
    zero = 0, ra, sp, gp, tp, t0, t1, t2, s0, s1, a0, a1, a2, a3, a4, a5, a6, a7, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, t3, t4, t5, t6
};
//unordered_map<string,int> IRV2RVReg;
//int GetRegFromIRV(string IRV) {
//    if(IRV2RVReg.find(IRV) == IRV2RVReg.end()) {
//        IRV2RVReg[IRV] = ++ now_reg;
//    }
//    return IRV2RVReg[IRV];
//}
class RegisterAllocator {
private:
    RVFunction* func;
    int now_treg = 0;
    unordered_map<string,Register> IRV2Reg;
    unordered_map<Register,string> Reg2IRV;
public:
    RegisterAllocator(RVFunction* func);
    Register GetRegFromIRV(string IRV);
    void FreeReg(Register reg);
    Register AllocateReg();
};
#endif