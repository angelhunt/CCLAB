/*************************************************************************
	> File Name: SDD.h
	> Author: 
	> Mail: 
	> Created Time: 2015年10月21日 星期三 18时21分51秒
 ************************************************************************/

#include "SDD.h"
//SDD.h提供函数
//函数中调用
//SDDFuncTable[root->nodetype](root->inh)


SDDFunc SDDFuncTable[] = 
{
    Program_Handle,   ExtDefList_Handle,      ExtDef_Handle,  ExtDecList_Handle,
    Specifier_Handle, StructSpecifier_Handle, OptTag_Handle,  Tag_Handle,
    VarDec_Handle,    FunDec_Handle,          VarList_Handle, ParamDec_Handle,
    CompSt_Handle,    StmtList_Handle,        Stmt_Handle,    DefList_Handle,
    Def_Handle,       DecList_Handle,         Dec_Handle,     Exp_Handle,
    Args_Handle
};

char SDDErrorStr[][70] = 
{
    "Undefined variable \"%s\".",                                     //1
    "Undefined function \"%s\".",                                     //2
    "Redefined variable \"%s\".",                                     //3
    "Redefined finction \"%s\".",                                     //4 
    "Type mismatched for assignment.",                                //5
    "The left-hand side of an assignment must be a variable.",        //6
    "Type mismatched for operands.",                                  //7
    "Type mismatched for return.",                                    //8
    "Function \"%s\" is not applicable for arguments \"%s\".",        //9
    "\"%s\" is not an array.",                                        //10
    "\"%s\" is not a function.",                                      //11
    "\"%s\" is not an integer.",                                      //12
    "Illegal use of \".\".",                                          //13
    "Non-existent field \"%s\".",                                     //14
    "Redefined field \"%s\".",                                        //15
    "Duplicated name \"%s\".",                                        //16
    "Undefined structure \"Position\".",                              //17
    "Undefined function \"%s\".",                                     //18
    "Inconsistent declaration of function \"%s\"."                    //19
};


Syn print_error(int errortype, int lineno, int argc, char *s1, char *s2)
{
    printf("Error type %d at Line %d: ", errortype, lineno);
    switch(argc)
    {
        case 0:
            printf("%s", SDDErrorStr[errortype - 1]);
            break;
        case 1:
            printf(SDDErrorStr[errortype - 1], s1);
            break;
        case 2:
            printf(SDDErrorStr[errortype - 1], s1, s2);
            break;
        default:break;
    }
    printf("\n");
    return NULL;
    //if(errortype != 3 && errortype != 19)
    //    exit(0);
}

STStack sts;
ScopeStack scs;
MCA mca;
void findUndefFunc()
{
    SymbolTable st = sts->sts[0];
    int i = 0;
    ListHead *head, *ptr;
    for(i = 0; i < HASH_TABLE_SIZE; i++)
    {
        head = &st->slist[i]->hashlist;
        for ((ptr) = (head)->next; (ptr) != (head); (ptr) = (ptr)->next)
        {
            Symbol s = SHLEntry(ptr);
            if(s->type->tn == FUNCAFF)
                print_error(18, s->lineno, 1, s->name, NULL);
        }
    }
}
void SDD(Node *root)
{
    //initial global data 
    mca = NewMCA();
    sts = NewSTStack();
    scs = NewScopeStack();


    //read and write
    TypeValue t1; 
    TypeValue t2;
    Type funtype;
    t1 = NewTypeValue();
    t2 = NewTypeValue();
    t2->basic = INT;
    t1->func = NewFuncType(NewType(BASIC, t2));
    t1->func->st = ST_GetTop(sts);
    t1->func->scope = SS_GetTop(t1->func->st->ss);
    t1->func->name = "read";
    funtype = NewType(FUNC, t1);
    Symbol ts = NewSymbol("read", funtype, -1);
    TableInsertSymbol(ST_GetTop(sts), ts);

    

    t1 = NewTypeValue();
    t1->func = NewFuncType(NewType(BASIC, t2));
    t1->func->st = ST_GetTop(sts);
    t1->func->scope = SS_GetTop(t1->func->st->ss);
    t1->func->name = "write";
    Symbol arg = NewSymbol("data", NewType(BASIC, t2), -1);
    ScopeInsertSymbol(t1->func->scope, arg);
    funtype = NewType(FUNC, t1);
    Symbol ts2 = NewSymbol("write", funtype, -1);
    TableInsertSymbol(ST_GetTop(sts), ts2);
    //run
    Program_Handle(root, NULL);
    #ifdef debug
    translate_Program(root, ST_GetTop(sts), mca);
    #else
    printMCA(mca, translate_Program(root, ST_GetTop(sts), mca));
    #endif
    findUndefFunc();
}

SDDFUNCDEF(Program_Handle)
{
    #ifdef DEBUG
    printf("Now is in func Program\n");
    #endif

    Node* child = n->children->head->next;
    n->syn = ExtDefList_Handle(child, NULL);
    return NULL;
}

SDDFUNCDEF(ExtDefList_Handle)
{
    #ifdef DEBUG
    printf("Now is in func ExtDefList\n");
    #endif

    Node* child = n->children->head->next;
    switch (n->seq)
    {
        case 0:
           ExtDef_Handle(child, NULL);
           child = child->next;
           ExtDefList_Handle(child, NULL);
           return NULL;
        case 1:
           return NULL;
    }
    
    return NULL;
}  
SDDFUNCDEF(ExtDef_Handle)
{
    #ifdef DEBUG
    printf("Now is in func ExtDef\n");
    #endif

    Node* child = n->children->head->next;
    Syn ts;
    Inh ti;
    TypeValue tv;
    switch (n->seq)
    {
        case 0:
            ts = Specifier_Handle(child, NULL);
            if(ts == NULL) return NULL;
            child = child->next;
            ExtDecList_Handle(child, ts);
            return NULL;
        case 1:
            ts = Specifier_Handle(child, NULL);
            if(ts == NULL) return NULL;
            return NULL;
        case 2:
            ts = Specifier_Handle(child, NULL);
            if(ts == NULL) return NULL;
            child = child->next;
            ST_Push(sts, NewSymbolTable(PARAMST));
            ts = FunDec_Handle(child, ts);
            if(ts == NULL) return NULL;
            child = child->next;
            CompSt_Handle(child, ts);
            ST_Pop(sts);
            return NULL;
        case 3:
            ts = Specifier_Handle(child, NULL);
            if(ts == NULL) return NULL;
            child = child->next;
            ts = FunDec_Handle(child, ts);
            if(ts == NULL) return NULL;
            return NULL;
            
    }
    return NULL;
}
SDDFUNCDEF(ExtDecList_Handle)
{
    #ifdef DEBUG
    printf("Now is in func ExtDecList\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn ts;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            ts = VarDec_Handle(child, i);
            if(ts == NULL) return NULL;
            return NULL;
        case 1:
            VarDec_Handle(child, i);
            child = child->next->next;
            ExtDecList_Handle(child, i);
            return NULL;
    }
    return NULL;
}
SDDFUNCDEF(Specifier_Handle)
{
    #ifdef DEBUG
    printf("Now is in func Specifier\n");
    #endif

    Node* child = n->children->head->next;
    Syn ts;
    Inh ti;
    TypeValue tv;
    switch (n->seq)
    {
        case 0:
            ts = NewSyn();
            tv = NewTypeValue();
            if(strcmp(child->data.s , "int") == 0)
                tv->basic = INT;
            if(strcmp(child->data.s , "float") == 0)
                tv->basic = FLOAT;
            ts->SType = NewType(BASIC, tv);
            child->syn = ts;
            return ts;
        case 1:
            ts = StructSpecifier_Handle(child, NULL);
            if(ts == NULL) return NULL;
            return ts;
    }
    return NULL;
}
SDDFUNCDEF(StructSpecifier_Handle)
{
    #ifdef DEBUG
    printf("Now is in func StructSpecifier\n");
    #endif

    Node* child = n->children->head->next;
    Node* t;
    Symbol symbol;
    Syn ts;
    TypeValue tv;
    Inh ti;
    char *s;
    switch (n->seq)
    {
        case 0:
            ST_Push(sts, NewSymbolTable(STRUCTST)); 
            ts = NewSyn();
            tv = NewTypeValue();
            tv->structure = NewStructureType();
            tv->structure->st = ST_GetTop(sts);
            tv->structure->scope = SS_GetTop(ST_GetTop(sts)->ss);
            ts->SType = NewType(STRUCTURE, tv);
            child = child->next;
            t = child;
            child = child->next->next;
            DefList_Handle(child, ts);
            ST_Pop(sts);
            OptTag_Handle(t, ts);
            return ts;
        case 1:
            child = child->next;
            Tag_Handle(child, ts);
            ts = NewSyn();
            s = child->children->head->next->data.s;
            symbol = LookUpSymbol(sts, NewSymbol(s, NULL, child->children->head->next->data.lineno));
            if(symbol == NULL)
                return print_error(17, child->data.lineno, 1, s, NULL);
            ts->SType = symbol->type;
            return ts;
    }
    return NULL;
}
SDDFUNCDEF(OptTag_Handle)
{
    #ifdef DEBUG
    printf("Now is in func OptTag\n"); 
    #endif
    Node* child = n->children->head->next;

    Symbol s;
    switch (n->seq)
    {
        case 0:
            i->SType->tv->structure->name = child->data.s;
            s = NewSymbol(child->data.s, i->SType, child->data.lineno);
            if(!TableInsertSymbol(ST_GetTop(sts), s))
                return print_error(16, n->data.lineno, 1, child->data.s, NULL);
            return NULL;
        case 1:
            return NULL;
    }
    return NULL;
}

SDDFUNCDEF(Tag_Handle)
{
    #ifdef DEBUG
    printf("Now is in func Tag\n");
    #endif

   /* Symbol srcsym = NewSymbol(n->data.s, NULL, child->data.lineno);
    Symbol dstsym = LOOKUPS(srcsym, 0, n->data.lineno);
    Syn ts = NewSyn();
    ts->SType = dstsym->type;
    */
    return NULL;
}

SDDFUNCDEF(VarDec_Handle)
{
    #ifdef DEBUG
    printf("Now is in func VarDec\n");
    #endif

    Node* child = n->children->head->next;
    Syn ts;
    Symbol symbol;
    TypeValue tv;
    switch (n->seq)
    {
        case 0:
            symbol = NewSymbol(child->data.s, i->SType, child->data.lineno);
           /* if(LookUpSymbol(sts, symbol) != NULL)
            {
                switch(ST_GetTop(sts)->type)
                {
                    case COMST : case PARAMST:
                        return print_error(3, n->data.lineno, 1, child->data.s, NULL);
                        break;
                    case STRUCTST:
                        return print_error(15, n->data.lineno, 1, child->data.s, NULL);
                        break;
                }
            }*/
            //if(getVarDecParent(n)->nodetype == ParamDec)
            if(ST_GetTop(sts)->type == STRUCTST || ST_GetTop(sts)->type == PARAMST)
            {
                if(symbol->type->tn == ARRAY)
                    symbol->type->ispointer = true;
                ScopeInsertSymbol(SS_GetTop(ST_GetTop(sts)->ss), symbol);
            }
            //else
            //{
            if(!TableInsertSymbol(ST_GetTop(sts), symbol))
            {
                switch(ST_GetTop(sts)->type)
                {
                    case COMST : case PARAMST:
                        return print_error(3, n->data.lineno, 1, child->data.s, NULL);
                        break;
                    case STRUCTST:
                        return print_error(15, n->data.lineno, 1, child->data.s, NULL);
                        break;
                }
            }
            //}
            child->syn->SType = i->SType;
            return NULL;
        case 1:
            ts = NewSyn();
            tv = NewTypeValue();
            tv->array = NewArrayType(i->SType, child->next->next->data.i);
            ts->SType = NewType(ARRAY, tv);
            ts = VarDec_Handle(child, ts);
            if(ts == NULL) return NULL;
            return NULL;
    }

    return NULL;
}
SDDFUNCDEF(FunDec_Handle)
{
    #ifdef DEBUG
    printf("Now is in func FunDec\n");
    #endif



    Node* child = n->children->head->next;
    Node* t;
    TypeValue tv;
    Syn ts;
    Inh ti;
    Symbol symbol;
    Symbol temp;
    switch (n->seq)
    {
        case 0:
            ts = NewSyn();
            tv = NewTypeValue();
            tv->func = NewFuncType(i->SType);
            tv->func->st = ST_GetTop(sts);
            tv->func->scope = SS_GetTop(tv->func->st->ss);
            tv->func->name = child->data.s;
            if(n->next->nodetype == SEMI)
                ts->SType = NewType(FUNCAFF, tv);
            else 
                ts->SType = NewType(FUNC, tv);
            t = child;
            child = child->next->next;
            VarList_Handle(child, ts);
            symbol = NewSymbol(t->data.s, ts->SType, child->data.lineno);
            temp = LookUpSymbol(sts, symbol);
            if(temp != NULL)
            {
                if(temp->type->tn == FUNC && ts->SType->tn == FUNC)
                    return print_error(4, t->data.lineno, 1, t->data.s, NULL);
                else
                {
                    if(!TypeIsEqual(symbol->type, temp->type))
                    {
                            return print_error(19, t->data.lineno, 1, t->data.s, NULL);
                    }
                    else
                    {
                        if(temp->type->tn == FUNCAFF && symbol->type->tn == FUNC)
                        {
                            delSymbol(temp);
                            free(temp);
                        }
                        if(symbol->type->tn == FUNCAFF && temp->type->tn == FUNC)
                        {
                            delSymbol(symbol);
                            free(symbol);
                        }
                    }
                }
            }
            else
            {
                if(!TableInsertSymbol(sts->sts[0], symbol))
                    return print_error(4, t->data.lineno, 1, t->data.s, NULL);
            }
            t->syn->SType = ts->SType;
            return ts;
        case 1:
            ts = NewSyn();
            tv = NewTypeValue();
            tv->func = NewFuncType(i->SType);
            tv->func->st = ST_GetTop(sts);
            tv->func->scope = SS_GetTop(tv->func->st->ss);
            tv->func->name = child->data.s;
            if(n->next->nodetype == SEMI)
                ts->SType = NewType(FUNCAFF, tv);
            else 
                ts->SType = NewType(FUNC, tv);
            symbol = NewSymbol(child->data.s, ts->SType, child->data.lineno);
            temp = LookUpSymbol(sts, symbol);
            if(temp != NULL)
            {
                if(temp->type->tn == FUNC && ts->SType->tn == FUNC)
                    return print_error(4, child->data.lineno, 1, child->data.s, NULL);
                else
                {
                    if(!TypeIsEqual(symbol->type, temp->type))
                            return print_error(19, child->data.lineno, 1, child->data.s, NULL);
                    else
                    {
                        if(temp->type->tn == FUNCAFF && symbol->type->tn == FUNC)
                        {
                            delSymbol(temp);
                            free(temp);
                        }
                        if(symbol->type->tn == FUNCAFF && temp->type->tn == FUNC)
                        {
                            delSymbol(symbol);
                            free(symbol);
                        }
                    }
                }
            }
            else
            {
                if(!TableInsertSymbol(sts->sts[0], symbol))
                    return print_error(4, child->data.lineno, 1, child->data.s, NULL);
            }
            child->syn->SType = ts->SType;
            return ts;
    }


    return NULL;
} 
SDDFUNCDEF(VarList_Handle)
{

    #ifdef DEBUG
    printf("Now is in func VarList\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn ts;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            ParamDec_Handle(child, i);
            child = child->next->next;
            VarList_Handle(child, i);
            return NULL;
        case 1:
            ParamDec_Handle(child, i);
            return NULL;
    }
    
    return NULL;


} 
SDDFUNCDEF(ParamDec_Handle)
{

    #ifdef DEBUG
    printf("Now is in func ParamDec\n");
    #endif

    TypeValue tv;
    Syn ts;
    Inh ti;
    Node* child = n->children->head->next;
    switch (n->seq)
    {
        case 0:
            ts = Specifier_Handle(child, NULL);
            if(ts == NULL) return NULL;
            child = child->next;
            VarDec_Handle(child, ts);
            break;
    }
    return NULL;
}
SDDFUNCDEF(CompSt_Handle)
{

    #ifdef DEBUG
    printf("Now is in func CompSt\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn s;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            child = child->next;
            DefList_Handle(child, i);
            child = child->next;
            StmtList_Handle(child, i);
            break;
    }

    return NULL;
}
SDDFUNCDEF(StmtList_Handle)
{

    #ifdef DEBUG
    printf("Now is in func StmtList\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn s;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            Stmt_Handle(child, i);
            //printMCA(mca, translate_Stmt(child, ST_GetTop(sts), mca));
            child = child->next;
            StmtList_Handle(child, i);
            break;
        case 1:
            break;
    }
    
    return NULL;
}   

SDDFUNCDEF(Stmt_Handle)
{

    #ifdef DEBUG
    printf("Now is in func Stmt\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn ts;
    Inh ti;
    Var v;
    switch (n->seq)
    {
        case 0:
            Exp_Handle(child, i);
            break;
        case 1:
            CompSt_Handle(child, i);
            break;
        case 2:
            child = child->next;
            ts = Exp_Handle(child, i);
            if(ts == NULL) return NULL;
            if(!TypeIsEqual(ts->SType, i->SType->tv->func->returntype))
                return print_error(8, n->data.lineno, 0, NULL, NULL);
            return NULL;
        case 3:
            child = child->next->next;
            Exp_Handle(child, i);
            child = child->next->next;
            Stmt_Handle(child, i);
            break;
        case 4:
            child = child->next->next;
            Exp_Handle(child, i);
            child = child->next->next;
            Stmt_Handle(child, i);
            child = child->next->next;
            Stmt_Handle(child, i);
            break;
    }
   
    return NULL;
}
SDDFUNCDEF(DefList_Handle)
{

    #ifdef DEBUG
    printf("Now is in func DefList\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn s;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            Def_Handle(child, i);
            child = child->next;
            DefList_Handle(child, i);
            return NULL;
        case 1:
            return NULL;
    }

    return NULL;
}
SDDFUNCDEF(Def_Handle)
{

    #ifdef DEBUG
    printf("Now is in func Def\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn ts;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            ts = Specifier_Handle(child, i);
            if(ts == NULL) return NULL;
            child = child->next;
            DecList_Handle(child, ts);
            return NULL;
    }

    return NULL;
}  

SDDFUNCDEF(DecList_Handle)
{

    #ifdef DEBUG
    printf("Now is in func DecList\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn s;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            Dec_Handle(child, i);
            return NULL;
        case 1:
            Dec_Handle(child, i);
            child = child->next->next;
            DecList_Handle(child, i);
            return NULL;
    }

    return NULL;
} 

SDDFUNCDEF(Dec_Handle)
{

    #ifdef DEBUG
    printf("Now is in func Dec\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn s;
    Inh ti;
    switch (n->seq)
    {
        case 0:
            VarDec_Handle(child, i);
            return NULL;
        case 1:
            VarDec_Handle(child, i);
            child = child->next->next;
            Exp_Handle(child, i);
            return NULL;
    }

    return NULL;
}    
SDDFUNCDEF(Exp_Handle)
{
    #ifdef DEBUG
    printf("Now is in func Exp\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn ts1, ts2;
    Inh ti;
    Symbol symbol;
    switch (n->seq)
    {
        case 0:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            if(!(child->seq == 15 || child->seq == 14 || child->seq == 9 || child->seq == 0 || child->seq == 13 || child->seq == 14))
                return print_error(6, child->data.lineno, 0, NULL, NULL);
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(5, n->data.lineno, 0, NULL, NULL);
            return NULL;
        case 1:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 2:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 3:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 4:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 5:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 6:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 7:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!TypeIsEqual(ts1->SType, ts2->SType))
                return print_error(7, n->data.lineno, 0, NULL, NULL);
            return ts1;
        case 8:
            child = child->next;
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            return ts1;
        case 9:
            child = child->next;
            ts1 = Exp_Handle(child, i);
            return ts1;
        case 10:
            child = child->next;
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            return ts1;
        case 11:
            symbol = LookUpSymbol(sts, NewSymbol(child->data.s, NULL, child->data.lineno));
            if(symbol == NULL)
                    return print_error(2, child->data.lineno, 1, child->data.s, NULL);
                if(symbol->type->tn != FUNC)
                    return print_error(11, child->data.lineno, 1, child->data.s, NULL);
            child = child->next->next;
            ts1 = NewSyn();
            ts1->SType = symbol->type;
            ts2 = Args_Handle(child, ts1);
            symbol->type->tv->func->scope->scopeposition = &symbol->type->tv->func->scope->scopelist;
            if(ts2 == NULL)
                return print_error(9, child->data.lineno, 2, getFuncStr(ts1->SType->tv->func), getArgsStr(child));
            return ts1;
        case 12:
            symbol = LookUpSymbol(sts, NewSymbol(child->data.s, NULL, child->data.lineno));
            if(symbol == NULL)
                return print_error(2, child->data.lineno, 1, child->data.s, NULL);
            if(symbol->type->tn != FUNC)
                return print_error(11, child->data.lineno, 1, child->data.s, NULL);
            ts1 = NewSyn();
            ts1->SType = symbol->type;
            return ts1;
        case 13:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            if(ts1->SType->tn != ARRAY)
            {
                char str[100];
                str[0] = '\0';
                Get_Node_Str(child, str, 100);
                return print_error(10, child->data.lineno, 1, str, NULL);
            }
            child = child->next->next;
            ts2 = Exp_Handle(child, i);
            if(ts2 == NULL) return NULL;
            if(!(ts2->SType->tn == BASIC && ts2->SType->tv->basic == INT))
            {
                char str[100];
                str[0] = '\0';
                Get_Node_Str(child, str, 100);
                return print_error(12, child->data.lineno, 1, str, NULL);
            }
            ts2 = NewSyn();
            ts2->SType = ts1->SType->tv->array->elem;
            n->syn = ts2;
            return ts2;
        case 14:
            ts1 = Exp_Handle(child, i);
            if(ts1 == NULL) return NULL;
            if(ts1->SType->tn != STRUCTURE)
                return print_error(13, child->data.lineno, 0, NULL, NULL);
            child = child->next->next;
            symbol = LookUpScope(ts1->SType->tv->structure->scope, NewSymbol(child->data.s, NULL, child->data.lineno));
            if(symbol == NULL)
                return print_error(14, child->data.lineno, 1, child->data.s, NULL);
            ts1 = NewSyn();
            ts1->SType = symbol->type; 
            n->syn = ts1;
            return ts1;
        case 15:
            symbol = LookUpSymbol(sts, NewSymbol(child->data.s, NULL, child->data.lineno));
            if(symbol == NULL)
                return print_error(1, child->data.lineno, 1, child->data.s, NULL);
            ts1 = NewSyn();
            if(symbol != NULL)
                ts1->SType = symbol->type;
            n->syn = ts1;
            return ts1;
        case 16:
            ts1 = NewSyn();
            tv = NewTypeValue();
            tv->basic = INT;
            ts1->SType = NewType(BASIC, tv); 
            n->syn = ts1;
            return ts1;
        case 17:
            ts1 = NewSyn();
            tv = NewTypeValue();
            tv->basic = FLOAT;
            ts1->SType = NewType(BASIC, tv); 
            n->syn = ts1;
            return ts1;
            
    }

    return NULL;

}



SDDFUNCDEF(Args_Handle)
{
    #ifdef DEBUG
    printf("Now is in func Args\n");
    #endif

    Node* child = n->children->head->next;
    TypeValue tv;
    Syn ts;
    Inh ti;
    Type opt;
    Scope scope;
    switch (n->seq)
    {
        case 0:
            ts = Exp_Handle(child, i);
            if(ts == NULL) return NULL;
            scope = i->SType->tv->func->scope;
            if(!ArgForward(i->SType->tv->func))
                return NULL;
            opt = list_entry(scope->scopeposition, struct Symbol_, scopelist)->type;
            if (!TypeIsEqual(ts->SType, opt))
                return NULL;
            child = child->next->next;
            ts = Args_Handle(child, i);
            if(ts == NULL) return NULL;
            return ts;
        case 1:
            ts = Exp_Handle(child, i);
            if(ts == NULL) 
                return NULL;
            scope = i->SType->tv->func->scope;
            if(!ArgForward(i->SType->tv->func))    
                return NULL;
            opt = list_entry(scope->scopeposition, struct Symbol_, scopelist)->type;
            if (!TypeIsEqual(ts->SType, opt))
                return NULL;
            return ts;
    }

    return NULL;
}
