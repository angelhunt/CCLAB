/*************************************************************************
	> File Name: ScopeStack.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月03日 星期二 20时54分10秒
 ************************************************************************/

#include<stdio.h>
#include"ScopeStack.h"
#include "Symbol.h"
Scope NewScope()
{
  Scope t = malloc(sizeof(struct Scope_));
  list_init(&t->scopelist);
  t->scopeposition = &t->scopelist;
    return t;
}
ScopeStack NewScopeStack()
{
    ScopeStack ss = malloc(sizeof(struct ScopeStack_));
    ss->stacksize = 10;
    ss->sc = malloc(sizeof(Scope) * ss->stacksize);
    ss->stacktop = -1;
    return ss;
}
bool SS_Push(ScopeStack stack, Scope s)
{    
    if(stack->stacktop == stack->stacksize - 1)
        return false;
    stack->stacktop++;
    stack->sc[stack->stacktop] = s;
    return true;
}


Scope SS_Pop(ScopeStack stack)
{
    if(stack->stacktop == -1)
        return NULL;
    Scope t = stack->sc[stack->stacktop];
    stack->stacktop--;
    return t;
}

 
Scope SS_GetTop(ScopeStack stack)
{
    if(stack->stacktop == -1)
        return NULL;
    return stack->sc[stack->stacktop];
}

void ScopePrints(Scope s)
{
    ListHead *head,*ptr;
    head = &s->scopelist;
    for(ptr = head->next; ptr != head; ptr = ptr->next)
        printf("%s\n", SSLEntry(ptr)->name);
}


struct Symbol_* LookUpScope(Scope scope, struct Symbol_* s)
{
    ListHead *head,*ptr;
    head = &scope->scopelist;
    for(ptr = head->next; ptr != head; ptr = ptr->next)
    {
        Symbol csymbol = SSLEntry(ptr);
        if(strcmp(s->name, csymbol->name) == 0)
            return csymbol;
    }
    return NULL;
}

bool ScopeInsertSymbol(Scope scope, struct Symbol_* s)
{
    ListHead *ptr,*head;
    head = &scope->scopelist;
    for(ptr = head->next; ptr != head; ptr = ptr->next)
    {
        Symbol csymbol = SSLEntry(ptr);
        if(strcmp(s->name, csymbol->name) == 0)
            return false;
    }
    list_add_before(head, &s->scopelist);
    return true;
}
