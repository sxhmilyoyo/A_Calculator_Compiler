#define TOTAL 50

struct variable {
  int used;     // 0: not used; 1: used
  int flag;     // 0: integer; 1: variable; 2: temporary; 3: operator
  char *name;
  int value;
};

struct variable variables[TOTAL];

struct variable temps[TOTAL];

struct variable *varlookup();

void inittemps();

struct variable *gettemp();

void freetemp(struct variable *t);

