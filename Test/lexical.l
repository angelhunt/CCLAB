%{
#include "syntax.tab.h"
#include "parser.h"
#include "string.h"
    
int yycolumn = 1;
#define YY_USER_ACTION \
   yylloc.first_line = yylloc.last_line = yylineno; \
   yylloc.first_column = yycolumn; \
   yylloc.last_column = yycolumn + yyleng - 1;\
   yycolumn += yyleng;
%}




%option yylineno
letter       [a-zA-Z]
digit        [0-9]
delim        [ \r\t]
ws           {delim}+
ten          0|([1-9][0-9]*)
eight        0[1-7][0-7]*
sixteen      0[xX]([1-9a-f]*|[1-9A-F]*)



INT          {ten}|{eight}|{sixteen}
FLOAT        [1-9][0-9]*(\.[0-9]+)?([Ee][+-]?[0-9]+)?
ID           ({letter}|_)+({digit}|{letter}|_)*


SEMI         ;
COMMA        ,
ASSIGNOP     =
RELOP        >|<|<=|>=|==|!=
MINUS        -
PLUS         \+
STAR         \*
DIV          \/
AND          &&
OR           \|\|
DOT          \.
NOT          !
TYPE         int|float
LP           \(
RP           \)
LB           \[
RB           \]
LC           \{
RC           \}
STRUCT       struct
RETURN       return
IF           if
ELSE         else
WHILE        while

%%
"\n"        { yycolumn = 1; }
"//"      { char c = input();
 		    while (c != '\n')
 		    c = input ();
          }
 
"/\*"     { char c = input();
 		    while(1)
 		    { if(c == '*')
 			    {
                    c = input();
 			        if(c == '/')
 			        break;
                }
 			    else
 			        c = input();
            }
 		  }
 
{ws}     { /*noting*/ }
 
 
 
{INT}           {   Data data;
                    memset((void *)&data, 0, sizeof(Data));
                    data.i = atoi(yytext);
                    yylval.np = NewNode("INT", &data, true);
     		        return INT;
                }
 
{FLOAT}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.f = atof(yytext);
                    yylval.np = NewNode("FLOAT", &data, true);
     		        return FLOAT;
                }

{SEMI}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("SEMI", &data, true);
     		        return SEMI;
 }
          
{COMMA}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("COMMA", &data, true);
                    return COMMA;
                }
 
{ASSIGNOP}      {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("ASSIGNOP", &data, true);
 	                return ASSIGNOP;
                }
 
{MINUS}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("MINUS", &data, true);
 	                return MINUS;
                }
 
{PLUS}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("PLUS", &data, true);
 	                return PLUS;
                 }
 
{STAR}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("STAR", &data, true);
 	                return STAR;
                 }
 
{DIV}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("DIV", &data, true);
 	                return DIV;
                 }
 
{AND}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("AND", &data, true);
 	                return AND;
                 }
 
{OR}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("OR", &data, true);
 	                return OR;
                 }
 
{NOT}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("NOT", &data, true);
 	                return NOT;
                 }
 
{DOT}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("DOT", &data, true);
 	                return DOT;
                 }
 
{LP}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("LP", &data, true);
 	                return LP;
                 }
 
{RP}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("RP", &data, true);
 	                return RP;
                 }
 
{LB}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("LB", &data, true);
 	                return LB;
                 }
 
{RB}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("RB", &data, true);
 	                return RB;
                 }
 
{LC}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("LC", &data, true);
 	                return LC;
                 }
 
{RC}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("RC", &data, true);
 	                return RC;
                 }
 
{STRUCT}        {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("STRUCT", &data, true);
 	                return STRUCT;
                 }
 
{IF}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("IF", &data, true);
 	                return IF;
                 }
 
{RETURN}        {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("RETURN", &data, true);
 	                return RETURN;
                 }
 
{ELSE}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("ELSE", &data, true);
                    return ELSE;
                 }
 
{WHILE}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("WHILE", &data, true);
                    return WHILE;
                 }
 
{RELOP}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("RELOP", &data, true);
                    return RELOP;
                 }
 
{TYPE}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("TYPE", &data, true);
                    return TYPE;
                 }
 
EOF             {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("EOF", &data, true);
                    return true;
                 }
 
{ID}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("ID", &data, true);
                    return ID;
                 }
 
.               {  
                    Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    yylval.np = NewNode("UNKNOWN", &data, true);
                    return UNKNOWN;
                 }
%%
