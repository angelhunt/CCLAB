#include <stdio.h>
extern FILE* yyin;


int main(int argc, char ** argv) {
  yyin = fopen(argv[1], "r");
  while(yylex());
  return 0;
}
