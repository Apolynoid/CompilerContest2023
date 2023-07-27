#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Ir.h"
#include "RVBlock.h"

using namespace std;

unordered_map<BasicBlock*,RVBlock*> IRB2RVB;
unordered_map<RVBlock*,BasicBlock*> RVB2IRB;
