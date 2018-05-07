#define TOTAL 20
int yyerror(char const *s);

struct quad{
	int flag;
	char operation[10];
	char arg1[20];
	char arg2[20];
	char result[10];
}quads[TOTAL];

struct quadLinkedList{
	int flag;
	char operation[10];
	char arg1[20];
	char arg2[20];
	char result[10];
	struct quadLinkedList *next;
};

// head
// extern struct quad *quadHead;
// extern struct quad *quadHead;

// lookup quad
struct quad *lookupQuad();

// build quad for each expression
void buildQuad(char *operation, char *arg1, char *arg2, char *result);

// build TAC for the syntax tree
char *buildTAC(tnode *node);

// remove duplicate assignment
// void rmDupAssign();


// build linked list node
struct quadLinkedList *buildQuad4ListNode(int flag, char *operation, char *arg1, char *arg2, char *result, struct quadLinkedList *next);

// build linked list for TAC
struct quadLinkedList *buildLinkedList4TAC();