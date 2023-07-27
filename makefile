.PHONY:main
INCLUDES = -I ./include
SRCS := ./parser.tab.cpp
SRCS += ./nodes/Node.cpp
SRCS += ./nodes/RootNode.cpp
SRCS += ./nodes/CompUnitNode.cpp
SRCS += ./nodes/DeclNode.cpp
SRCS += ./nodes/ConstDeclNode.cpp
SRCS += ./nodes/ConstDefsNode.cpp
SRCS += ./nodes/ConstDefNode.cpp
SRCS += ./nodes/ConstInitValNode.cpp
SRCS += ./nodes/ConstInitValsNode.cpp
SRCS += ./nodes/ConstArrayListNode.cpp
SRCS += ./nodes/ConstExpNode.cpp
SRCS += ./nodes/AddExpNode.cpp
SRCS += ./nodes/MulExpNode.cpp
SRCS += ./nodes/UnaryExpNode.cpp
SRCS += ./nodes/PrimaryExpNode.cpp
SRCS += ./nodes/FuncRParamsNode.cpp
SRCS += ./nodes/ExpNode.cpp
SRCS += ./nodes/LValNode.cpp
SRCS += ./nodes/ArrayListNode.cpp
SRCS += ./nodes/VarDeclNode.cpp
SRCS += ./nodes/VarDefsNode.cpp
SRCS += ./nodes/VarDefNode.cpp
SRCS += ./nodes/InitValNode.cpp
SRCS += ./nodes/InitValsNode.cpp
SRCS += ./nodes/FuncDefNode.cpp
SRCS += ./nodes/FuncFParamsNode.cpp
SRCS += ./nodes/FuncFParamNode.cpp
SRCS += ./nodes/BlockNode.cpp
SRCS += ./nodes/BlockItemsNode.cpp
SRCS += ./nodes/BlockItemNode.cpp
SRCS += ./nodes/StmtNode.cpp
SRCS += ./nodes/CondNode.cpp
SRCS += ./nodes/LOrExpNode.cpp
SRCS += ./nodes/LAndExpNode.cpp
SRCS += ./nodes/EqExpNode.cpp
SRCS += ./nodes/RelExpNode.cpp
SRCS += ./lex.yy.cpp
SRCS += ./ir/Ir.cpp
SRCS += ./ir/Symbol.cpp
SRCS += ./ir/Type.cpp
SRCS += ./ir/NodeVisit.cpp
SRCS += ./backend/generator.cc
SRCS += ./backend/RVBlock.cpp
SRCS += ./backend/instruction.cpp
SRCS += ./backend/register.cpp
SRCS += main.cpp

main:
	g++ -g -o main $(SRCS) $(INCLUDES)
test.s:test.ll
	llc -O0 --march=riscv64 -o test.s test.ll