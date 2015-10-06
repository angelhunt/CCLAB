/*************************************************************************
	> File Name: nTree.h
	> Author: 
	> Mail: 
	> Created Time: 2015年10月06日 星期二 15时44分42秒
 ************************************************************************/

#ifndef _NTREE_H
#define _NTREE_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct ntList
{
  struct Node *head;
}ntList;

typedef struct Data{
    int i;
    float f;
    char* s;
} Data;


typedef struct Node  {
  bool term;
  char *name;

  Data data;
  
  
  
  struct Node *parent;
  struct ntList *children;
  struct Node *next;
  struct Node *pre;
}Node;

Node *NewNode(char *name, Data *data, bool term);
ntList *NewList();
extern bool LIsEmpty(ntList *l);
extern void clean(ntList *l);
extern void TreeInsert(Node *root, int nodeNum, ...);
extern void DFS(Node *rooti, unsigned hight);
#endif
