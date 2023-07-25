#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;
const int MAX_REG_FOR_FUNC_ARGU = 8;
const int REG_ARGU[MAX_REG_FOR_FUNC_ARGU] = {10, 11, 12, 13, 14, 15, 16, 17};
int now_reg = 0;
enum Register:int{
    zero = 0, ra, sp, gp, tp, t0, t1, t2, s0, s1, a0, a1, a2, a3, a4, a5, a6, a7, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, t3, t4, t5, t6
};
unordered_map<string,int> IRV2RVReg;
int GetRegFromIRV(string IRV) {
    if(IRV2RVReg.find(IRV) == IRV2RVReg.end()) {
        IRV2RVReg[IRV] = ++ now_reg;
    }
    return IRV2RVReg[IRV];
}
class RegisterAllocator {
    unordered_map<int, unordered_set<int>> interference_graph;
    unordered_map<int, int> color_map;
    unordered_set<int> spilledVars;
    int num_regs;
public:
    RegisterAllocator(int num_regs);

};