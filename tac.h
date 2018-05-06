#define TOTAL 20
int yyerror(char const *s);

struct quad{
	char operation[10];
	char arg1[20];
	char arg2[20];
	char result[10];
} quads[TOTAL];

// build quad for each expression
void buildQuad(char *operation, char *arg1, char *arg2, char *result);

// build TAC for the syntax tree
char *buildTAC(tnode *node);
