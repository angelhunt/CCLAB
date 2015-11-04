/*************************************************************************
	> File Name: SymbolTable.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月03日 星期二 19时05分31秒
 ************************************************************************/

#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<stdlib.h>
#include "SymbolTable.h"
const unsigned HASH_TABLE_SIZE = 0xff;



//hash function
unsigned  HashPjw(char *name)
{
    unsigned val = 0, i;
    for(; *name; ++name)
    {
        val = (val << 2) + *name;
        if(i =val & ~ HASH_TABLE_SIZE) val = (val ^ (i >> 12)) & HASH_TABLE_SIZE;
    }
    return val;
}


//initial
 void SymboltableInit(SymbolTable st)
{
    int i = 0;
    for(i = 0; i < HASH_TABLE_SIZE; i++)
    {
        st->slist[i] = NewSymbol(NULL, NULL, 0);
        list_init(&st->slist[i]->hashlist);
        list_init(&st->slist[i]->scopelist);
    }
}


SymbolTable NewSymbolTable(STTYPE type)
{
    SymbolTable t = malloc(sizeof(struct SymbolTable_));
    t->type = type;
    t->slist = malloc(sizeof(Symbol) * HASH_TABLE_SIZE);
    t->ss = NewScopeStack();
    SS_Push(t->ss, NewScope());
    SymboltableInit(t);
    return t;
}


//You should call NewSymbol before call it
bool TableInsertSymbol(SymbolTable table, Symbol s)
{
    unsigned hashnum = HashPjw(s->name);
    ListHead *ptr,*head;
    head = &table->slist[hashnum]->hashlist;
    for(ptr = head->next; ptr != head; ptr = ptr->next)
    {
        Symbol csymbol = SHLEntry(ptr);
        if(strcmp(s->name, csymbol->name) == 0)
            return false;
    }
    list_add_after(&table->slist[hashnum]->hashlist, &s->hashlist);
    if(table->type == STRUCTST || table->type == PARAMST)
    {
        Scope scope = SS_GetTop(table->ss);
        list_add_after(&(scope->scopelist), &s->scopelist);
    }
    return true;
}

//Just for test
 void SymbolTablePrint(SymbolTable table)
{
    int i;
    printf("SymbolTable:\n");
    for(i = 0; i < HASH_TABLE_SIZE; i++)
    {
        ListHead *ptr,*head;
        head = &table->slist[i]->hashlist;
        if(!list_empty(head))
            {
                for(ptr = head->next; ptr != head; ptr = ptr->next)
                printf("%s\n",SHLEntry(ptr)->name); 
            }
    
    }
    printf("ScopeStack top:\n");
    ScopePrints(SS_GetTop(table->ss));
}
