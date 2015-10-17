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
extern bool LP_match;
extern bool LB_match;
extern bool LC_match;
extern bool SEMI_match;

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
    if(LP_match && LB_match && LC_match && SEMI_match)
    {
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
    else
    {
        if (LP_match == false)
        {
            errormsg = "Error type B at Line %d: Missing : \")\"\n";
            LP_match = true;
        }
        if (LB_match == false)
        {
            errormsg = "Error type B at Line %d: Missing : \"]\"\n";
            LB_match = true;
        }
        if (LC_match == false)
        {
            errormsg = "Error type B at Line %d: Missing : \"}\"\n";
            LC_match = true;
        }
        if (SEMI_match == false)
        {
            errormsg = "Error type B at Line %d: Missing : \";\"\n";
            SEMI_match = true;
        }
        printf(errormsg, yylloc.first_line);
    }
}
