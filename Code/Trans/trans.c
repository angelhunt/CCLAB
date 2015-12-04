/*************************************************************************
	> File Name: trans.c
	> Author: 
	> Mail: 
	> Created Time: 2015年11月13日 星期五 19时54分39秒
 ************************************************************************/

#include "trans.h"


static inline MCAHead genPlaceMidCode(MCA mca, MIDCODET kind, Var place, Var t2, Var t3)
{
    if(place == NULL) 
        return NULL;
    MCAHead h = NewMCAHead(mca, NewMidCode(kind, place, t2, t3));
    return h;
}
MCAHead translate_Exp(Node *n, SymbolTable table, Var place, MCA mca)
{
    assert(n->nodetype == Exp);
    Var v1, v2, v3, v4, v5;
    Node* child = n->children->head->next;
    Symbol symbol;
    MCAHead h;
    MCAHead h1, h2, h3, h4, h5;
    char *temp;
    Var vlist[12];
    int vlistlen = 0;
    int t;
    switch(n->seq)
    {
        case 0:   //ASSIGNOP
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            h1 = translate_Exp(child, table, v1, mca);
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h2 = translate_Exp(child->next->next, table, v2, mca);
            h3 = NewMCAHead(mca, NewMidCode(C_ASSIGN, v1, v2, NULL));
            h4 = genPlaceMidCode(mca, C_ASSIGN, place, v3, NULL);
            h = LinkMulMCAHead(mca, 4, h1, h2, h3, h4);
            break;
        case 1:   case 2: case 3: case 10:  //AND OR NOT RELOP
            v3 = NewVar(CON);
            v3->value = 0;
            h1 = genPlaceMidCode(mca, C_ASSIGN, place, v3, NULL);
            v1 = NewVar(PLACE);
            v1->ttype = LABEL;
            v2 = NewVar(PLACE);
            v2->ttype = LABEL;
            h2 = translate_Cond(n, v1, v2, table, mca);
            v3 = NewVar(CON);
            v3->value = 1;
            h = LinkMulMCAHead(mca, 5, h1, h2,
                               NewMCAHead(mca, NewMidCode(C_LAB, v1, NULL, NULL)),
                               genPlaceMidCode(mca, C_ASSIGN, place, v3, NULL),
                               NewMCAHead(mca, NewMidCode(C_LAB, v2, NULL, NULL)));
            break;
        case 4:   //PLUS
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h1 = translate_Exp(child, table, v2, mca);
            v3 = NewVar(PLACE);
            v3->ttype = TEMP;
            h2 = translate_Exp(child->next->next, table, v3, mca);
            h3 = genPlaceMidCode(mca, C_ADD, place, v2, v3);
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
        case 5:   //MINUS
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h1 = translate_Exp(child, table, v2, mca);
            v3 = NewVar(PLACE);
            v3->ttype = TEMP;
            h2 = translate_Exp(child->next->next, table, v3, mca);
            h3 = genPlaceMidCode(mca, C_SUB, place, v2, v3);
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
        case 6:   //STAR
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h1 = translate_Exp(child, table, v2, mca);
            v3 = NewVar(PLACE);
            v3->ttype = TEMP;
            h2 = translate_Exp(child->next->next, table, v3, mca);
            h3 = genPlaceMidCode(mca, C_MUL, place, v2, v3);
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
        case 7:   //DIV
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h1 = translate_Exp(child, table, v2, mca);
            v3 = NewVar(PLACE);
            v3->ttype = TEMP;
            h2 = translate_Exp(child->next->next, table, v3, mca);
            h3 = genPlaceMidCode(mca, C_DIV, place, v2, v3);
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
        case 8:   //LPRP
            h = translate_Exp(child->next, table, place, mca);
            break;
        case 9:   //MINUS
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            h1 = translate_Exp(child->next, table, v1, mca);
            v2 = NewVar(CON);
            v2->value = 0;
            h2 = genPlaceMidCode(mca, C_SUB, place, v2, v1);
            h = LinkMulMCAHead(mca, 2, h1, h2);
            break;
        case 11:  //CALL
            v1 = NewVar(VAR);
            v1->name = NT_getChild(n, 0)->data.s;
            h1 = translate_Args(NT_getChild(n, 2), table, vlist, &vlistlen, mca);
            #ifdef debug
            printf("args\n");
            printMCA(mca, h1);
            printf("args\n");
            #endif
            if(strcmp(v1->name, "write") == 0) 
            {
                h = LinkMulMCAHead(mca, 2, h1,
                                   NewMCAHead(mca, NewMidCode(C_WRITE, vlist[0], NULL, NULL)));
            }
            else
            {
                for(t = 0; t < vlistlen; t++)
                    h1 = LinkMulMCAHead(mca, 2, h1,
                                   NewMCAHead(mca, NewMidCode(C_ARG, vlist[t], NULL, NULL)));
                h = LinkMulMCAHead(mca, 2, h1, genPlaceMidCode(mca, C_CALL, place, v1, NULL));
            }
            break;
        case 12:  //CALL NO ARG
            v1 = NewVar(VAR);
            v1->name = NT_getChild(n, 0)->data.s;
            if(strcmp(v1->name, "read") == 0)
                h = genPlaceMidCode(mca, C_READ, place, NULL, NULL);
            else 
                h = genPlaceMidCode(mca, C_CALL, place, v1, NULL);
            break;
        case 13:  //ARRAY
            if(NT_getChild(n, 0)->seq == 15)
            {
                temp = NT_getChild(NT_getChild(n, 0), 0)->data.s;
                symbol = LookUpSymbol(sts, NewSymbol(temp, NULL, -1));
                if(n->syn == NULL)
                   n->syn = NewSyn();
                n->syn->SType = symbol->type->tv->array->elem;
                n->syn->symbol = symbol;
                v1 = NewVar(PLACE);
                v1->ttype = TEMP;
                h1 = translate_Exp(NT_getChild(n, 2), table, v1, mca);
                v2 = NewVar(CON);
                v2->value = n->syn->SType->width;
                v3 = NewVar(TEMP);
                n->syn->addr = v3;
                h2 = NewMCAHead(mca, NewMidCode(C_MUL, v3, v1, v2));
                h = LinkMulMCAHead(mca, 2, h1, h2);
            }
            else 
            {
                if(n->syn == NULL)
                   n->syn = NewSyn();
                h1 = translate_Exp(NT_getChild(n, 0), table, NULL, mca);
                n->syn->SType = NT_getChild(n, 0)->syn->SType->tv->array->elem;
                n->syn->symbol = NT_getChild(n, 0)->syn->symbol;
                v1 = NewVar(PLACE);
                v1->ttype = TEMP;
                h2 = translate_Exp(NT_getChild(n, 2), table, v1, mca);
                v2 = NewVar(TEMP);
                v3 = NewVar(CON);
                v3->value = n->syn->SType->width;
                h3 = NewMCAHead(mca, NewMidCode(C_MUL, v2, v1, v3));
                v4 = NewVar(TEMP);
                n->syn->addr = v4;
                h4 = NewMCAHead(mca, NewMidCode(C_ADD, v4, NT_getChild(n, 0)->syn->addr, v2));
                h = LinkMulMCAHead(mca, 4, h1, h2, h3, h4);
            }
            if(n->parent->nodetype != Exp || n->parent->seq != 13)
            {
                if(n->syn->symbol->type->ispointer)
                    v1 = NewVar(VAR);
                else 
                    v1 = NewVar(GetADDR);
                v1->name = n->syn->symbol->name;
                v2 = NewVar(TEMP);
                h5 = NewMCAHead(mca, NewMidCode(C_ADD, v2, v1, n->syn->addr));
                h = LinkMulMCAHead(mca, 2, h, h5);
                n->syn->addr = v2;

                changevar(place, n->syn->addr);
                place->kind = ADDR;
                char *temp = malloc(5);
                sprintf(temp, "t%d", place->var_no);
                place->name = temp;

            }
            break;
        case 14:  //STRUCT
            break;
        case 15:   //ID
            symbol = LookUpSymbol(sts, NewSymbol(child->data.s, NULL, -1));
            switch(symbol->type->tn)
            {
                case BASIC:  
                    v2 = NewVar(VAR);
                    v2->name = child->data.s;
                    changevar(place, v2);
                    //h = genPlaceMidCode(mca, C_ASSIGN, place, v2, NULL);
                    h = NULL;
                    break;
                
                case ARRAY:
                    v2 = NewVar(GetADDR);
                    v2->name = child->data.s;
                    changevar(place, v2);
                    h = NULL;
                    break;
                case STRUCTURE:
                    printf("%s", "Cannot translate: Code contains variables or parameters of structure type\n.");
                    exit(0);
                    break;
            }
            break;
        case 16:   //INT
            v2 = NewVar(CON);
            v2->value = child->data.i; 
            changevar(place, v2);
           // place = v2;
            //h = genPlaceMidCode(mca, C_ASSIGN, place, v2, NULL);
            h = NULL;
            break;
        case 17:   //FLOAT
            break;
    }
    return h;
}




MCAHead translate_Stmt(Node* n, SymbolTable table, MCA mca)
{
    assert(n->nodetype == Stmt);
    Var v1, v2, v3;
    Node* child = n->children->head->next;
    MCAHead h;
    MCAHead h1, h2, h3, h4, h5, h6, h7;

    switch(n->seq)
    {
        case 0:        //Exp
            h = translate_Exp(child, table, NULL, mca);
            break;
        case 1:        //Compst
            return translate_CompSt(child, table, mca);
            break;
        case 2:        //RETURN
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            h1 = translate_Exp(child->next, table, v1, mca);
            h2 = NewMCAHead(mca, NewMidCode(C_RETURN, v1, NULL, NULL));
            h = LinkMulMCAHead(mca, 2, h1, h2);
            break;
        case 3:        //IF
            v1 = NewVar(PLACE);
            v1->ttype = LABEL;
            v2 = NewVar(PLACE);
            v2->ttype = LABEL;
            h1 = translate_Cond(child->next->next, v1, v2, table,mca);
            h2 = NewMCAHead(mca, NewMidCode(C_LAB, v1, NULL, NULL));
            h3 = translate_Stmt(NT_getChild(n, 4), table, mca);
            h4 = NewMCAHead(mca, NewMidCode(C_LAB, v2, NULL, NULL));
            h = LinkMulMCAHead(mca, 4, h1, h2, h3, h4);
            break;
        case 4:        //IF ELSE
            v1 = NewVar(PLACE);
            v1->ttype = LABEL;
            v2 = NewVar(PLACE);
            v2->ttype = LABEL;
            v3 = NewVar(PLACE);
            v3->ttype = LABEL;
            h1 = translate_Cond(child->next->next, v1, v2, table,mca);
            h2 = NewMCAHead(mca, NewMidCode(C_LAB, v1, NULL, NULL));
            h3 = translate_Stmt(NT_getChild(n, 4), table, mca);
            h4 = NewMCAHead(mca, NewMidCode(C_GOTO, v3, NULL, NULL)); 
            h5 = NewMCAHead(mca, NewMidCode(C_LAB, v2, NULL, NULL));
            h6 = translate_Stmt(NT_getChild(n, 6), table, mca);
            h7 = NewMCAHead(mca, NewMidCode(C_LAB, v3, NULL, NULL));
            assert(h6 != NULL && h2 != NULL);
            h = LinkMulMCAHead(mca, 7, h1, h2, h3, h4, h5, h6, h7);
            break;
        case 5:        //WHILE
            v1 = NewVar(PLACE);
            v1->ttype = LABEL;
            v2 = NewVar(PLACE);
            v2->ttype = LABEL;
            v3 = NewVar(PLACE);
            v3->ttype = LABEL;
            h1 = NewMCAHead(mca, NewMidCode(C_LAB, v1, NULL, NULL)); 
            h2 = translate_Cond(NT_getChild(n, 2), v2, v3, table,mca);
            h3 = NewMCAHead(mca, NewMidCode(C_LAB, v2, NULL, NULL));
            h4 = translate_Stmt(NT_getChild(n, 4), table, mca);
            h5 = NewMCAHead(mca, NewMidCode(C_GOTO, v1, NULL, NULL));
            h6 = NewMCAHead(mca, NewMidCode(C_LAB, v3, NULL, NULL));
            h = LinkMulMCAHead(mca, 6, h1, h2, h3, h4, h5, h6);
            break;
    }
    
    return h;
}



MCAHead translate_Cond(Node *n, Var lt, Var lf, SymbolTable table, MCA mca)
{
    assert(n->nodetype == Exp);
    Var v1, v2, v3;
    Node* child = n->children->head->next;
    MCAHead h;
    MCAHead h1, h2, h3, h4, h5;
    char *op;
    switch(n->seq)
    {
        case 3:                   //RELOP
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h1 = translate_Exp(NT_getChild(n, 0), table, v1, mca);
            h2 = translate_Exp(NT_getChild(n, 2), table, v2, mca);
            h3 = NewMCAHead(mca, NewMidCode(C_IF, v1, v2, lt));
            h3->ptrtoe->op = NT_getChild(n, 1)->data.s;
            h4 = NewMCAHead(mca, NewMidCode(C_GOTO, lf, NULL, NULL));
            h = LinkMulMCAHead(mca, 4, h1, h2, h3, h4);
            break;
        case 10:                  //NOT
            h = translate_Cond(NT_getChild(n, 1), lf, lt, table, mca);
            break;
        case 1:                   //AND
            v1 = NewVar(PLACE);
            v1->ttype = LABEL;
            h1 = translate_Cond(NT_getChild(n, 0), v1, lf, table, mca);
            h2 = NewMCAHead(mca, NewMidCode(C_LAB, v1, NULL, NULL));
            h3 = translate_Cond(NT_getChild(n, 2), lt, lf, table, mca);
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
        case 2:                   //OR
            v1 = NewVar(PLACE);
            v1->ttype = LABEL;
            h1 = translate_Cond(NT_getChild(n, 0), lt, v1, table, mca);
            h2 = NewMCAHead(mca, NewMidCode(C_LAB, v1, NULL, NULL));
            h3 = translate_Cond(NT_getChild(n, 2), lt, lf, table, mca);
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
        default:
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            h1 = translate_Exp(child, table, v1, mca);
            v2 = NewVar(CON);
            v2->value = 0;
            h2 = NewMCAHead(mca, NewMidCode(C_IF, v1, v2, lt));
            h3 = NewMCAHead(mca, NewMidCode(C_GOTO, lf, NULL, NULL));
            h = LinkMulMCAHead(mca, 3, h1, h2, h3);
            break;
    }

    return h;
}



MCAHead translate_Args(Node *n, SymbolTable table, Var* vlist, int *len, MCA mca)
{
    assert(n->nodetype == Args);
    Var v1, v2, v3;
    Node* child = n->children->head->next;
    MCAHead h;
    MCAHead h1, h2, h3;
    switch(n->seq)
    {
        case 0:
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            h1 = translate_Exp(NT_getChild(n, 0), table, v1, mca);
            vlist[*len] = v1;
            *len = *len + 1;
            h2 = translate_Args(NT_getChild(n, 2), table, vlist, len, mca);
            h = LinkMulMCAHead(mca, 2, h1, h2);
            break;
        case 1:
            v1 = NewVar(PLACE);
            v1->ttype = TEMP;
            h = translate_Exp(NT_getChild(n, 0), table, v1, mca);
            vlist[*len] = v1;
            *len = *len + 1;
            break;
    }

    return h;
}





MCAHead translate_Program(Node *n, SymbolTable table, MCA mca)
{
    assert(n->nodetype == Program);
    Var v1, v2, v3;
    Node* extdl = NT_getChild(n, 0);
    Node *ext, *comp, *funcdecid;
    MCAHead h = NULL;
    MCAHead h1, h2, h3;
    
    while(extdl->seq != 1)
    {
        ext = NT_getChild(extdl, 0);
        if(ext->seq == 2)
        {
            h1 = translate_FunDec(NT_getChild(ext, 1), table, mca);
            #ifdef debug
            printf("fundec\n");
            printMCA(mca, h1);
            printf("fundec\n");
            #endif

            comp = NT_getChild(ext, 2);
            h2 = translate_CompSt(comp, table, mca);
            if(h == NULL)
                h = LinkMulMCAHead(mca, 2, h1, h2);
            else
                h = LinkMulMCAHead(mca, 3, h, h1, h2);
        }



        extdl = NT_getChild(extdl, 1);
    }


    return h;
}

MCAHead translate_FunDec(Node *n, SymbolTable table, MCA mca)
{
    assert(n->nodetype == FunDec);
    Var v1, v2, v3;
    Node* varlist = NT_getChild(n, 2);
    char *varid;
    Node *funcdecid;
    MCAHead h = NULL;
    MCAHead h1, h2, h3;
    funcdecid = NT_getChild(n, 0);
    v1 = NewVar(VAR);
    v1->name = funcdecid->data.s;
    h = NewMCAHead(mca, NewMidCode(C_FUNC,  v1, NULL, NULL));
    if(n->seq == 0)
    {
    while(1)
    {
        varid = getVarId(NT_getChild(NT_getChild(varlist, 0), 1));
        Symbol s = LookUpSymbol(sts, NewSymbol(varid, NULL, -1));
        if(s->type->tn == STRUCTURE)
        {
            printf("%s", "Cannot translate: Code contains variables or parameters of structure type.\n");
            exit(0);
            
        }
        
        v1 = NewVar(VAR);
        v1->name = varid;
        h1 = NewMCAHead(mca, NewMidCode(C_PARAM, v1, NULL, NULL));
        h = LinkMulMCAHead(mca, 2, h, h1);
        if(varlist->seq == 1)
            break;
        varlist = NT_getChild(varlist, 2);
    }
    }

    return h;
}
    

MCAHead translate_CompSt(Node *n, SymbolTable table, MCA mca)
{
    assert(n->nodetype == CompSt);
    Var v1, v2, v3;
    Node* stmtlist = NT_getChild(n, 2);
    Node* deflist = NT_getChild(n, 1);
    Node *stmt;
    MCAHead h = NULL;
    MCAHead h1, h2, h3;
    
    h = translate_DefList(deflist, table, mca);
    while(stmtlist->seq != 1)
    {
        stmt = NT_getChild(stmtlist, 0);
        h1 = translate_Stmt(stmt, table, mca);
        h = LinkMulMCAHead(mca, 2, h, h1);
        stmtlist = NT_getChild(stmtlist, 1);
    }

    return h;
}


MCAHead translate_DefList(Node *n, SymbolTable table, MCA mca)
{
    assert(n->nodetype == DefList);
    Var v1, v2, v3;
    Node* deflist = n;
    Node *declist = NULL;

    MCAHead h = NULL;
    MCAHead h1, h2, h3;

    while(deflist->seq != 1)
    {
        declist = NT_getChild(NT_getChild(deflist, 0), 1);
        h1 = translate_DecList(declist, table, mca);
        h = LinkMulMCAHead(mca, 2, h, h1);

        deflist = NT_getChild(deflist, 1);
    }

    
    return h;
}


MCAHead translate_DecList(Node *n, SymbolTable table, MCA mca)
{
    assert(n->nodetype == DecList);
    Var v1 = NULL, v2 = NULL, v3 = NULL;
    Node* declist = n;
    Node *dec = NULL;
    char *decid;
    MCAHead h = NULL;
    MCAHead h1 = NULL, h2 = NULL, h3 = NULL;
    Symbol symbol;

    while(1)
    {
        dec = NT_getChild(declist, 0); 
        decid = getVarId(NT_getChild(dec, 0));
        symbol = LookUpSymbol(sts, NewSymbol(decid, NULL, -1)); 
        switch(symbol->type->tn)
        {
            case ARRAY:
                v1 = NewVar(VAR);
                v1->name = decid;
                v2 = NewVar(SIZE);
                v2->value = symbol->type->width; 
                h1 = NewMCAHead(mca, NewMidCode(C_DEC, v1, v2, NULL));
                break;
            case STRUCTURE:
                printf("%s", "Cannot translate: Code contains variables or parameters of structure type\n.");
                exit(0);
                break;
            case BASIC:
                break;
        }
        if(dec->seq == 1)
        {
            v1 = NewVar(VAR);
            v1->name = decid;
            v2 = NewVar(PLACE);
            v2->ttype = TEMP;
            h2 = translate_Exp(NT_getChild(dec, 2), table, v2, mca);
            h3 = NewMCAHead(mca, NewMidCode(C_ASSIGN, v1, v2, NULL));
        }
        h = LinkMulMCAHead(mca, 4, h, h1, h2, h3);

        if(declist->seq == 0)
            break;
        declist = NT_getChild(declist, 2);
    }
    return h;
}
