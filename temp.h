#define TOTAL 20

struct temp {
  char *name;   //temporary variable name
  int flag;     //indicate whether the variable is free(0: free; 1: used)
} temps[TOTAL];

void inittemps();

struct temp *gettemp();

void freetemp(struct temp *t);
