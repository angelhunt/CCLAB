#ifndef _MIDCODE_H
#define _MIDCODE_H
#include <stdio.h>
#include "../Symbol/common.h"
enum VART { VAR = 200, CON = 201, LABEL = 202, TEMP = 203, PLACE = 204, SIZE = 205, ADDR = 206, GetADDR = 207};
typedef enum VART VART;
struct Var_
{
	VART kind;
	union
	{
		int var_no;
		int value;
        char *name;
        VART ttype;
	};
};


typedef struct Var_* Var;


enum MIDCODET { C_LAB = 100, C_FUNC, C_ASSIGN, C_ADD, C_SUB, C_MUL, C_DIV,
                C_GETADDR, C_GETMEM, C_SETMEM, C_GOTO, C_IF, C_RETURN, C_DEC,
               C_ARG, C_CALL, C_PARAM, C_READ, C_WRITE};

typedef enum MIDCODET MIDCODET;
struct MidCode_
{
	MIDCODET kind;
	Var result;
	Var arg1;
	Var arg2;
    char *op;
};


typedef struct MidCode_* MidCode;




#define eletype MidCode
struct CodeSU
{
    eletype ptrtoe;
    int next;
    int last;
    int index;
};
typedef struct CodeSU CodeSU;


typedef struct CodeSU* MCAHead;
struct MCA_
{
    struct CodeSU* array;
    int asize;
    MCAHead alloc;
    MCAHead unalloc;
};

typedef struct MCA_* MCA;


extern Var NewVar(VART kind);
extern MidCode NewMidCode(MIDCODET ct, Var t1, Var t2, Var t3);
extern MCA NewMCA();
extern MCAHead NewMCAHead(MCA a, MidCode code);
extern MCAHead LinkMulMCAHead(MCA a, int num, ...);
extern void printMCA(MCA a, MCAHead h);
extern void changevar(Var v1, Var v2);
#endif
