%option yylineno
letter       [a-zA-Z]
digit        [0-9]
delim        [ \r\t\n]
ws           {delim}+
ten          0|([1-9][0-9]*)
eight        0[1-7]*
sixteen      0[xX]([1-9a-f]*|[1-9A-F]*)

ERR_EIGHT    0([1-7]*[089a-zA-Z]+[1-7]*)*
ERR_SIXTEEN  (0[x]([1-9a-f]*[g-z]+[1-9a-f]*)*)|(0[X]([1-9A-F]*[G-Z]+[1-9A-F]*)*)

INT          {ten}|{eight}|{sixteen}
FLOAT        [0-9]+(\.[0-9]+)?([Ee][+-]?[0-9]+)?
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
"//"              {
                     char c = input();
		     while (c != '\n')
		     {
		            c = input ();
		     }
		  }
"/\*"             {
                     char c = input();
		     while(1)
		     {
			   if(c == '*')
			   {
		              c = input();
			      if(c == '/')
			         break;
			   }
			   else
			   c = input();
	             }
		  }
{ws}              {  printf("WS\n");/*nothing */     return 1; }
{ERR_SIXTEEN}     {  printf("Error type A at Line:%d invalid digit \"%s\" in hexadecimal constant\n", yylineno, yytext);      
                     return 1; }
{ERR_EIGHT}       {  printf("Error type A at Line:%d invalid digit \"%s\" in octal constant\n", yylineno, yytext);       
                     return 1; }
{INT}             {  printf("INT\n");
		     return 1; }
{FLOAT}           {  printf("FLOAT\n");
	             return 1; }
{SEMI}            {  printf("SEMI\n");
	             return 1; }
{COMMA}           {  printf("COMMA\n");
	             return 1; }
{ASSIGNOP}        {  printf("ASSIGNOP\n");
	             return 1; }
{MINUS}           {  printf("MINUS\n");
	             return 1; }
{PLUS}            {  printf("PLUS\n"); 
	             return 1;  }
{STAR}            {  printf("STAR\n");
	             return 1; }
{DIV}             {  printf("DIV\n");
	             return 1; }
{AND}             {  printf("AND\n");
	             return 1; }
{OR}              {  printf("OR\n");
	             return 1; }
{NOT}             {  printf("NOT\n");
	             return 1; }
{DOT}             {  printf("DOT\n");
	             return 1; }
{LP}              {  printf("LP\n");
	             return 1; }
{RP}              {  printf("RP\n");
	             return 1; }
{LB}              {  printf("LB\n");
	             return 1; }
{RB}              {  printf("RB\n");
	             return 1; }
{LC}              {  printf("LC\n");
	             return 1; }
{RC}              {  printf("RC\n");
	             return 1; }
{STRUCT}          {  printf("STRUCT\n");
	             return 1; }
{IF}              {  printf("IF\n");
	             return 1; }
{RETURN}          {  printf("RETURN\n");
	             return 1; }
{ELSE}            {  printf("ELSE\n");
	             return 1; }
{WHILE}           {  printf("WHILE\n");
	             return 1; }
{RELOP}           {  printf("RELOP\n");
	             return 1; }
{TYPE}            {  printf("TYPE\n");
	             return 1; }
EOF               {  return 0;}
{ID}              {  printf("ID\n");
	             return 1; }
.                 {  printf("Error type A at Line:%d Myserious characters \"%s\"\n", yylineno, yytext);      return 1;} 
