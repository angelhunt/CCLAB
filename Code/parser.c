/*************************************************************************
	> File Name: parser.c
	> Author: 
	> Mail: 
	> Created Time: 2015年10月07日 星期三 12时58分13秒
 ************************************************************************/

#include<stdio.h>
#include "parser.h"
#define NLINE 100
enum errortype et = B;
char errorstr[][40] =
{
    "Error type B at Line %d: Syntax error.\n",
    "Error type B at Line %d: Missing \";\".\n",
    "Error type B at Line %d: Missing \")\".\n",
    "Error type B at Line %d: Missing \"]\".\n",
    "Error type B at Line %d: Missing \";\".\n"
};
bool lineflag[NLINE];
/*
void error_handle(char *msg, Node *error, int lineno)
{
    isErrorOut = false;
    errorhandle = true;
    if(!lineflag[lineno])
    {
        printf("Error type B at Line %d: %s\n", lineno, msg);
        lineflag[lineno] = true;
    }
} 
*/
