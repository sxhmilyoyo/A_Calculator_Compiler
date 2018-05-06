int yyerror(char const *s);

void inittemps() {
    int index = 1;
    struct temp *sp;

    for(sp = temps; sp < &temps[TOTAL]; sp++) {
        /* is it already here? */
        sp->name = malloc(10);
        sprintf(sp->name, "Temp%d", index);
        index++;
    }
}

struct temp *gettemp() {
   struct temp *sp;

   for(sp = temps; sp < &temps[TOTAL]; sp++) {
        /* is it already here? */
        if (sp->flag == 0){
            sp->flag = 1;
            return sp;
        }
   }
   yyerror("All temporary variables are used.\n");
   exit(1);
}

void freetemp(struct temp *t) {
    struct temp *sp;

    for(sp = temps; sp < &temps[TOTAL]; sp++) {
        /* is it already here? */
        if (sp->name == t->name){
            sp->flag = 0;
        }
        /* otherwise continue to the next */
   }
   yyerror("temporary variable is not in temps.\n");
   exit(1);
}