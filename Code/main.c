#include <stdio.h>
#include "syntax.tab.h"
#include "nTree.h"
#include "parser.h"
extern FILE* yyin;
extern int yydebug;
extern void yyrestart (FILE *input_file  );
extern bool error_exist;
extern void error_handle(char *msg, Node *error, int lineno);
extern bool isErrorOut;
extern bool errorhandle;

int main(int argc, char ** argv)
{
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if(!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
//    yydebug = 1;

    yyparse();

    return 0;
}

void yyerror(char* msg) {
    char *errormsg = "Error type B at Line %d: syntax error\n";
    if(error_exist == false)
       error_exist = true;
    if(strcmp(yylval.np->name, "UNKNOWN") == 0)
    {
        errormsg = "Error type A at Line %d: Mysterious character \"%s\"\n";
        printf(errormsg, yylloc.first_line, yylval.np->data.s);
    }
    else
    {
    printf(errormsg, yylloc.first_line);
    }
}
