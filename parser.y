%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>

    #include "AllNodes.h"

    Node* root;

    extern FILE *yyin;
    extern int line_cnt;
    extern int yylineno;
    extern char *yytext;
    extern int yylex();
    extern int yyparse();
    //extern void yyerror(char *msg);
    void yyerror(const char* fmt, ...);
    int syntax_error = 0;
    char filename[100];
%}

%union {
    int int_val;
    float float_val;
    char* str_val;
    Node* node_val;
}

%type <node_val> Root CompUnit Decl ConstDecl VarDecl ConstDefs ConstDef ConstInitVal ConstArrayList ConstExp AddExp MulExp UnaryExp PrimaryExp 
%type <node_val> FuncRParams Exp LVal ArrayList VarDefs VarDef InitVal InitVals FuncFParams FuncFParam Block BlockItems BlockItem Stmt Cond 
%type <node_val> FuncDef LOrExp RelExp EqExp LAndExp ConstInitVals

%token <int_val> CONST COMMA LC RC LB RB AND MINUS MUL DIV MOD LP RP NOT SEMICOLON
%token <int_val> INT FLOAT VOID RETURN IF ELSE WHILE BREAK CONTINUE
%token <int_val> ASSIGN ADD OR EQ NE LT LE GT GE LEX_ERR FOR INC DEC THEN

%token <str_val> ID
%token <int_val> INT_LIT
%token <float_val> FLOAT_LIT

%nonassoc THEN
%nonassoc ELSE

%start Root

%%
Root: CompUnit {root = new RootNode($1);};
CompUnit: Decl {$$ = new CompUnitNode($1, nullptr, nullptr);};
        | FuncDef {$$ = new CompUnitNode(nullptr, $1, nullptr);};
        | Decl CompUnit {$$ = new CompUnitNode($1, nullptr, $2);};
        | FuncDef CompUnit {$$ = new CompUnitNode(nullptr, $1, $2);};
Decl: ConstDecl {$$ = new DeclNode($1, nullptr);};
    | VarDecl {$$ = new DeclNode(nullptr, $1);};
ConstDecl   : CONST INT ConstDefs SEMICOLON {$$ = new ConstDeclNode($3, INTTYPE);};
            | CONST FLOAT ConstDefs SEMICOLON {$$ = new ConstDeclNode($3, FLOATTYPE);};
ConstDefs   : ConstDef {$$ = new ConstDefsNode($1, nullptr);};
            | ConstDef COMMA ConstDefs {$$ = new ConstDefsNode($1, $3);};
ConstDef: ID ASSIGN ConstInitVal {$$ = new ConstDefNode($1, nullptr, $3);};
        | ID ConstArrayList ASSIGN ConstInitVal {$$ = new ConstDefNode($1, $2, $4);};
ConstInitVal: ConstExp {$$ = new ConstInitValNode($1, nullptr);};
            | LC RC {$$ = new ConstInitValNode(nullptr, nullptr);};
            | LC ConstInitVals RC {$$ = new ConstInitValNode(nullptr, $2);};
ConstInitVals   : ConstInitVal {$$ = new ConstInitValsNode($1, nullptr);};
                | ConstInitVal COMMA ConstInitVals {$$ = new ConstInitValsNode($1, $3);};
ConstArrayList  : LB ConstExp RB {$$ = new ConstArrayListNode($2, nullptr);};
                | LB ConstExp RB ConstArrayList {$$ = new ConstArrayListNode($2, $4);};
ConstExp: AddExp {$$ = new ConstExpNode($1);};
AddExp  : MulExp {$$ = new AddExpNode(nullptr, NULLOP, $1);};
        | AddExp ADD MulExp {$$ = new AddExpNode($1, ADDOP, $3);};
        | AddExp MINUS MulExp {$$ = new AddExpNode($1, MINUSOP, $3);};
MulExp  : UnaryExp {$$ = new MulExpNode(nullptr, NULLOP, $1);};
        | MulExp MUL UnaryExp {$$ = new MulExpNode($1, MULOP, $3);};
        | MulExp DIV UnaryExp {$$ = new MulExpNode($1, DIVOP, $3);};
        | MulExp MOD UnaryExp {$$ = new MulExpNode($1, MODOP, $3);};
UnaryExp: PrimaryExp {$$ = new UnaryExpNode($1, "", nullptr, NULLOP, nullptr);};
        | ID LP RP {$$ = new UnaryExpNode(nullptr, $1, nullptr, NULLOP, nullptr);};
        | ID LP FuncRParams RP {$$ = new UnaryExpNode(nullptr, $1, $3, NULLOP, nullptr);};
        | ADD UnaryExp {$$ = new UnaryExpNode(nullptr, "", nullptr, ADDOP, $2);};
        | MINUS UnaryExp {$$ = new UnaryExpNode(nullptr, "", nullptr, MINUSOP, $2);};
        | NOT UnaryExp {$$ = new UnaryExpNode(nullptr, "", nullptr, NOTOP, $2);};
PrimaryExp  : LP Exp RP {$$ = new PrimaryExpNode($2, nullptr, 0, 0.0, VOIDTYPE);};
            | LVal {$$ = new PrimaryExpNode(nullptr, $1, 0, 0.0, VOIDTYPE);};
            | INT_LIT {$$ = new PrimaryExpNode(nullptr, nullptr, $1, 0.0, INTTYPE);};
            | FLOAT_LIT {$$ = new PrimaryExpNode(nullptr, nullptr, 0, $1, FLOATTYPE);};
FuncRParams : Exp {$$ = new FuncRParamsNode($1, nullptr);};
            | Exp COMMA FuncRParams {$$ = new FuncRParamsNode($1, $3);};
Exp : AddExp {$$ = new ExpNode($1);};
LVal: ID {$$ = new LValNode($1, nullptr);};
    | ID ArrayList {$$ = new LValNode($1, $2);};
ArrayList   : LB Exp RB {$$ = new ArrayListNode($2, nullptr);};
            | LB Exp RB ArrayList {$$ = new ArrayListNode($2, $4);};
VarDecl : INT VarDefs SEMICOLON {$$ = new VarDeclNode($2, INTTYPE);};
        | FLOAT VarDefs SEMICOLON {$$ = new VarDeclNode($2, FLOATTYPE);};
VarDefs : VarDef {$$ = new VarDefsNode($1, nullptr);};
        | VarDef COMMA VarDefs {$$ = new VarDefsNode($1, $3);};
VarDef  : ID {$$ = new VarDefNode($1, nullptr, nullptr);};
        | ID ConstArrayList {$$ = new VarDefNode($1, $2, nullptr);};
        | ID ASSIGN InitVal {$$ = new VarDefNode($1, nullptr, $3);};
        | ID ConstArrayList ASSIGN InitVal {$$ = new VarDefNode($1, $2, $4);};
InitVal : Exp {$$ = new InitValNode($1, nullptr);};
        | LC RC {$$ = new InitValNode(nullptr, nullptr);}
        | LC InitVals RC {$$ = new InitValNode(nullptr, $2);};
InitVals: InitVal {$$ = new InitValsNode($1, nullptr);};
        | InitVal COMMA InitVals {$$ = new InitValsNode($1, $3);};
FuncDef : VOID ID LP RP Block {$$ = new FuncDefNode(VOIDTYPE, $2, nullptr, $5);};
        | INT ID LP RP Block {$$ = new FuncDefNode(INTTYPE, $2, nullptr, $5);};
        | FLOAT ID LP RP Block {$$ = new FuncDefNode(FLOATTYPE, $2, nullptr, $5);};
        | VOID ID LP FuncFParams RP Block {$$ = new FuncDefNode(VOIDTYPE, $2, $4, $6);};
        | INT ID LP FuncFParams RP Block {$$ = new FuncDefNode(INTTYPE, $2, $4, $6);};
        | FLOAT ID LP FuncFParams RP Block {$$ = new FuncDefNode(FLOATTYPE, $2, $4, $6);};
FuncFParams : FuncFParam {$$ = new FuncFParamsNode($1, nullptr);};
            | FuncFParam COMMA FuncFParams {$$ = new FuncFParamsNode($1, $3);};
FuncFParam  : INT ID {$$ = new FuncFParamNode(INTTYPE, $2, nullptr, false);};
            | FLOAT ID {$$ = new FuncFParamNode(FLOATTYPE, $2, nullptr, false);};
            | INT ID LB RB {$$ = new FuncFParamNode(INTTYPE, $2, nullptr, true);};
            | FLOAT ID LB RB {$$ = new FuncFParamNode(FLOATTYPE, $2, nullptr, true);};
            | INT ID LB RB ArrayList {$$ = new FuncFParamNode(INTTYPE, $2, $5, true);};
            | FLOAT ID LB RB ArrayList {$$ = new FuncFParamNode(FLOATTYPE, $2, $5, true);};
Block   : LC RC {$$ = new BlockNode(nullptr);};
        | LC BlockItems RC {$$ = new BlockNode($2);};
BlockItems  : BlockItem {$$ = new BlockItemsNode($1, nullptr);};
            | BlockItem BlockItems {$$ = new BlockItemsNode($1, $2);};
BlockItem   : Decl {$$ = new BlockItemNode($1, nullptr);};
            | Stmt {$$ = new BlockItemNode(nullptr, $1);};
Stmt: LVal ASSIGN Exp SEMICOLON {$$ = new StmtNode($1, $3, nullptr, nullptr, nullptr, nullptr, ASSIGNSTMT);};
    | SEMICOLON {$$ = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, NULLSTMT);};
    | Exp SEMICOLON{$$ = new StmtNode(nullptr, $1, nullptr, nullptr, nullptr, nullptr, EXPSTMT);};
    | Block {$$ = new StmtNode(nullptr, nullptr, $1, nullptr, nullptr, nullptr, BLOCKSTMT);};
    | IF LP Cond RP Stmt %prec THEN {$$ = new StmtNode(nullptr, nullptr, nullptr, $3, $5, nullptr, IFSTMT);};
    | IF LP Cond RP Stmt ELSE Stmt {$$ = new StmtNode(nullptr, nullptr, nullptr, $3, $5, $7, IFSTMT);};
    | WHILE LP Cond RP Stmt {$$ = new StmtNode(nullptr, nullptr, nullptr, $3, $5, nullptr, WHILESTMT);};
    | BREAK SEMICOLON {$$ = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, BREAKSTMT);};
    | CONTINUE SEMICOLON {$$ = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, CONTSTMT);};
    | RETURN SEMICOLON {$$ = new StmtNode(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, RETURNSTMT);};
    | RETURN Exp SEMICOLON {$$ = new StmtNode(nullptr, $2, nullptr, nullptr, nullptr, nullptr, RETURNSTMT);};
Cond: LOrExp {$$ = new CondNode($1);};
LOrExp  : LAndExp {$$ = new LOrExpNode(nullptr, $1);};
        | LOrExp OR LAndExp {$$ = new LOrExpNode($1, $3);};
LAndExp : EqExp {$$ = new LAndExpNode(nullptr, $1);};
        | LAndExp AND EqExp {$$ = new LAndExpNode($1, $3);};
EqExp   : RelExp {$$ = new EqExpNode(nullptr, NULLOP, $1);};
        | EqExp EQ RelExp {$$ = new EqExpNode($1, EQOP, $3);};
        | EqExp NE RelExp {$$ = new EqExpNode($1, NEOP, $3);};
RelExp  : AddExp {$$ = new RelExpNode(nullptr, NULLOP, $1);};
        | RelExp GT AddExp {$$ = new RelExpNode($1, GTOP, $3);};
        | RelExp GE AddExp {$$ = new RelExpNode($1, GEOP, $3);};
        | RelExp LT AddExp {$$ = new RelExpNode($1, LTOP, $3);};
        | RelExp LE AddExp {$$ = new RelExpNode($1, LEOP, $3);};

%%

/*
int main(int argc, char *argv[]) {
    int index = strlen(argv[1]) - 1;
    while(index > 0 && argv[1][index - 1] != '/')
        index--;
    strcpy(filename, argv[1] + index);
    freopen(argv[1], "r", stdin);
    yyparse();
    if (syntax_error == 0) 
        printf("finish\n");
        root->show(0);
    return 0;
}
*/

/*
void yyerror(char *msg) {
    printf("%s:%d\n", name, yylineno);
    printf("error text: %s\n", yytext);
    exit(-1);
}
*/
#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    syntax_error = 1;    
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s:%d ", filename, yylineno);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}