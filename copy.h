#define COPYTABLESTOTAL 20

struct copyStatement{
    int used;
    struct variable *result;
    struct variable *arg;
}copyTable[COPYTABLESTOTAL];

// look up the copyTables
struct copyStatement *lookupCopyTables();

// build copyTables
void buildCopyTable(struct quad *q);

// eliminate the copy statement
void eliminateCopy(struct quad *q);

// eliminate copy statements for copy statements
void eliminateCopy4CS(struct quad *q);

// main function for copy statements elimination
void copyElimination();