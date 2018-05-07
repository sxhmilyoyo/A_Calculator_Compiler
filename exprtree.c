
struct tnode *makeLeafNode(int n, char *name){
    // printf("leaf0");
    struct variable *var;
    var = varlookup(name);
    if(strcmp(name, "") == 0){
        var->flag = 0;
        sprintf(var->name, "%d", n);
    }
    else{
        printf("%s", name);        
        var->flag = 1;
    }
    var->value = n;

    struct tnode *temp;
    temp = malloc(sizeof(struct tnode));
    temp->flag = 0;
    temp->op = NULL;
    // temp->val = n;
    // temp->varname = name;
    temp->var = malloc(sizeof(struct variable));
    temp->var = var;
    temp->left = NULL;
    temp->right = NULL;
    // printf("leaf1");    
    return temp;
}

struct tnode *makeOperatorNode(char *c, struct tnode* l, struct tnode* r){
    // printf("operator0");    
    struct variable *var;
    var = varlookup(c);
    var->flag = 3;
    // var->name = malloc(sizeof(char));
    // *(var->name) =  c;
    var->value = 0;

    struct tnode *temp;
    temp = malloc(sizeof(struct tnode));
    temp->flag = 2;
    // temp->op = malloc(sizeof(char));
    temp->var = malloc(sizeof(struct variable));
    temp->var = var;
    
    temp->op = strdup(c);
    temp->left = l;
    temp->right = r;
    // printf("operator1");        
    return temp;
}

int evaluate(struct tnode *t){
    if(t->op == NULL){
        return t->var->value;
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
            case '=':   t->left->var->value = evaluate(t->right);
                        return  evaluate(t->right);
            default:    return -1;
        }
    }
}

struct tnode *nodelookup( char *s ){
   struct tnode *node;

   for(node=tnodes; node < &tnodes[TOTAL]; node++) {
     /* is it already here? */
     if (node->var->name && !strcmp(node->var->name, s))
       return node;

     /* is it free */
     if (!node->var->name) {
        node->flag = 1;
        node->var->name = strdup(s);
        return node;
     }
     /* otherwise continue to the next */
   }
   yyerror("Exceed the Total Number of Symbols...\n");
   exit(1);
}

// char *present(tnode *node){
//     if(node->op == NULL){
//         if(node->varname == NULL){
//             char *tmp;
//             tmp = malloc(10);
//             sprintf(tmp, "%d", node->val);
//             return tmp;
//         }
//         else{
//             return node->varname;
//         }
//     }
//     // char* fullStr;
//     // fullStr = malloc(strlen(name)+1+4); /* make space for the new string (should check the return value ...) */
//     // strcpy(name_with_extension, name); /* copy name into the new var */
//     // strcat(name_with_extension, extension); /* add the extension */
//     char *left_present = present(node->left);
//     char *right_present = present(node->right);
//     char *operator = node->op;
//     if(strncmp(operator, "=", 1) != 0){
//         struct temp *t = gettemp();
//         char *tempvar = t->name;
//         struct expr *expression = exprstack_lookup();
//         expression->expr = malloc(50);
//         sprintf(expression->expr, "%s = %s %s %s", tempvar, left_present, node->op, right_present);
//         return tempvar;
//     }
//     else{
//         struct expr *expression = exprstack_lookup();
//         expression->expr = malloc(50);
//         sprintf(expression->expr, "%s %s %s", left_present, operator, right_present);
//         return left_present;
//     }
    
// }

// struct expr *exprstack_lookup(){
//     struct expr *e;

//     for(e=exprstack; e < &exprstack[TOTAL]; e++) {
//         /* is it already here? */
//         if (e->flag == 0){
//             e->flag = 1;
//             return e;
//         }
//     }
//     yyerror("Exceed the Total Number of Symbols...\n");
//     exit(1);
// }

// void show(){
//     struct expr *e;
//     int index = 1;
//     for(e=exprstack; e < &exprstack[TOTAL]; e++) {
//         /* is it already here? */
//         if (e->flag == 1){
//             printf("\tS%d: %s;\n", index, e->expr);
//             index++;
//         }
//     }
// }

void transform2c(){
    FILE *fp = fopen("output.txt", "w+");

    if (fp != NULL)
    {
        fprintf(fp, "main(){\n");
        // define variable
        struct variable *var;
        for(var = variables; var < &variables[TOTAL]; var++) {
            if(var->used == 1 && var->flag == 1 && strcmp(var->name, "") != 0){
                fprintf(fp, "\tint %s;\n", var->name);
            }
        }
        // define temproary variable
        struct variable *tp;
        for(tp = temps; tp < &temps[TOTAL]; tp++) {
            if(tp->used == 1 && var->flag == 2){
                fprintf(fp, "\tint %s;\n", tp->name);
            }
        }

        // input value for variable
        for(var = variables; var < &variables[TOTAL]; var++) {
            if(var->used == 1 && var->flag == 1 && strcmp(var->name, "") != 0){
                fprintf(fp, "\tprintf(\"%s=\");\n", var->name);
                fprintf(fp, "\tscanf(\"%%d\", &%s);\n", var->name);
                fprintf(fp, "\n");
            }
        }

        // present statements
        // struct expr *e;
        // int idx = 1;
        // for(e=exprstack; e < &exprstack[TOTAL]; e++) {
        //     /* is it already here? */
        //     if (e->flag == 1){
        //         fprintf(fp, "\tS%d: %s;\n", idx, e->expr);
        //         idx++;
        //     }
        // }
        
        int idx = 1;
        extern struct quad *head;
        struct quad *h = malloc(sizeof(int) + 4*sizeof(struct variable) + sizeof(struct quad));;
        h = head;
        char *s1, *s2, *s3, *s4;
        while(h->next != NULL){
            
            if(h->next->result != NULL){
                s1 = h->next->result->name;
            }
            else{
                s1 = "";
            }
            if(h->next->arg1 != NULL){
                s2 = h->next->arg1->name;
            }
            else{
                s2 = "";
            }
            if(h->next->operation != NULL){
                s3 = h->next->operation->name;
            }
            else{
                s3 = "";
            }
            if(h->next->arg2 != NULL){
                s4 = h->next->arg2->name;
            }
            else{
                s4 = "";
            }
            fprintf(fp, "\tS%d: %s=%s%s%s;\n", idx, s1, s2, s3, s4);
            h = h->next;

            idx++;
        }
        // for(q=quads; q<&quads[TOTAL]; q++){
        //     printf("%d", q->flag);
        //     if(q->flag == 1){
        //         printf("111");
                
        //         fprintf(fp, "\tS%d: %s=%s%s%s;\n", idx, q->result->name, q->arg1->name, q->operation->name, q->arg2->name);
        //         idx++;
        //     }
        // }

        printf("\n");

        // print all the variable
        for(var = variables; var < &variables[TOTAL]; var++) {
            if(var->used == 1 && var->flag == 1 && strcmp(var->name, "") != 0){
                fprintf(fp, "\tprintf(\"%s=%%d\\n\", %s);\n", var->name, var->name);
            }
        }

        fprintf(fp, "      }\n");

        fclose(fp);
        printf("done.\n");
    }
}