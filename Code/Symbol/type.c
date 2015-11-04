/*************************************************************************
	> File Name: type.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月03日 星期二 19时26分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include "type.h"
static int ArrayType_Size = sizeof(struct ArrayType_);
static int StructureType_Size = sizeof(struct StructureType_);
static int FuncType_Size = sizeof(struct FuncType_);
static int TypeValue_Size = sizeof(union TypeValue_);
static int Type_Size = sizeof(struct Type_);



bool ArgForward(FuncType func)
{
    Scope fscope = func->scope;
    ListHead *next = fscope->scopeposition->next;
    if(next == &(fscope->scopelist))
        return false;
    fscope->scopeposition = next;
    return true;
}

 ArrayType NewArrayType(Type elem, int size)
{
    ArrayType t = (ArrayType)malloc(ArrayType_Size);
    memset(t, 0, ArrayType_Size);
    t->elem = elem;
    t->size = size;
    return t;
}



 FuncType NewFuncType(Type returntype)
{
    FuncType t = (FuncType)malloc(FuncType_Size);
    memset(t, 0, FuncType_Size);
    t->paramternum = 0;
    t->returntype = returntype;
    t->funstr = malloc(100);
    memset(t->funstr, 0, 100);
    return t;
}

 StructureType NewStructureType()
{
    StructureType t = (StructureType)malloc(StructureType_Size);
    //t->scope = stack[stacktop];
    return t;
}

 TypeValue NewTypeValue()
{
   TypeValue t = (TypeValue)malloc(TypeValue_Size);
   memset(t, 0, TypeValue_Size);
   return t;
}

 Type NewType(KIND tn, TypeValue tv)
{
    Type t = (Type)malloc(Type_Size);
    memset(t, 0, Type_Size);
    t->tn = tn;
    t->tv = tv;
    return t;
}
