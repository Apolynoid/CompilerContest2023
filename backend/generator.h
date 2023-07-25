#include "Ir.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "register.h"
#include "RVBlock.hpp"
#include "function.hpp"
using namespace std;

class Generator {
private:
    Module *module;
    vector<unique_ptr<RVFunction>> functions;
    vector<string> targetCode;
    unordered_map<string,CMP_Context> cmp_context;
    int num_block;
    void GenerateFunctionCode();
    void GenerateGlobalVarCode();
    void GenerateArrayCode(ConstArray* array);
public:
    Generator(Module *module): module(module) {};
    void GenerateRisc_V();
    void print();
    friend class RVFunction;
};
