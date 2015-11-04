/*************************************************************************
	> File Name: ScopeStack.h
	> Author: 
	> Mail: 
	> Created Time: 2015年11月03日 星期二 20时57分41秒
 ************************************************************************/

#ifndef _SCOPESTACK_H
#define _SCOPESTACK_H
#include "common.h"
#include "list.h"
struct Scope_
{
    ListHead scopelist;
    ListHead *scopeposition;
};
typedef struct Scope_* Scope;
struct ScopeStack_
{
    int stacksize;
    int stacktop;
    Scope* sc;
};
typedef struct ScopeStack_* ScopeStack;
extern Scope NewScope();
extern ScopeStack NewScopeStack();
extern bool SS_Push(ScopeStack stack, Scope s);
extern Scope SS_Pop(ScopeStack stack);
extern Scope SS_GetTop(ScopeStack stack);
extern void ScopePrints(Scope s);
struct Symbol_;
extern struct Symbol_* LookUpScope(Scope scope, struct Symbol_* s);
#endif
