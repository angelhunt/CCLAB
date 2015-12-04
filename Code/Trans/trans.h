/*************************************************************************
	> File Name: tran.h
	> Author: 
	> Mail: 
	> Created Time: 2015年11月13日 星期五 20时58分51秒
 ************************************************************************/

#ifndef _TRAN_H
#define _TRAN_H
//#define debug
#include "MidCode.h"
#include "../SDD/SDD.h"
#include "../Symbol/SymbolTable.h"
#include "../nTree.h"
#include<stdio.h>
extern MCAHead translate_Exp(Node *n, SymbolTable table, Var place, MCA mca);
extern MCAHead translate_Stmt(Node* n, SymbolTable table, MCA mca);
extern MCAHead translate_Cond(Node *n, Var lt, Var lf, SymbolTable table, MCA mca);
extern MCAHead translate_Args(Node *n, SymbolTable table, Var* vlist, int *len, MCA mca);
extern MCAHead translate_CompSt(Node *n, SymbolTable table, MCA mca);
extern MCAHead translate_Program(Node *n, SymbolTable table, MCA mca);
extern MCAHead translate_DecList(Node *n, SymbolTable table, MCA mca);
extern MCAHead translate_FunDec(Node *n, SymbolTable table, MCA mca);
extern MCAHead translate_DefList(Node *n, SymbolTable table, MCA mca);
#endif
