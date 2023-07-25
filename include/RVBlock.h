#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Ir.h"

using namespace std;

extern unordered_map<BasicBlock*,RVBlock*> IRB2RVB;
extern unordered_map<RVBlock*,BasicBlock*> RVB2IRB;
extern int now_reg;