# ifndef DEF_ENUMS
# define DEF_ENUMS

# define TAB "    "

# define INTTYPE 0
# define FLOATTYPE 1
# define VOIDTYPE 2
# define LABELTYPE 3
# define FUNCTIONTYPE 4
# define ARRAYTYPE 5
# define POINTTYPE 6

# define NULLOP 0
# define ADDOP 1
# define MINUSOP 2
# define MULOP 3
# define DIVOP 4
# define MODOP 5
# define NOTOP 6
# define EQOP 7
# define NEOP 8
# define GTOP 9
# define GEOP 10
# define LTOP 11
# define LEOP 12

# define NULLSTMT 0
# define ASSIGNSTMT 1
# define EXPSTMT 2
# define BLOCKSTMT 3
# define IFSTMT 4
# define WHILESTMT 5
# define BREAKSTMT 6
# define CONTSTMT 7
# define RETURNSTMT 8


# define Ret 0
# define Br 1

# define FNeg 2

# define Add 3
# define Sub 4
# define Mul 5
# define SDiv 6
# define SRem 7
# define UDiv 8
# define URem 9

# define FAdd 10
# define FSub 11
# define FMul 12
# define FDiv 13

# define Shl 14
# define LShr 15
# define AShr 16
# define And 17
# define Or 18
# define Xor 19

# define Alloca 20
# define Load 21
# define Store 22
# define GetElementPtr 23

# define ZExt 24
# define FPtoSI 25
# define SItoFP 26
# define BitCast 27

# define ICmp 28
# define FCmp 29
# define PHI 30
# define Call 31

#define IEQ 0
#define INE 1
#define ISGT 2
#define ISGE 3
#define ISLT 4
#define ISLE 5

#define FUEQ 6
#define FUNE 7
#define FUGT 8
#define FUGE 9
#define FULT 10
#define FULE 11

# endif