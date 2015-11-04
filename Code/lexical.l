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
                    data.s = yytext;
                    yylval.np = NewNode(INT, -1 , &data);
     		        return INT;
                }
 
{FLOAT}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.f = atof(yytext);
                    data.lineno = yylineno;
                    data.s = yytext;
                    yylval.np = NewNode(FLOAT, -1 , &data);
     		        return FLOAT;
                }

{SEMI}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(SEMI, -1 , &data);
     		        return SEMI;
 }
          
{COMMA}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(COMMA, -1 , &data);
                    return COMMA;
                }
 
{ASSIGNOP}      {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(ASSIGNOP, -1 , &data);
 	                return ASSIGNOP;
                }
 
{MINUS}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(MINUS, -1 , &data);
 	                return MINUS;
                }
 
{PLUS}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(PLUS, -1 , &data);
 	                return PLUS;
                 }
 
{STAR}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(STAR, -1 , &data);
 	                return STAR;
                 }
 
{DIV}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(DIV, -1 , &data);
 	                return DIV;
                 }
 
{AND}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(AND, -1 , &data);
 	                return AND;
                 }
 
{OR}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(OR, -1 , &data);
 	                return OR;
                 }
 
{NOT}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(NOT, -1 , &data);
 	                return NOT;
                 }
 
{DOT}           {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(DOT, -1 , &data);
 	                return DOT;
                 }
 
{LP}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(LP, -1 , &data);
 	                return LP;
                 }
 
{RP}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(RP, -1 , &data);
 	                return RP;
                 }
 
{LB}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(LB, -1 , &data);
 	                return LB;
                 }
 
{RB}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(RB, -1 , &data);
 	                return RB;
                 }
 
{LC}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(LC, -1 , &data);
 	                return LC;
                 }
 
{RC}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(RC, -1 , &data);
 	                return RC;
                 }
 
{STRUCT}        {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(STRUCT, -1 , &data);
 	                return STRUCT;
                 }
 
{IF}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(IF, -1 , &data);
 	                return IF;
                 }
 
{RETURN}        {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(RETURN, -1 , &data);
 	                return RETURN;
                 }
 
{ELSE}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(ELSE, -1 , &data);
                    return ELSE;
                 }
 
{WHILE}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(WHILE, -1 , &data);
                    return WHILE;
                 }
 
{RELOP}         {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(RELOP, -1 , &data);
                    return RELOP;
                 }
 
{TYPE}          {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(TYPE, -1 , &data);
                    return TYPE;
                 }
 
EOF             {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(EOF, -1 , &data);
                    return true;
                 }
 
{ID}            {   Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(ID, -1 , &data);
                    return ID;
                 }
 
.               {  
                    Data data;  
                    memset((void *)&data, 0, sizeof(Data));
                    data.s = yytext;
                    data.lineno = yylineno;
                    yylval.np = NewNode(UNKNOWN, -1 , &data);
                    return UNKNOWN;
                 }
%%
