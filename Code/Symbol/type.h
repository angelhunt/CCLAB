/*************************************************************************
	> File Name: type.h
	> Author: 
	> Mail: 
	> Created Time: 2015年10月17日 星期六 15时33分38秒
 ************************************************************************/
#ifndef _TYPE_H
#define _TYPE_H
#include "common.h"
#include "ScopeStack.h"
#include "../syntax.tab.h"
//#include "Symbol.h"
struct SymbolTable_;
struct Symbol_;
extern int getSymbolSize(struct Symbol_* s);
extern struct Symbol_* SSLEntry(ListHead *ptr);
enum KIND{ BASIC, ARRAY, STRUCTURE, FUNC, STRUCTTYPE, NONE, FUNCAFF};
typedef enum KIND KIND;
typedef struct Type_* Type;
typedef struct StructureType_* StructureType;
typedef struct ArrayType_* ArrayType;
typedef struct FuncType_* FuncType;
typedef union TypeValue_* TypeValue;
struct ArrayType_
{
    Type elem;
    int size;
};

struct StructureType_
{
    char *name;
    Scope scope;
    struct SymbolTable_* st;
};

struct FuncType_
{
    char *name;

    Scope scope;
    struct SymbolTable_* st;
    int paramternum;
    Type returntype;
    char *funstr;
};


union TypeValue_
{
    int basic;
    ArrayType array;
    StructureType structure;
    FuncType func;
};
struct Type_
{
    KIND tn;
    TypeValue tv;
    int width;
    bool ispointer;
};









extern Type NewType(KIND tn, TypeValue tv);
extern TypeValue NewTypeValue();
extern StructureType NewStructureType();
extern FuncType NewFuncType(Type returntype);
extern ArrayType NewArrayType(Type elem, int size);
extern bool ArgForward(FuncType func);
#endif
