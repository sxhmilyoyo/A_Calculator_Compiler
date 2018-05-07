#define TOTAL 50
int yyerror(char const *s);

struct quad{
	int flag;
	struct variable *operation;
	struct variable *arg1;
	struct variable *arg2;
	struct variable *result;
	struct quad *next;
}quads[TOTAL];

// struct quadLinkedList{
// 	int flag;
// 	struct quad *next;
// };

// head
// extern struct quad *quadHead;
// extern struct quad *quadHead;

// lookup quad
struct quad *lookupQuad();

// build quad for each expression
struct quad *buildQuad(struct variable *operation, struct variable *arg1, struct variable *arg2, struct variable *result);
// build TAC for the syntax tree
struct variable *buildTAC(tnode *node);

// build linked list node
struct quadLinkedList *buildQuad4ListNode(int flag, struct variable *operation, struct variable *arg1, struct variable *arg2, struct variable *result, struct quadLinkedList *next);

// build linked list for TAC
struct quad *buildLinkedList4TAC(struct quad *q);

// update the quad node in linked list
struct quad *updateQuad4ListNode(struct quad *node, struct variable *result, struct quad *next);

// remove the duplicate assignment
struct quad *rmDupAssign();