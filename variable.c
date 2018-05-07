int yyerror(char const *s);

struct variable *varlookup( char *s ) {
  char *p;
  struct variable *sp;

  for(sp = variables; sp < &variables[TOTAL]; sp++) {
    /* is it already here? */
    if (sp->used==1 && strcmp(sp->name, s)==0){
      return sp;
    }

    /* is it free */
    if (sp->used==0) {
      sp->used = 1;
      sp->name = strdup(s);
      return sp;
    }
    /* otherwise continue to the next */
  }
  yyerror("Exceed the Total Number of Symbols...\n");
  exit(1);
}

int yyerror(char const *s);

void inittemps() {
  int index = 1;
  struct variable *sp;

  for(sp = temps; sp < &temps[TOTAL]; sp++) {
      /* is it already here? */
      sp->flag = 2;
      sp->used = 0;
      sp->name = malloc(10);
      sprintf(sp->name, "Temp%d", index);
      index++;
  }
}

struct variable *gettemp() {
  struct variable *sp;

  for(sp = temps; sp < &temps[TOTAL]; sp++) {
      /* is it already here? */
      if (sp->used == 0){
          sp->used = 1;
          return sp;
      }
  }
  yyerror("All temporary variables are used.\n");
  exit(1);
}

void freetemp(struct variable *t) {
    struct variable *sp;

    for(sp = temps; sp < &temps[TOTAL]; sp++) {
        /* is it already here? */
        if (strcmp(sp->name, t->name)==0){
            sp->used = 0;
            return;
        }
        /* otherwise continue to the next */
   }
   yyerror("temporary variable is not in temps.\n");
   exit(1);
}