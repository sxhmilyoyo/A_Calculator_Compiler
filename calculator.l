/* Auxiliary declarations start here */

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "y.tab.h"
    #include "variable.h"
    #include "variable.c"
    int yyerror(char const *);
    struct tnode* makeLeafNode(int n, char* name);
    struct tnode* nodelookup( char *s );
    // #include "exprtree.h"
    // #include "exprtree.c"

    int number;
    char *name;
    int value;
%}
%option noyywrap

/* Regular expressions start here */
%%

[a-zA-Z][a-zA-Z0-9]*	{
                        struct tnode *sp = nodelookup(yytext);
                        yylval.tnode = sp;
                        return VARIABLE;
                    }
[0-9]+      {
                number = atoi(yytext);
                yylval.tnode = makeLeafNode(number, NULL);
                return NUM;
            }
"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return MUL;}
"/"         {return DIV;}
"="         {return ASSIGN;}
";"         {return SEMICOLON;}
[ \t]       {}
[()]        {return *yytext;}
[\n]        {return END;}
.           {
                yyerror("unknown character\n");
                exit(1);
            }

%%

/* Auxiliary functions */
// int yywrap(void){
//     return 1;
// }