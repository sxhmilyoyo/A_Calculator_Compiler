#define RWTOTAL 20

struct RWTable{
    int flag;               // 0: init; 1: read first
    struct variable *var;
    int read[RWTOTAL];
    int write[RWTOTAL];
    struct RWTable *next;
};

struct dataDependTable{
    int used;
    int i;
    int j;
};

struct dataDependTable flow[RWTOTAL];
struct dataDependTable output[RWTOTAL];
struct dataDependTable anti[RWTOTAL];

// build read and write table
struct RWTable *buildRWTable();

// look up RWTable: if existed return; else create a new one
struct RWTable *lookupRWTable(struct RWTable *head, struct variable *var);

// look up free index in read array
int lookupReadFreeIndex(struct RWTable *node);

// look up free index in write array
int lookupWriteFreeIndex(struct RWTable *node);

// clean up read & write array
struct RWTable *cleanupRWTable(struct RWTable *node);

// show read & write table
void showRWTable(struct RWTable *head);

// get dependencies for statements
void getDataDepend(struct RWTable *head);

// get available and update existed flow type dependend table 
struct dataDependTable *lookupFlowDataDependTable(int write, int read);

// get available output data dependend table
struct dataDependTable *lookupOutputDataDependTable();

// get available anti data dependend table
struct dataDependTable *lookupAntiDataDependTable();

// show data dependence table
void showDataDependTable();

// transfer to sentence
void transfer2sentence();