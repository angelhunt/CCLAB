#include "MidCode.h"
int Var_Size = sizeof(struct Var_);
int CodeSU_Size = sizeof(struct CodeSU);
int MidCode_Size = sizeof(struct MidCode_);
int MCA_Size = sizeof(struct MCA_);
static int temp_no = 1;
static int label_no = 1;
Var NewVar(VART kind)
{
	Var t = malloc(Var_Size);
	t->kind = kind;
	switch (kind)
	{
	case VAR:
		break;
	case CON:
		break;
    case LABEL:
		t->var_no = label_no;
		label_no++;
		break;
    case TEMP:
		t->var_no = temp_no;
		temp_no++;
		break;
    case PLACE:
        break;
    case SIZE:
        break;
	}
    return t;
}


static void convertplace(Var t1)
{
    if(t1 != NULL && t1->kind == PLACE)
    {
        changevar(t1, NewVar(t1->ttype));
    }
}

MidCode NewMidCode(MIDCODET ct, Var t1, Var t2, Var t3)
{
    convertplace(t1);
    convertplace(t2);
    convertplace(t3);
    MidCode t = malloc(MidCode_Size);
    t->kind = ct;
    t->result = t1;
    t->arg1 = t2;
    t->arg2 = t3;
    return t;
}


MCA NewMCA()
{
    MCA t = malloc(MCA_Size);
    t->asize = 300;
    t->array = malloc(t->asize * CodeSU_Size);
    t->alloc = &t->array[0];
    t->unalloc = &t->array[1];


    int i = 0;
    for(i = 0; i < t->asize; i++)
    {
        t->array[i].ptrtoe = NULL;
        t->array[i].next = -1;
        t->array[i].last = -1;
        t->array[i].index = i;
    }



    t->alloc->next = 0;
    t->alloc->last = 0;
    t->unalloc->next = 2;
    t->unalloc->last = t->asize - 1;
    t->array[t->asize - 1].next = 1;
    t->array[t->asize - 1].last = t->asize - 2;
    for(i = 2; i < t->asize - 1; i++)
    {
        t->array[i].next = i + 1;
        t->array[i].last = i - 1;
    }

    return t;
}


void changevar(Var v1, Var v2)
{
    switch(v1->kind)
    {
    case LABEL:
		label_no--;
		break;
    case TEMP:
		temp_no--;
		break;
    }
    memcpy(v1, v2, Var_Size);
    //free(v2);
}


static char* GetVarStr(Var v)
{
    if(v == NULL)
        return NULL;
    char *temp = malloc(10);
    switch(v->kind)
    {
        case VAR:
            sprintf(temp, "%s", v->name);
            break;
        case CON:
            sprintf(temp, "#%d", v->var_no);
            break;
        case LABEL:
            sprintf(temp, "label%d", v->var_no);
            break;
        case TEMP:
            sprintf(temp, "t%d", v->var_no);
            break;
        case SIZE:
            sprintf(temp, "%d", v->value);
            break;
        case ADDR:
            sprintf(temp, "*%s", v->name);
            break;
        case GetADDR:
            sprintf(temp, "&%s", v->name);
            break;
    }
    return temp;
}
static void printMidCode(MidCode code)
{
    char *vstr1 = GetVarStr(code->result);
    char *vstr2 = GetVarStr(code->arg1);
    char *vstr3 = GetVarStr(code->arg2);
    switch(code->kind)
    {
        case C_LAB:
            printf("LABEL %s :\n", vstr1);
            break;
        case C_FUNC:
            printf("FUNCTION %s :\n", vstr1);
            break;
        case C_ASSIGN:
            printf("%s := %s\n", vstr1, vstr2);
            break;
        case C_ADD:
            printf("%s := %s + %s\n", vstr1, vstr2, vstr3);
            break;
        case C_SUB:
            printf("%s := %s - %s\n", vstr1, vstr2, vstr3);
            break;
        case C_MUL:
            printf("%s := %s * %s\n", vstr1, vstr2, vstr3);
            break;
        case C_DIV:
            printf("%s := %s / %s\n", vstr1, vstr2, vstr3);
            break;
        case C_GETADDR:
            printf("%s := &%s\n", vstr1, vstr2);
            break;
        case C_GETMEM:
            printf("%s := *%s\n", vstr1, vstr2);
            break;
        case C_SETMEM:
            printf("*%s := %s\n", vstr1, vstr2);
            break;
        case C_GOTO:
            printf("GOTO %s\n", vstr1);
            break;
        case C_IF:
            printf("IF %s %s %s GOTO %s\n", vstr1, code->op, vstr2, vstr3);
            break;
        case C_RETURN:
            printf("RETURN %s\n", vstr1);
            break;
        case C_DEC:
            printf("DEC %s %s\n", vstr1, vstr2);
            break;
        case C_ARG:
            printf("ARG %s\n", vstr1);
            break;
        case C_CALL:
            printf("%s := CALL %s\n", vstr1, vstr2);
            break;
        case C_PARAM:
            printf("PARAM %s\n", vstr1);
            break;
        case C_READ:
            printf("READ %s\n", vstr1);
            break;
        case C_WRITE:
            printf("WRITE %s\n", vstr1);
            break;
    }


    if(vstr1 != NULL)
    free(vstr1);
    if(vstr2 != NULL)
    free(vstr2);
    if(vstr3 != NULL)
    free(vstr3);
}


static int  MCAGetUnalloc(MCA a)
{
    assert(a->unalloc->next != a->unalloc->index);
    int index = a->unalloc->next;
    struct CodeSU *ptr = a->array + index;
    a->unalloc->next = ptr->next;
    a->array[ptr->next].last = a->unalloc->index;
    return index;
}

MCAHead NewMCAHead(MCA a, MidCode code)
{
    int index = MCAGetUnalloc(a);
    MCAHead h = &a->array[index];
    h->next = h->index;
    h->last = h->index;
    h->ptrtoe = code;
    return h;
}
static inline void Link2MCAHead(MCA a, MCAHead h1, MCAHead h2)
{
    if(h2 == NULL || h1 == NULL) return;
    CodeSU *last1 = &a->array[h1->last];
    CodeSU *last2 = &a->array[h2->last];
    last1->next = h2->index;
    h2->last = last1->index;
    last2->next = h1->index;
    h1->last = last2->index;
}

MCAHead LinkMulMCAHead(MCA a, int num, ...)
{
    va_list h_list;
    int count = 0;
    va_start(h_list, num);

    MCAHead h = va_arg(h_list, MCAHead);
//    if(h == NULL) return NULL;
    while(h == NULL && count < num - 1)
    {
        count ++;
        h = va_arg(h_list, MCAHead);
    }
    MCAHead t;
    for(; count < num - 1; count++)
    {
        t = va_arg(h_list, MCAHead);
        Link2MCAHead(a, h, t);
    }

    va_end(h_list);

    return h;
}
void printMCA(MCA a, MCAHead h)
{
    if(h == NULL) 
        return;
    printMidCode(h->ptrtoe);
    CodeSU* cu = &a->array[h->next];
    for(; cu != h; cu = &a->array[cu->next])
        printMidCode(cu->ptrtoe);
}



