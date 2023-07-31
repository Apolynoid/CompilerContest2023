nodeNames = ["Root", "CompUnit", "Decl", "ConstDecl", "VarDecl", "ConstDefs", "ConstDef", "ConstInitVal", "ConstArrayList", "AddExp", "MulExp", "UnaryExp", "PrimaryExp", "FuncRParams", "Exp", "LVal", "ArrayList", "VarDefs", "VarDef", "InitVal", "InitVals", "FuncFParams", "FuncFParam", "Block", "BlockItems", "BlockItem", "Stmt", "Cond", "FuncDef", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", "ConstInitVals"]

for name in nodeNames:
    file = open(name+"Node.h", "a")
    file.write("# ifndef DEF_"+name.upper()+"_NODE\n# define DEF_"+name.upper()+"_NODE\n\n# include <Node.h>\n\n")
    file.write("class "+name+"Node:Node {\npublic:\n\tvoid generateCode();\n};")
    file.write("\n\n#endif")
    file.close

    file = open(name+"Node.cpp", "a")
    file.write("# include <"+name+"Node.h>\n\n")
    file.write("void "+name+"Node::generateCode()\n{\n\n}")
    file.close

file = open("AllNodes.h", "a")
for name in nodeNames:
    file.write("# include <"+name+"Node.h>")
file.close()