/*************************************************************************
	> File Name: SDD.c
	> Author: 
	> Mail: 
	> Created Time: 2015年10月21日 星期三 18时21分28秒
 ************************************************************************/

#ifndef _SDD_H
#define _SDD_H
#include<stdio.h>
#include "../nTree.h"
#include "../Symbol/SymbolTable.h"
#include "../Symbol/STStack.h"
#define SDDFUNCDEF(s) static Syn s(Node *n, Inh i)  
//#define DEBUG
typedef Syn (*SDDFunc)(Node *n, Inh);
extern void SDD(Node *root);


SDDFUNCDEF(Program_Handle); 
SDDFUNCDEF(ExtDefList_Handle);  
SDDFUNCDEF(ExtDef_Handle);
SDDFUNCDEF(ExtDecList_Handle);
SDDFUNCDEF(Specifier_Handle);
SDDFUNCDEF(StructSpecifier_Handle);
SDDFUNCDEF(OptTag_Handle); 
SDDFUNCDEF(Tag_Handle);
SDDFUNCDEF(VarDec_Handle);
SDDFUNCDEF(FunDec_Handle); 
SDDFUNCDEF(VarList_Handle); 
SDDFUNCDEF(ParamDec_Handle);
SDDFUNCDEF(CompSt_Handle);
SDDFUNCDEF(StmtList_Handle);   
SDDFUNCDEF(Stmt_Handle);
SDDFUNCDEF(DefList_Handle);
SDDFUNCDEF(Def_Handle);  
SDDFUNCDEF(DecList_Handle); 
SDDFUNCDEF(Dec_Handle);    
SDDFUNCDEF(Exp_Handle);
SDDFUNCDEF(Args_Handle);
#endif
