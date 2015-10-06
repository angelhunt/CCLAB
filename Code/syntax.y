%locations
%{
#include "lex.yy.c"
#include <stdio.h>
#include "parser.h"
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


%type <np> Program  ExtDefList ExtDef ExtDecList    
%type <np> Specifier StructSpecifier OptTag Tag
%type <np> VarDec FunDec VarList ParamDec 
%type <np> CompSt StmtList Stmt
%type <np> DefList Def DecList Dec
%type <np> Exp Args 

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

ExtDef : Specifier ExtDecList SEMI {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDef", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
       }
    | Specifier SEMI {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("ExtDef", &data, false); 
        TreeInsert($$, 2, $1, $2);
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

StructSpecifier : STRUCT OptTag LC DefList RC {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("StructSpecifier", &data, false); 
        TreeInsert($$, 5, $1, $2, $3, $4, $5);
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
    | VarDec LB INT RB {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("VarDec", &data, false);
        TreeInsert($$, 4, $1, $2, $3, $4);
        }
    ;

FunDec : ID LP VarList RP {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("FunDec", &data, false);
        TreeInsert($$, 4, $1, $2, $3, $4);
       }
    | ID LP RP {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("FunDec", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
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
CompSt : LC DefList StmtList RC {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("CompSt", &data, false);
        TreeInsert($$, 4, $1, $2, $3, $4);

       }
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

Stmt : Exp SEMI {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 2, $1, $2);
     }
    | CompSt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 1, $1);
        }
    | RETURN Exp SEMI{
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 5, $1, $2, $3, $4, $5);
    }
    | IF LP Exp RP Stmt ELSE Stmt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 7, $1, $2, $3, $4, $5, $6, $7);
    }
    | WHILE LP Exp RP Stmt {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Stmt", &data, false);
        TreeInsert($$, 5, $1, $2, $3, $4, $5);
    }
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

Def : Specifier DecList SEMI {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Def", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
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
    | LP Exp RP {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
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
    | ID LP Args RP {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 4, $1, $2, $3, $4);
    }
    | ID LP RP {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 3, $1, $2, $3);
    } 
    | Exp LB Exp RB {
        Data data;
        memset((void *)&data, 0, sizeof(Data));
        data.i = @1.first_line;
        $$ = NewNode("Exp", &data, false);
        TreeInsert($$, 4, $1, $2, $3, $4);
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
