/* Beginning of Declarations part */
%{
    /* Beginning of C declarations */
    #include <stdio.h>
    #include <stdlib.h>

    #include "temp.h"
    #include "temp.c"
    #include "exprtree.h"
    #include "exprtree.c"

    int yylex(void);
    int yyerror(char const *s);

    extern FILE *yyin;
%}

%union{
    int value;
    char *str;
    struct tnode *tnode;
}

/* Beginning of YACC declarations */
// %token <str> NUM PLUS MINUS MUL DIV END
%right ASSIGN
%left PLUS MINUS
%left MUL DIV


%token <str> PLUS MINUS MUL DIV ASSIGN SEMICOLON END
%token <tnode> NUM VARIABLE
%type <tnode> expr statement
%type <str> program

%%
program : program statement END     {
                                        $$ = $3;
                                        printf("Answer : %d\n", evaluate($2));
                                        present($2);
                            
                                        return 0;
                                    }
        | statement END     {
                                $$ = $2;
                                printf("Answer : %d\n", evaluate($1));
                                present($1);
                                
                                return 0;
                            }
        | program statement SEMICOLON END   {
                                                $$ = $4;
                                                printf("Answer : %d\n", evaluate($2));
                                                present($2);
                                                // exit(1);
                                            }
        | statement SEMICOLON END   {
                                        $$ = $3;
                                        printf("Answer : %d\n", evaluate($1));
                                        present($1);
                                        
                                        // exit(1);
                                    }
    ;


statement   : expr
            // | VARIABLE ASSIGN statement     {$$ = makeOperatorNode('=', $1, $3);}
            // | VARIABLE ASSIGN statement     {$$ = makeOperatorNode('=', $1, $3);}
            ;

expr : expr PLUS expr       {$$ = makeOperatorNode('+', $1, $3);}
     | expr MINUS expr      {$$ = makeOperatorNode('-', $1, $3);}
     | expr MUL expr        {$$ = makeOperatorNode('*', $1, $3);}
     | expr DIV expr        {$$ = makeOperatorNode('/', $1, $3);}
     | '(' expr ')'         {$$ = $2;}
     | NUM                  {$$ = $1;}
     | VARIABLE             {$$ = $1;}
     | VARIABLE ASSIGN expr     {$$ = makeOperatorNode('=', $1, $3);}    
     ;

%%
/* Auxiliary functions */
int yyerror(char const *s){
    printf("yyerror %s\n", s);
    return 0;
}

int main(void){
    inittemps();

  	yyin = fopen("input_file.txt","r");
    yyparse();
    fclose(yyin);

    transform2c();
    return 0;
}