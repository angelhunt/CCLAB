/*************************************************************************
  > File Name: nTree.c
  > Author: 
  > Mail: 
  > Created Time: 2015年09月29日 星期二 19时10分05秒
 ************************************************************************/

#ifndef _NTREE_H
#include "nTree.h"
#endif


static void DataAssign(Data *dst, Data *src)
{
    memcpy((void *)dst, (void *)src, sizeof(Data));
    if(src->s != NULL)
    {
        dst->s = malloc(strlen(src->s));
        strcpy(dst->s, src->s);
    }    
}



//build new node
extern Node *NewNode(char *name, Data *data, bool term)
{
    //alloc memory and initial children list
    Node *n = malloc(sizeof(Node));
    memset(n, 0, sizeof(Node));
    n->children = NewList();
    n->children->head->parent = n; 

    //assign
    n->name = malloc(strlen(name) + 1);
    strcpy(n->name, name);
    DataAssign(&n->data, data);
    n->term = term;
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


static void printNodeInfo(Node *n, unsigned hight)
{
    if(n->term)
    {
       if(strcmp(n->name, "ID") == 0 ||
        strcmp(n->name, "TYPE") == 0)
        printf("%*s: %s\n", (int)(hight * 2 + strlen(n->name)), n->name, n->data.s);
       else if(strcmp(n->name, "INT") == 0)
        printf("%*s: %d\n", (int)(hight * 2 + strlen(n->name)), n->name, n->data.i);   
       else if(strcmp(n->name, "FLOAT") == 0)
        printf("%*s: %f\n", (int)(hight * 2 + strlen(n->name)), n->name, n->data.f);
       else printf("%*s\n", (int)(hight * 2 + strlen(n->name)), n->name);
    }
    else
    {
        if(!LIsEmpty(n->children))
            printf("%*s (%d)\n", (int)(hight * 2 + strlen(n->name)), n->name, n->data.i);
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
/*
static void tree_BFS(Node *r)
{
    Node *p;
    p = r -> children -> head -> next;
    while(p != r -> children -> head)
        printf("%d ", p -> data);
    printf("\n")
}*/
