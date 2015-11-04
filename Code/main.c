#include <stdio.h>
#include "syntax.tab.h"
#include "nTree.h"
#include "parser.h"
extern FILE* yyin;
extern int yydebug;
extern int yylineno;
extern void yyrestart (FILE *input_file  );
extern bool error_exist;

int main(int argc, char ** argv)
{
    if (argc <= 1) return 1;
    int i;
    FILE* f;
    for(i = 1; i < argc; i++)
    {
        f = fopen(argv[i], "r");
        if(!f)
        {
            perror(argv[i]);
            return 1;
        }
        yylineno = 1;
        yyrestart(f);
//    yydebug = 1;

        yyparse();
    }
    return 0;
}

void yyerror(char* msg) {
    char *errormsg = errorstr[B];
    if(error_exist == false)
       error_exist = true;
    if(yylval.np->nodetype == UNKNOWN)
    {
        errormsg = "Error type A at Line %d: Mysterious character \"%s\"\n";
        printf(errormsg, yylloc.first_line, yylval.np->data.s);
    }
    else
    {
        errormsg = errorstr[et];
        printf(errormsg, yylloc.first_line);
    }
}
