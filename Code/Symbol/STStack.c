/*************************************************************************
	> File Name: SymbolTable.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月03日 星期二 18时47分10秒
 ************************************************************************/

#include "list.h"
#include "STStack.h"
#include "SymbolTable.h"
#include "convenience.h"
#include "../syntax.tab.h"
static int lasttype = COMST;


STStack NewSTStack()
{
    STStack t = malloc(sizeof(struct STStack_));
    t->stacksize = 100;
    t->sts = malloc(sizeof(SymbolTable) * t->stacksize);
    t->stacktop = -1;
    memset(t->sts, 0, t->stacksize * sizeof(SymbolTable));
    ST_Push(t, NewSymbolTable(COMST));
    return t;
}

 
bool ST_Push(STStack stack, SymbolTable SymbolTable)
{    
    if(stack->stacktop == stack->stacksize - 1)
        return false;
    stack->stacktop++;
    //stack->sts[stack->stacktop] = SymbolTable;
    if(stack->stacktop == 0)
        stack->sts[stack->stacktop] = SymbolTable;
    else
    {
    SS_Push(stack->sts[0]->ss, NewScope());
    stack->sts[stack->stacktop] = stack->sts[0];
    stack->sts[stack->stacktop]->type = SymbolTable->type;
    }
    return true;
}


SymbolTable ST_Pop(STStack stack)
{
    if(stack->stacktop == -1)
        return NULL;
    SymbolTable t = stack->sts[stack->stacktop];
    stack->stacktop--;
    stack->sts[stack->stacktop]->type = COMST;
    SS_Pop(stack->sts[0]->ss);
    return t;
}

 
SymbolTable ST_GetTop(STStack stack)
{
    if(stack->stacktop == -1)
        return NULL;
    return stack->sts[stack->stacktop];
}



 //look up the table
 Symbol LookUpSymbol(STStack stack, Symbol s)
 {
    SymbolTable table = ST_GetTop(stack);
    Symbol csymbol = NULL;
    if(table->type == PARAMST)
    {
            csymbol = LookUpScope(SS_GetTop(table->ss), s);
            if(csymbol != NULL) 
            return csymbol;
    }
    unsigned hashnum = HashPjw(s->name);
    ListHead *ptr,*head;
    head = &table->slist[hashnum]->hashlist;
    for(ptr = head->next; ptr != head; ptr = ptr->next)
    {
        csymbol = SHLEntry(ptr);
        if(strcmp(s->name, csymbol->name) == 0)
            return csymbol;
    }
    table = stack->sts[0];
    head = &table->slist[hashnum]->hashlist;
    for(ptr = head->next; ptr != head; ptr = ptr->next)
    {
        csymbol = SHLEntry(ptr);
        if(strcmp(s->name, csymbol->name) == 0)
            return csymbol;
    }
    return NULL;
 }
