/*************************************************************************
  > File Name: nTree.c
  > Author: 
  > Mail: 
  > Created Time: 2015年09月29日 星期二 19时10分05秒
 ************************************************************************/

#include "nTree.h"
char nodetypestr[][20] = 
{
    "INT", "FLOAT", "ID", "SEMI", "COMMA", "DOT",
    "ASSIGNOP", "RELOP", "MINUS", "PLUS", "STAR",
    "DIV", "AND", "OR", "NOT", "TYPE", "STRUCT",
    "LP", "RP", "LB", "RB", "LC", "RC", "RETURN",
    "IF", "ELSE", "WHILE", "UNKNOWN","LOWER_THAN_ELSE",
    "NEG",
    "Program", "ExtDefList", "ExtDef", "ExtDecList",
    "Specifier", "StructSpecifier", "OptTag", "Tag",
    "VarDec", "FunDec", "VarList","ParamDec", "CompSt",
    "StmtList", "Stmt", "DefList", "Def", "DecList",
    "Dec", "Exp", "Args"
};

static void DataAssign(Data *dst, Data *src)
{
    if(src == NULL)
     { 
         dst = NULL;
         return;
     }
    memcpy((void *)dst, (void *)src, sizeof(Data));
    if(src->s != NULL)
    {
        dst->s = malloc(strlen(src->s));
        strcpy(dst->s, src->s);
    }    
}



//build new node
extern Node *NewNode(NODETYPE nodetype, int seq, Data *data)
{
    //alloc memory and initial children list
    Node *n = malloc(sizeof(Node));
    memset(n, 0, sizeof(Node));
    n->children = NewList();
    n->children->head->parent = n; 

    //assign
    n->nodetype = nodetype;
    n->seq = seq;
    n->syn = NewSyn();
    n->inh = NewInh();
    DataAssign(&n->data, data);
    return n;
}

//Boild new 
extern ntList *NewList()
{
    ntList *l;
    l = malloc(sizeof(ntList));
    memset(l, 0, sizeof(ntList));
    l->head = malloc(sizeof(Node));
    memset(l->head, 0, sizeof(Node));
    l->head->next = l->head;
    l->head->pre = l->head;
    return l;
}


//Insert a node to list
static void Insert(ntList *l, Node *n)
{
    l->head->pre->next = n;
    n->pre = l->head->pre;
    n->next = l->head;
    l->head->pre = n;

    n->parent = l->head->parent;
}




extern void clean(ntList *l)
{
    Node *lp = l->head->next;
    Node *temp;
    while(lp != l->head)
    {
        temp = lp->next;
        Node *lp = temp;
        free(lp);
        lp = temp;
    }
    free(l->head);
}



extern bool LIsEmpty(ntList *l)
{
    if(l == NULL)
    {
        printf("LIsEmpty get NULL\n");
        exit(0);
    }
    return l->head->next == l->head;
}







//Tree
extern void TreeInsert(Node *root, int nodeNum, ...)
{
    va_list node_list;
    int count = 0;
    va_start(node_list, nodeNum);

    for(count = 0; count < nodeNum; count++)
        Insert(root -> children, va_arg(node_list, Node*));

    va_end(node_list);
}


static inline bool isTerm(Node *n)
{
    return (INT <= n->nodetype) && (n->nodetype <= NEG);
}
static void printNodeInfo(Node *n, unsigned hight)
{
    NODETYPE ntype = n->nodetype;
    char *typestr = nodetypestr[ntype - OFFSETTYPETOSTR]; 
    int typestrlen = strlen(typestr);
    if(isTerm(n))
    {
       if(ntype == ID || ntype == TYPE)
        printf("%*s: %s\n", (int)(hight * 2 + typestrlen), typestr, n->data.s);
       else if(ntype == INT)
        printf("%*s: %d\n", (int)(hight * 2 + typestrlen), typestr, n->data.i);   
       else if(ntype == FLOAT)
        printf("%*s: %f\n", (int)(hight * 2 + typestrlen), typestr, n->data.f);
       else printf("%*s\n", (int)(hight * 2 + typestrlen), typestr);
    }
    else
    {
        if(!LIsEmpty(n->children))
            printf("%*s (%d)\n", (int)(hight * 2 + typestrlen), typestr, n->data.lineno);
    }
}


void DFS(Node *root, unsigned hight)
{
    if(root == NULL)
        return;
    printNodeInfo(root, hight);
    if(LIsEmpty(root->children))
        return;
    Node *t = root -> children -> head -> next;
    while(t != root -> children -> head)
    {
        DFS(t, hight + 1);
        t = t->next;
    }
}

void Get_Node_Str(Node *n, char *str, int len)
{
    if(n == NULL)
        return;
    Node *curent = n;
    if(isTerm(n))
        strncat(str, n->data.s, len - strlen(str));
    Node *t = n -> children -> head -> next;
    while(t != n -> children -> head)
    {
        Get_Node_Str(t, str, len);
        t = t->next;
    }
}

char *getArgsStr(Node *n)
{
    if(n->nodetype != Args)
        return NULL;
    char *str = CONVENIENCE_malloc(100);
    Node* m = n;
    bool end = false;
    bool first = true;
    Node *child;
    strncat(str, "(", 100 - strlen(str));
    while(!end)
    {
        if(!first)
            strncat(str, ", ", 100 - strlen(str));
        else 
            first = false;
        child = m->children->head->next;
        Type t = child->syn->SType;
        switch(t->tn)
        {
            case BASIC:
                if(t->tv->basic == INT) strncat(str, "int", 100 - strlen(str));
                if(t->tv->basic == FLOAT) strncat(str, "float", 100 - strlen(str));
                break;
            case STRUCTURE:
                 strncat(str, "struct ", 100 - strlen(str));
                strncat(str, t->tv->structure->name, 100 - strlen(str));
                break;
        }
        switch(m->seq)
        {
            case 0:
                m = child->next->next;
                break;
            case 1:
                end = true;
                break;
        }
    }
    strncat(str, ")", 100 - strlen(str));
    return str;

}


char *GetFuncStr(Node *n)
{
    if(n->nodetype != FunDec)
        return NULL;
    char *str = CONVENIENCE_malloc(100);
    Node *child = n->children->head->next;
    strncat(str, child->data.s, 100 - strlen(str));
    child = child->next->next;
    char *temp = GetVarListStr(child);
    strncat(str, child->data.s, 100 - strlen(str));
    free(temp);
    return str;
}
char * GetVarListStr(Node *n)
{
    if(n->nodetype != VarList)
        return NULL;
    char *str = CONVENIENCE_malloc(100);
    Node *m = n;
    bool flag = true;
    Node *child;
    char *temp;
    while(flag)
    {
        child = m->children->head->next;
        switch(m->seq)
        {
            case 0:
                child = child->children->head->next;
                temp = GetSpecifierStr(child);
                strncat(str, temp, 100 - strlen(str));
                free(temp);
                m = child->next->next;
            case 1:
                child = child->children->head->next;
                temp = GetSpecifierStr(child);
                strncat(str, temp, 100 - strlen(str));
                free(temp);
                flag = false;
        }
    }
    return str;
}
char* GetSpecifierStr(Node *n)
{
    if(n->nodetype != Specifier)
        return NULL;
    char *str = CONVENIENCE_malloc(30);
    Node *child = n->children->head->next;
    switch(n->seq)
    {
        case 0:
           strncat(str, child->data.s, 30 - strlen(str));
           break;
        case 1:
           child = child->children->head->next->next;
           strncat(str, "struct", 30 - strlen(str));
           strncat(str, child->data.s, 30 - strlen(str));
           break;
    }
    return str;
}
/*
static void tree_BFS(Node *r)
{
    Node *p;
    p = r -> children -> head -> next;
    while(p != r -> children -> head)
        printf("%d ", p -> data);
    printf("\n")
}*/
