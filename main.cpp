#include <fstream>
#include <iostream>
#include "NodeVisit.h"
#include "generator.h"

extern Node* root;
extern int yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {
    char* filename;
    char* destfilename;
    filename = argv[4];
    destfilename =argv[3];
    yyin = fopen(filename, "r");
    if (yyin == nullptr) {
        std::cout << "yyin open" << filename << "failed" << std::endl;
        return -1;
    }
    yyparse();

    NodeVisit * nodevisit = new NodeVisit();
    nodevisit->visit(static_cast<RootNode*>(root));
    Module* m = nodevisit->getModule();
    //cout<<m->print();
     std::string write_file_name1 = "test.ll";
     ofstream os1;    
    os1.open(write_file_name1, ios::out);
     os1<<m->print();  
     os1.close();

    //Generator* generator = new Generator(m);
    //generator->GenerateRisc_V();
   // generator->print();
   // std::string IR = m->print();
    Generator* generator = new Generator(m);
    generator->GenerateRisc_V();
    std::string write_file_name = destfilename;
    ofstream os;    
    os.open(write_file_name, ios::out);
    os<<generator->print();
    os.close();
    return 0;
}
