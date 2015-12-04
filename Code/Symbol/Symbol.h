/*************************************************************************
	> File Name: SymbolTable.h
	> Author: 
	> Mail: 
	> Created Time: 2015年10月18日 星期日 20时13分42秒
 ************************************************************************/

#ifndef _SYMBOL_H
#define _SYMBOL_H
#include "list.h"
#include "type.h"
//structure of data
struct Symbol_
{
    char *name;    //name 
                   //name type
    Type type;     //actual type
    KIND kind;               //
                   //amount of paramter
                   //value 
                   //address in memory
    unsigned lineno;     //depth of scope
    ListHead hashlist;               //hashlist
    ListHead scopelist;               //scopelist
};

typedef struct Symbol_* Symbol;


extern int symbolSize;

extern  Symbol NewSymbol(char *name, Type type, int lineno);
bool SymbolIsEqual(Symbol s1, Symbol s2);
extern char *getFuncStr(FuncType f);
extern bool TypeIsEqual(Type t1, Type t2);
extern void delSymbol(Symbol s);
extern int getSymbolSize(Symbol s);
extern Symbol SSLEntry(ListHead *ptr);
extern Symbol SHLEntry(ListHead *ptr);
#endif
