#include "variable.h"
#include <string.h>
#define TOTAL 20

int yyerror(char const *s);

typedef struct tnode{
    int flag;   //indicate whether the node is a leaf(0: number; 1: variable) or internal node(2: operator)
    char *varname;      //name of the variable
    int val;    //value of the expression tree
    char *op;   //operator branch
    struct tnode *left, *right;     //left and right node
}tnode;

struct expr{
    int flag;
    char *expr;
}exprstack[TOTAL];

tnode tnodes[TOTAL];

// construct a leaf tnode and set the value to val field
tnode *makeLeafNode(int n, char *name);

// construct a operator tnode and set the left and right nodes
tnode *makeOperatorNode(char c, tnode *l, tnode *r);

// evaluate an expression tree
int evaluate(tnode *t);

// look up the node
tnode *nodelookup( char *s );

// present and store statements into expr
char *present(tnode *t);

// get expr struct
struct expr *exprstack_lookup();

// transform the calculator language into C language
void transform2c();