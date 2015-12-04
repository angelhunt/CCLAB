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
#include "Symbol/type.h"
#include "syntax.tab.h"
#include "Symbol/Symbol.h"
#include "Trans/MidCode.h"
#define OFFSETTYPETOSTR 258
typedef struct ntList
{
  struct Node *head;
}ntList;
typedef enum NODETYPE NODETYPE;
enum NODETYPE{
/*    INT = 258, FLOAT = 259, ID = 260, SEMI = 261,
    COMMA = 262, DOT = 263, ASSIGNOP = 264, RELOP = 265,
    MINUS = 266, PLUS = 267, STAR = 268, DIV = 269,
    AND = 270, OR = 271, NOT = 272, TYPE = 273, STRUCT = 274,
    LP = 275, RP = 276, LB = 277, RB = 278, LC = 279, RC = 280,
    RETURN = 281, IF = 282, ELSE = 283, WHILE = 284, UNKNOWN = 285,
    LOWER_THAN_ELSE = 286, NEG = 287,*/
    Program = 288, ExtDefList = 289, ExtDef = 290, 
    ExtDecList = 291,Specifier = 292, StructSpecifier = 293,
    OptTag = 294, Tag = 295,VarDec = 296, FunDec = 297,
    VarList = 298, ParamDec = 299, CompSt = 300,
    StmtList = 301, Stmt = 302, DefList = 303, Def = 304, 
    DecList = 305, Dec = 306, Exp = 307, Args = 308
};
typedef struct Data{
    int i;
    float f;
    char* s;
    int lineno;
} Data;

typedef struct SynInh_* Syn;
typedef struct SynInh_* Inh;

typedef struct Node  {
  NODETYPE nodetype;
  Data data;
  Syn syn;
  Inh inh;
  
  int seq;                     //产生式序号
  struct Node *parent;
  struct ntList *children;
  struct Node *next;
  struct Node *pre;
}Node;

struct SynInh_
{
    Type SType;    
    int value;
    Var addr;
    Symbol symbol;
};


static inline Syn NewSyn()
{
    Syn s = malloc(sizeof(struct SynInh_));
    return s;
}
static inline Inh NewInh()
{
    Inh i = (Inh)malloc(sizeof(struct SynInh_));
    return i;
}

static inline void SynAssign(Syn s1, Syn s2)
{ 
    if(s2 != NULL)
    {
        s1->SType = s2->SType;
    }
}

static inline Node* NT_getChild(Node *a, int n)
{
    Node* child = a->children->head->next;
    int i = 0;
    for(i = 0; i < n; i++)
        child = child->next;
    return child;
}

extern char nodetypestr[][20];
Node *NewNode(NODETYPE nodetype, int seq, Data *data);
ntList *NewList();
extern bool LIsEmpty(ntList *l);
extern void clean(ntList *l);
extern void TreeInsert(Node *root, int nodeNum, ...);
extern void DFS(Node *rooti, unsigned hight);
extern void Get_Node_Str(Node *n, char *str, int len);
extern char *GetSpecifierStr(Node *n);
extern char *GetVarListStr(Node *n);
extern char *GetFuncStr(Node *n);
extern char *getArgsStr(Node *n);
extern char *getVarId(Node *n);
extern Node *getVarDecParent(Node *n);

#endif
