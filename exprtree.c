
struct tnode *makeLeafNode(int n, char *name){
    struct tnode *temp;
    temp = malloc(sizeof(struct tnode));
    temp->flag = 0;
    temp->op = NULL;
    temp->val = n;
    temp->varname = name;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct tnode *makeOperatorNode(char c, struct tnode* l, struct tnode* r){
    struct tnode *temp;
    temp = malloc(sizeof(struct tnode));
    temp->flag = 2;
    temp->op = malloc(sizeof(char));
    *(temp->op) = c;
    temp->left = l;
    temp->right = r;
    return temp;
}

int evaluate(struct tnode *t){
    if(t->op == NULL){
        return t->val;
    }
    else{
        switch(*(t->op)){
            case '+':   return evaluate(t->left) + evaluate(t->right);
                        break;
            case '-':   return evaluate(t->left) - evaluate(t->right);
                        break;
            case '*':   return evaluate(t->left) * evaluate(t->right);
                        break;
            case '/':   return evaluate(t->left) / evaluate(t->right);
                        break;
            case '=':   t->left->val = evaluate(t->right);
                        return  evaluate(t->right);
            default:    return -1;
        }
    }
}

struct tnode *nodelookup( char *s ){
   struct tnode *node;

   for(node=tnodes; node < &tnodes[TOTAL]; node++) {
     /* is it already here? */
     if (node->varname && !strcmp(node->varname, s))
       return node;

     /* is it free */
     if (!node->varname) {
        node->flag = 1;
        node->varname = strdup(s);
        return node;
     }
     /* otherwise continue to the next */
   }
   yyerror("Exceed the Total Number of Symbols...\n");
   exit(1);
}

char *present(tnode *node){
    if(node->op == NULL){
        if(node->varname == NULL){
            char *tmp;
            tmp = malloc(10);
            sprintf(tmp, "%d", node->val);
            return tmp;
        }
        else{
            return node->varname;
        }
    }
    // char* fullStr;
    // fullStr = malloc(strlen(name)+1+4); /* make space for the new string (should check the return value ...) */
    // strcpy(name_with_extension, name); /* copy name into the new var */
    // strcat(name_with_extension, extension); /* add the extension */
    char *left_present = present(node->left);
    char *right_present = present(node->right);
    char *operator = node->op;
    if(strncmp(operator, "=", 1) != 0){
        struct temp *t = gettemp();
        char *tempvar = t->name;
        struct expr *expression = exprstack_lookup();
        expression->expr = malloc(50);
        sprintf(expression->expr, "%s = %s %s %s", tempvar, left_present, node->op, right_present);
        return tempvar;
    }
    else{
        struct expr *expression = exprstack_lookup();
        expression->expr = malloc(50);
        sprintf(expression->expr, "%s %s %s", left_present, operator, right_present);
        return left_present;
    }
    
}

struct expr *exprstack_lookup(){
    struct expr *e;

    for(e=exprstack; e < &exprstack[TOTAL]; e++) {
        /* is it already here? */
        if (e->flag == 0){
            e->flag = 1;
            return e;
        }
    }
    yyerror("Exceed the Total Number of Symbols...\n");
    exit(1);
}

void show(){
    struct expr *e;
    int index = 1;
    for(e=exprstack; e < &exprstack[TOTAL]; e++) {
        /* is it already here? */
        if (e->flag == 1){
            printf("\tS%d: %s;\n", index, e->expr);
            index++;
        }
    }
}

void transform2c(){
    FILE *fp = fopen("output.txt", "w+");

    if (fp != NULL)
    {
        fprintf(fp, "main(){\n");
        // define variable
        struct tnode *node;
        for(node = tnodes; node < &tnodes[TOTAL]; node++) {
            if(node->flag == 1){
                fprintf(fp, "\tint %s;\n", node->varname);
            }
        }
        // define temproary variable
        struct temp *tp;
        for(tp = temps; tp < &temps[TOTAL]; tp++) {
            if(tp->flag == 1){
                fprintf(fp, "\tint %s;\n", tp->name);
            }
        }

        // input value for variable
        for(node = tnodes; node < &tnodes[TOTAL]; node++) {
            if(node->flag == 1){
                fprintf(fp, "\tprintf(\"%s=\");\n", node->varname);
                fprintf(fp, "\tscanf(\"%%d\", &%s);\n", node->varname);
                fprintf(fp, "\n");
            }
        }

        // present statements
        struct expr *e;
        int idx = 1;
        for(e=exprstack; e < &exprstack[TOTAL]; e++) {
            /* is it already here? */
            if (e->flag == 1){
                fprintf(fp, "\tS%d: %s;\n", idx, e->expr);
                idx++;
            }
        }
        // struct quad *q;
        // int idx = 1;
        // for(q=quads; q<&quads[TOTAL]; q++){
        //     if(q != NULL){
        //         fprintf(fp, "\tS%d: %s %s %s %s;\n", idx, q->result, q->operation, q->arg1, q->arg2);
        //         idx++;
        //     }
        // }

        printf("\n");

        // print all the variable
        for(node = tnodes; node < &tnodes[TOTAL]; node++) {
            if(node->flag == 1){
                fprintf(fp, "\tprintf(\"%s=%%d\\n\", %s);\n", node->varname, node->varname);
            }
        }

        fprintf(fp, "      }\n");

        fclose(fp);
    }
}