/*************************************************************************
	> File Name: SymbolTable.h
	> Author: 
	> Mail: 
	> Created Time: 2015年10月26日 星期一 21时18分11秒
 ************************************************************************/

#ifndef _STStack_H
#define _STStack_H
#include "common.h"
#include "SymbolTable.h"
struct STStack_
{
    SymbolTable *sts;
    int stacktop;
    unsigned stacksize;
};
typedef struct STStack_* STStack;



extern STStack NewSTStack();
extern bool ST_Push(STStack stack, SymbolTable SymbolTable);
extern SymbolTable ST_Pop(STStack stack);
extern SymbolTable ST_GetTop(STStack stack);
extern Symbol LookUpSymbol(STStack stack, Symbol s);

#endif
