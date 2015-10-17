%locations
%{
#include "lex.yy.c"
#include <stdio.h>
#include "parser.h"
bool error_exist = false;
bool isErrorOut = false;
bool errorhandle = false;
bool LP_match = true;
bool LB_match = true;
bool LC_match = true;
bool SEMI_match = true;
%}

%define api.value.type {struct DATATYPE}

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
        data.i = @1.first_line;
        $$ = NewNode("Program", &data, false); 
        TreeInsert($$, 1, $1);
        if(error_exist == false)
        DFS($$, 0);
        }
    ;

ExtDefList : {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = -1;
        $$ = NewNode("ExtDefList", &data, false);
        }
    | ExtDef ExtDefList { 
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDefList", &data, false);
        TreeInsert($$, 2, $1, $2);
        }
    ;


ExtDef : Specifier ExtDecList{SEMI_match = false;} SEMI {
       SEMI_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDef", &data, false);
        TreeInsert($$, 3, $1, $2, $4);
       }
    | Specifier {SEMI_match = false;} SEMI {
        SEMI_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDef", &data, false); 
        TreeInsert($$, 2, $1, $3);
        }
    | Specifier FunDec CompSt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDef", &data, false); 
        TreeInsert($$, 3, $1, $2, $3);
        }
    ;

ExtDecList : VarDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDecList", &data, false);
        TreeInsert($$, 1, $1);
        } 
    | VarDec COMMA ExtDecList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDecList", &data, false);
        TreeInsert($$, 3, $1, $1, $3);
        }
    ;




/*Specifier*/
Specifier : TYPE {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Specifier", &data, false); 
        TreeInsert($$, 1, $1);
        }
    | StructSpecifier {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Specifier", &data, false);
        TreeInsert($$, 1, $1);
        }
    ;

StructSpecifier : STRUCT OptTag LC {LC_match = false;}DefList RC {
        LC_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("StructSpecifier", &data, false); 
        TreeInsert($$, 5, $1, $2, $3, $5, $6);
        }
    | STRUCT Tag {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("StructSpecifier", &data, false);
        TreeInsert($$, 2, $1, $2);
        }   
    ;

OptTag : {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = -1;
        $$ = NewNode("OptTag", &data, false);
        } 
    | ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("OptTag", &data, false);
        TreeInsert($$, 1, $1);
        }
    ;

Tag : ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Tag", &data, false);
        TreeInsert($$, 1, $1);
        }
    ;




/*Declarators*/
VarDec : ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("VarDec", &data, false);
        TreeInsert($$, 1, $1);
        }
    | VarDec LB {LB_match = false;}INT RB {
        LB_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("VarDec", &data, false);
        TreeInsert($$, 4, $1, $2, $4, $5);
        }
    ;

FunDec : ID LP {LP_match = false;}VarList RP {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("FunDec", &data, false);
        TreeInsert($$, 4, $1, $2, $4, $5);
       }
    | ID LP {LP_match = false;}RP {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("FunDec", &data, false);
        TreeInsert($$, 3, $1, $2, $4);
    }
    ;

VarList : ParamDec COMMA VarList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("VarList", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
        }
    | ParamDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("VarList", &data, false);
        TreeInsert($$, 1, $1);
    }
    ; 

ParamDec : Specifier VarDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ParamDec", &data, false);
        TreeInsert($$, 2, $1, $2);
         }
    ;




/*Statements*/
CompSt : LC {LC_match = false;}DefList StmtList RC {
        LC_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @3.first_line;
        $$ = NewNode("CompSt", &data, false);
        TreeInsert($$, 4, $1, $3, $4, $5);
       }
    |   error RC
    ;

StmtList : {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = -1;
        $$ = NewNode("StmtList", &data, false);
        }
    | Stmt StmtList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("StmtList", &data, false);
        TreeInsert($$, 2, $1, $2);
    }
    ;


Stmt : Exp {SEMI_match = false;}SEMI {
        SEMI_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 2, $1, $3);
     }
    | CompSt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 1, $1);
        }
    | RETURN Exp {SEMI_match = false;}SEMI{
        SEMI_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 3, $1, $2, $4);
    }
    | IF LP Exp {LP_match = false;} RP Stmt %prec LOWER_THAN_ELSE {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 5, $1, $2, $3, $5, $6);
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 7, $1, $2, $3, $4, $5, $6, $7);
    }
    | WHILE LP {LP_match = false;}Exp RP Stmt {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 5, $1, $2, $4, $5, $6);
    }
    | error SEMI
    ;




/*Local Definitions*/
DefList : {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = -1;
        $$ = NewNode("DefList", &data, false);
        }
    | Def DefList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("DefList", &data, false);
        TreeInsert($$, 2, $1, $2);
    }
    ;

Def : Specifier DecList {SEMI_match = false;} SEMI {
        SEMI_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Def", &data, false);
        TreeInsert($$, 3, $1, $2, $4);
    }
    ;

DecList : Dec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("DecList", &data, false);
        TreeInsert($$, 1, $1);
        }
    | Dec COMMA DecList {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("DecList", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    ;

Dec : VarDec {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Dec", &data, false);
        TreeInsert($$, 1, $1);
        
    }
    | VarDec ASSIGNOP Exp{
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Dec", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    ;




/*Expressions*/ 
Exp : Exp ASSIGNOP Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp AND Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp RELOP Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp PLUS Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp MINUS Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp STAR Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | Exp DIV Exp {
       Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    } 
    | LP {LP_match = false;}Exp RP {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $3, $4);
    }
    | MINUS Exp %prec NEG {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 2, $1, $2);
    }
    | NOT Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 2, $1, $2);
    }
    | ID LP {LP_match = false;}Args RP {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 4, $1, $2, $4, $5);
    }
    | ID LP {LP_match = false;}RP {
        LP_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $4);
    } 
    | Exp LB {LB_match = false;}Exp RB {
        LB_match = true;
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 4, $1, $2, $4, $5);
    } 
    | Exp DOT ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | ID {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 1, $1);
    }
    | INT {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 1, $1);
    }
    |FLOAT {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 1, $1);
    }
    | error RB
    ;

Args : Exp COMMA Args {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Args", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
     }
    | Exp {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Args", &data, false);
        TreeInsert($$, 1, $1);
    }


%%
