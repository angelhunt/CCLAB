%locations
%{
#include "lex.yy.c"
#include <stdio.h>
#include "parser.h"
#include "nTree.h"
#include "SDD/SDD.h"
bool error_exist = false;
/*bool isErrorOut = false;
bool le = false;
*/
%}

%union 
{
    struct Node* np;
};
/*declared tokens*/
%token <np> INT
%token <np> FLOAT 
%token <np> ID
%token <np> SEMI COMMA DOT
%token <np> ASSIGNOP RELOP 
%token <np> MINUS PLUS STAR DIV AND OR NOT
%token <np> TYPE STRUCT 
%token <np> LP RP LB RB LC RC
%token <np> RETURN IF ELSE WHILE
%token <np> UNKNOWN 

%type <np> Program  ExtDefList ExtDef ExtDecList    
%type <np> Specifier StructSpecifier OptTag Tag
%type <np> VarDec FunDec VarList ParamDec 
%type <np> CompSt StmtList Stmt
%type <np> DefList Def DecList Dec
%type <np> Exp Args 
%type <np> error

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGNOP
%left  OR
%left  AND 
%left  RELOP
%left  PLUS MINUS
%left  STAR DIV
%right NOT NEG
%left  RP LP RB LB DOT
%%
/*Highi-level*/
Program : ExtDefList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Program, 0, &data); 
        TreeInsert($$, 1, $1);
        #ifdef DEBUG
        if(error_exist == false)
            DFS($$, 0);
        #endif
        if(error_exist == false)
            SDD($$);
        }
    ;

ExtDefList : ExtDef ExtDefList { 
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDefList, 0, &data);
        TreeInsert($$, 2, $1, $2);
        }
    | { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        $$ = NewNode(ExtDefList, 1, &data);
        }
    ;


ExtDef : Specifier ExtDecList { et = MISSSEMI; }SEMI {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDef, 0, &data);
        TreeInsert($$, 3, $1, $2, $4);
       }
    | Specifier { et = MISSSEMI; }SEMI {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDef, 1, &data); 
        TreeInsert($$, 2, $1, $3);
        }
    | Specifier FunDec CompSt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDef, 2, &data); 
        TreeInsert($$, 3, $1, $2, $3);
        }
    | Specifier FunDec SEMI {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDef, 2, &data); 
        TreeInsert($$, 3, $1, $2, $3);
        }
    ;

ExtDecList : VarDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDecList, 0, &data);
        TreeInsert($$, 1, $1);
        } 
    | VarDec COMMA ExtDecList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ExtDecList, 1, &data);
        TreeInsert($$, 3, $1, $1, $3);
        }
    ;




/*Specifier*/
Specifier : TYPE {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Specifier, 0, &data); 
        TreeInsert($$, 1, $1);
        }
    | StructSpecifier {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Specifier, 1, &data);
        TreeInsert($$, 1, $1);
        }
    ;

StructSpecifier : STRUCT OptTag LC DefList {et = MISSRC;}RC {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(StructSpecifier, 0, &data); 
        TreeInsert($$, 5, $1, $2, $3, $4, $6);
        }
    | STRUCT Tag {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(StructSpecifier, 1, &data);
        TreeInsert($$, 2, $1, $2);
        }   
    ;

OptTag : ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(OptTag, 0, &data);
        TreeInsert($$, 1, $1);
        }
    | { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        $$ = NewNode(OptTag, 1, &data);
        } 
    ;

Tag : ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Tag, 0, &data);
        TreeInsert($$, 1, $1);
        }
    ;




/*Declarators*/
VarDec : ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(VarDec, 0, &data);
        TreeInsert($$, 1, $1);
        }
    | VarDec LB INT {et = MISSRB; }RB {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(VarDec, 1, &data);
        TreeInsert($$, 4, $1, $2, $3, $5);
        }
    ;

FunDec : ID LP VarList { et = MISSRP; }RP {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(FunDec, 0, &data);
        TreeInsert($$, 4, $1, $2, $3, $5);
        et = B;
       }
    | ID LP { et = MISSRP; }RP {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(FunDec, 1, &data);
        TreeInsert($$, 3, $1, $2, $4);
        et = B;
    }
    ;

VarList : ParamDec COMMA VarList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(VarList, 0, &data);
        TreeInsert($$, 3, $1, $2, $3);
        }
    | ParamDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(VarList, 1, &data);
        TreeInsert($$, 1, $1);
    }
    ; 

ParamDec : Specifier VarDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(ParamDec, 0, &data);
        TreeInsert($$, 2, $1, $2);
         }
    ;




/*Statements*/
CompSt : LC DefList StmtList {et = MISSRC; }RC {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @3.first_line;
        $$ = NewNode(CompSt, 0, &data);
        TreeInsert($$, 4, $1, $2, $3, $5);
        et = B;
       }
    |   error RC
    ;

StmtList : Stmt StmtList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(StmtList, 0, &data);
        TreeInsert($$, 2, $1, $2);
    }
    | { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        $$ = NewNode(StmtList, 1, &data);
        }
    ;


Stmt : Exp {et = MISSSEMI; }SEMI {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Stmt, 0, &data);
        TreeInsert($$, 2, $1, $3);
     }
    | CompSt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Stmt, 1, &data);
        TreeInsert($$, 1, $1);
        }
    | RETURN Exp {et = MISSSEMI; }SEMI{
        et = B; 
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Stmt, 2, &data);
        TreeInsert($$, 3, $1, $2, $4);
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Stmt, 3, &data);
        TreeInsert($$, 5, $1, $2, $3, $4, $5);
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Stmt, 4, &data);
        TreeInsert($$, 7, $1, $2, $3, $4, $5, $6, $7);
    }
    | WHILE LP Exp { et = MISSRP; }RP { et = B; }Stmt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Stmt, 5, &data);
        TreeInsert($$, 5, $1, $2, $3, $5, $7);
    }
    | error SEMI
    ;




/*Local Definitions*/
DefList : Def DefList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(DefList, 0, &data);
        TreeInsert($$, 2, $1, $2);
    }
    | { Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = -1;
        $$ = NewNode(DefList, 1, &data);
        }
    ;

Def : Specifier DecList { et = MISSSEMI; }SEMI {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Def, 0, &data);
        TreeInsert($$, 3, $1, $2, $4);
    }
    ;

DecList : Dec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(DecList, 0, &data);
        TreeInsert($$, 1, $1);
        }
    | Dec COMMA DecList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(DecList, 1, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    ;

Dec : VarDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Dec, 0, &data);
        TreeInsert($$, 1, $1);
        
    }
    | VarDec ASSIGNOP Exp{
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Dec, 1, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    ;




/*Expressions*/ 
Exp : Exp ASSIGNOP Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 0, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp AND Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 1, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp OR Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 2, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp RELOP Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 3, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp PLUS Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 4, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp MINUS Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 5, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp STAR Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 6, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp DIV Exp {
       Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 7, &data);
        TreeInsert($$, 3, $1, $2, $3);
    } 
    | LP Exp {et = MISSRP; }RP {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 8, &data);
        TreeInsert($$, 3, $1, $2, $4);
    }
    | MINUS Exp %prec NEG {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 9, &data);
        TreeInsert($$, 2, $1, $2);
    }
    | NOT Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 10, &data);
        TreeInsert($$, 2, $1, $2);
    }
    | ID LP Args { et = MISSRP; }RP {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 11, &data);
        TreeInsert($$, 4, $1, $2, $3, $5);
    }
    | ID LP { et = MISSRP; }RP {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 12, &data);
        TreeInsert($$, 3, $1, $2, $4);
    } 
    | Exp LB Exp { et = MISSRB; }RB {
        et = B;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 13, &data);
        TreeInsert($$, 4, $1, $2, $3, $5);
    } 
    | Exp DOT ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 14, &data);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 15, &data);
        TreeInsert($$, 1, $1);
    }
    | INT {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 16, &data);
        TreeInsert($$, 1, $1);
    }
    |FLOAT {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Exp, 17, &data);
        TreeInsert($$, 1, $1);
    }
    ;

Args : Exp COMMA Args {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Args, 0, &data);
        TreeInsert($$, 3, $1, $2, $3);
     }
    | Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.lineno = @1.first_line;
        $$ = NewNode(Args, 1, &data);
        TreeInsert($$, 1, $1);
    }
    ;


%%
