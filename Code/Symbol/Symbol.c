/*************************************************************************
	> File Name: SymbolTable.c
	> Author: 
	> Mail: 
	> Created Time: 2015年10月17日 星期六 15时01分36秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Symbol.h"
#include "../syntax.tab.h"

int listSize = sizeof(ListHead);
int symbolSize = sizeof(struct Symbol_);



//creat new symbol
 Symbol NewSymbol(char *name, Type type, int depth)
{
    Symbol symbol = malloc(symbolSize);
    memset((void *)symbol, 0, symbolSize);
    symbol->name = name;
    symbol->type = type;
    symbol->depth = depth;
    return symbol;
}

 bool SymbolIsEqual(Symbol s1, Symbol s2)
{
    if(strcmp(s1->name, s2->name) == 0)
        return true;
    else
        return false;
}


char *getFuncStr(FuncType f)
{
    Scope scope = f->scope;
    ListHead *ptr,*head;
    head = &scope->scopelist;
    char *str = CONVENIENCE_malloc(100);
    strncat(str, f->name, 100 - strlen(str));
    strncat(str, "(", 100 - strlen(str));
    for(ptr = head->next; ptr != head; ptr = ptr->next)
    {
        if(ptr != head->next)
            strncat(str, ", ", 100 - strlen(str));
        Symbol csymbol = list_entry(ptr, struct Symbol_, scopelist);
        switch(csymbol->type->tn)
        {
            case BASIC:
                if(csymbol->type->tv->basic == INT) strncat(str, "int", 100 - strlen(str));
                if(csymbol->type->tv->basic == FLOAT) strncat(str, "float", 100 - strlen(str));
                break;
            case STRUCTURE:
                strncat(str, "struct ", 100 - strlen(str));
                strncat(str, csymbol->type->tv->structure->name, 100 - strlen(str));
        }
    }
    strncat(str, ")", 100 - strlen(str));
    return str;
}
    


bool TypeIsEqual(Type t1, Type t2)
{
    Scope scope1;
    Scope scope2;
    ListHead *head1, *head2, *ptr1, *ptr2;
    Symbol s1, s2;
    if(t1->tn == t2->tn || (t1->tn == FUNC && t2->tn == FUNCAFF) || (t1->tn == FUNC && t2->tn == FUNCAFF) )
    {
        switch(t1->tn)
        {
            case BASIC:
                return t1->tv->basic == t2->tv->basic;
            case ARRAY:
                return t1->tv == t2->tv;
            case FUNC: case FUNCAFF:
                scope1 = t1->tv->func->scope;
                scope2 = t2->tv->func->scope;
                head1 = &scope1->scopelist;
                head2 = &scope2->scopelist;
	            for (ptr1 = head1->next, ptr2 = head2->next; ptr1 != head1 && ptr2 != head2; ptr1 = ptr1->next, ptr2 = ptr2->next)
                {
                    s1 = list_entry(ptr1, struct Symbol_, scopelist);
                    s2 = list_entry(ptr2, struct Symbol_, scopelist);
                    if(!TypeIsEqual(s1->type, s2->type))
                        return false;
                }
                if(!(ptr1 == head1 && ptr2 == head2))
                    return false;
                return true; 
            default:
                return false;
        }
    }
    else
    {
        if(t2->tn == FUNC)
            return TypeIsEqual(t1, t2->tv->func->returntype);
        return false;
    }
}

