#include <fstream>
#include <iostream>
#include "NodeVisit.h"
//#include "backend/generator.h"

extern Node* root;
extern int yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {
    char* filename;
    bool print_ir = false;
    if (argc == 2) {
        filename = argv[1];
    }
    else if (argc == 3) {
        print_ir = true;
        filename = argv[2];
    }
    yyin = fopen(filename, "r");
    if (yyin == nullptr) {
        std::cout << "yyin open" << filename << "failed" << std::endl;
        return -1;
    }
    yyparse();

    NodeVisit * nodevisit = new NodeVisit();
    nodevisit->visit(static_cast<RootNode*>(root));
    Module* m = nodevisit->getModule();
    //Generator* generator = new Generator(m);
    //generator->GenerateRisc_V();
   // generator->print();
   std::string IR = m->print();
    if (print_ir) {
       std::cout << IR << std::endl;
       std::string IRtest="test.ll";
       std::ofstream os;
       os.open(IRtest,std::ios::trunc);
        os<<IR;
        os.close();
    }
    return 0;
}
