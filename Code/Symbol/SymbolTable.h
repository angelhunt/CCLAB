/*************************************************************************
	> File Name: SymbolTable.h
	> Author: 
	> Mail: 
	> Created Time: 2015年11月03日 星期二 19时02分41秒
 ************************************************************************/

#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include "list.h"
#include "type.h"
#include "Symbol.h"
#include "ScopeStack.h"
extern const unsigned HASH_TABLE_SIZE;
enum STTYPE{ STRUCTST, PARAMST, COMST };
typedef enum STTYPE STTYPE;

struct SymbolTable_
{
    STTYPE type;
    Symbol* slist;
    ScopeStack ss;
};
typedef struct SymbolTable_* SymbolTable;


extern SymbolTable NewSymbolTable(STTYPE type);
extern  void SymboltableInit(SymbolTable st);
extern  bool TableInsertSymbol(SymbolTable table, Symbol s);
extern  void SymbolTablePrint(SymbolTable table);
extern unsigned  HashPjw(char *name);
#endif
