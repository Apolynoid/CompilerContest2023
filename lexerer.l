%option yylineno
%option noyywrap

%{
    #include<iostream>
    #include<stdio.h>
    #include<fstream>

    # include "AllNodes.h"
    # include "parser.tab.h"   
%}


DIGIT [0-9]
LETTER [A-Za-z]
INT_10         (0|[1-9][0-9]*)
INT_8          0[0-7]*
INT_16         (0x|0X)[0-9a-fA-F]+
FLOAT_10          ([0-9]*\.?[0-9]+|[0-9]+\.)((e|E)[-+]?[0-9]+)?
FLOAT_16       (0x|0X)([0-9a-fA-F]*\.?[0-9a-fA-F]+|[0-9a-fA-F]+\.)((p|P)[-+]?[0-9a-fA-F]+)?
ID               [_a-zA-Z][_a-zA-Z0-9]*

MultilineComment "/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"
SingleLineComment "//".*$
%%

"int" {printf("%s : INT\n", yytext); return INT; }
"float" {printf("%s : FLOAT\n", yytext); return FLOAT; }
"void" {printf("%s : VOID\n", yytext); return VOID; }
"const" {printf("%s : CONST\n", yytext); return CONST; }
"return" {printf("%s : RETURN\n", yytext); ; return RETURN; }
"if" {printf("%s : IF\n", yytext); return IF; }
"else" {printf("%s : ELSE\n", yytext); return ELSE; }

"while" {printf("%s : WHILE\n", yytext); return WHILE; }

"break" {printf("%s : BREAK\n", yytext); return BREAK; }
"continue" {printf("%s : CONTINUE\n", yytext); return CONTINUE; }

"(" {printf("%s : LP\n", yytext); return LP; }
")" {printf("%s : RP\n", yytext); return RP; }
"[" {printf("%s : LB\n", yytext); return LB; }
"]" {printf("%s : RB\n", yytext); return RB; }
"{" {printf("%s : LC\n", yytext); return LC; }
"}" {printf("%s : RC\n", yytext); return RC; }
"," {printf("%s : COMMA\n", yytext); return COMMA; }
";" {printf("%s : SEMICOLON\n", yytext); return SEMICOLON; }
"!" {printf("%s : NOT\n", yytext); return NOT; }
"=" {printf("%s : ASSIGN\n", yytext); return ASSIGN; }
"-" {printf("%s : MINUS\n", yytext); return MINUS; }
"+" {printf("%s : ADD\n", yytext); return ADD; }
"*" {printf("%s : MUL\n", yytext); return MUL; }
"/" {printf("%s : DIV\n", yytext); return DIV; }
"%" {printf("%s : MOD\n", yytext); return MOD; }
"&&" {printf("%s : AND\n", yytext); return AND; }
"||" {printf("%s : OR\n", yytext); return OR; }
"==" {printf("%s : EQ\n", yytext); return EQ; }
"!=" {printf("%s : NE\n", yytext); return NE; }
"<" {printf("%s : LT\n", yytext); return LT; }
"<=" {printf("%s : LE\n", yytext); return LE; }
">" {printf("%s : GT\n", yytext); return GT; }
">=" {printf("%s : GE\n", yytext); return GE; }

{MultilineComment} {}
{SingleLineComment} {}
{INT_10}	    {
                        yylval.int_val=(int)strtol(yytext, (char **)NULL, 10);
                        int x = (int)strtol(yytext, (char **)NULL, 10);
                        //printf("%s:%d\n",yytext,x);
                        return INT_LIT;
                    }
{INT_8}	    {
                        yylval.int_val = (int)strtol(yytext, (char **)NULL, 8);
                        int x = (int)strtol(yytext, (char **)NULL, 8);
                        //printf("%s:%d\n",yytext,x);
                        return INT_LIT;
                    }
{INT_16}	    {
                        yylval.int_val = (int)strtol(yytext, (char **)NULL, 16);
                        int x = (int)strtol(yytext, (char **)NULL, 16);
                        //printf("%s:%d\n",yytext,x);
                        return INT_LIT;
                    }
{FLOAT_10}	    {
                        yylval.float_val = (float)strtof(yytext, (char **)NULL);
                        float x = (float)strtof(yytext, (char **)NULL);
                        //printf("%s:%f\n",yytext,x);
                        return FLOAT_LIT;
                    }
{FLOAT_16}	    {
                        yylval.float_val = (float)strtof(yytext, (char **)NULL);
                        float x = (float)strtof(yytext, (char **)NULL);
                        //printf("%s:%f\n",yytext,x);
                        return FLOAT_LIT;
                    }
{ID}             {
                        yylval.str_val = (char *)malloc(strlen(yytext) + 1);
                        strcpy(yylval.str_val, yytext);
                        yylval.str_val[strlen(yytext)] = '\0';
                        //printf("%s:ID\n",yytext);
                        return ID;
                    }
[ \n] {}
[ \r\t] {}
[ \n\t]+ {}
. {printf("Lexical error - line %d : %s\n",yylineno,yytext);return LEX_ERR;}

%%
/*
int main(int argc, char** argv) {
    
    if(argc > 1) {
        std::filebuf fb ;
        fb.open(argv[1], std::ios::in);
		std::istream in(&fb);
        FlexLexer* lexer = new yyFlexLexer(&in);    
        int symbol; 
        while( symbol = lexer->yylex()) { };
        fb.close();
    
    } else printf("No source file given!\n"); 

    return 0; 

}*/
