#define TOTAL 20

struct variable {
  char *name;
  int value;
} variables[TOTAL];

struct variable *varlookup();
