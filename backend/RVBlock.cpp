#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Ir.h"
#include "RVBlock.hpp"

using namespace std;

unordered_map<BasicBlock*,RVBlock*> IRB2RVB;
unordered_map<RVBlock*,BasicBlock*> RVB2IRB;
int now_reg;
unordered_map<string,int> IRV2RVReg;
int GetRegFromIRV(string IRV) {
    if(IRV2RVReg.find(IRV) == IRV2RVReg.end()) {
        IRV2RVReg[IRV] = ++ now_reg;
    }
    return IRV2RVReg[IRV];
}