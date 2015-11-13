/*************************************************************************
	> File Name: parser.h
	> Author: 
	> Mail: 
	> Created Time: 2015年10月06日 星期二 18时22分09秒
 ************************************************************************/

#ifndef _NTREE_H
#include "nTree.h"
#endif
#ifndef _PARSER_H
#define _PARSER_H
#include "syntax.tab.h"

//extern bool isErrorOut;
//extern bool errorhandle;
//extern void error_handle(char *msg, Node *error, int lineno);
enum errortype
{
    B,
    MISSSEMI,
    MISSRP,
    MISSRB,
    MISSRC
};

extern enum errortype et;
extern char errorstr[][40];

#endif
