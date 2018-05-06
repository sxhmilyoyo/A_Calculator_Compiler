int yyerror(char const *s);

struct variable *varlookup( char *s ) {
   char *p;
   struct variable *sp;

   for(sp = variables; sp < &variables[TOTAL]; sp++) {
     /* is it already here? */
     if (sp->name && !strcmp(sp->name, s))
       return sp;

     /* is it free */
     if (!sp->name) {
       sp->name = strdup(s);
       return sp;
     }
     /* otherwise continue to the next */
   }
   yyerror("Exceed the Total Number of Symbols...\n");
   exit(1);
}