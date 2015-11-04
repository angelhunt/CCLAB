/*************************************************************************
	> File Name: convenience.c
	> Author: 
	> Mail: 
	> Created Time: 2015年10月31日 星期六 12时06分00秒
 ************************************************************************/

#include<stdio.h>
#include "convenience.h"
void *CONVENIENCE_malloc(unsigned size)
{
    void* t = malloc(size);
    if(t == NULL)
    {
        printf("malloc error!\n");
        exit(-1);
    }
    memset(t, 0, size);
    return t;
}
