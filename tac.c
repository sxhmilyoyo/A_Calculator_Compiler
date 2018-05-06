void buildQuad(char *operation, char *arg1, char *arg2, char *result){
    struct quad *q;
    for(q=quads; q<&quads[TOTAL]; q++){
        if(q != NULL){
            strcpy(q->operation, operation);
            strcpy(q->arg1, arg1);
            strcpy(q->arg2, arg2);
            strcpy(q->result, result);
        }
    }
}

char *buildTAC(tnode *node){
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
    char *left_node = buildTAC(node->left);
    char *right_node = buildTAC(node->right);
    char *operator = node->op;
    if(strncmp(operator, "=", 1) != 0){
        struct temp *t = gettemp();
        char *tempvar = t->name;
        // struct expr *expression = exprstack_lookup();
        // expression->expr = malloc(50);
        // sprintf(expression->expr, "%s = %s %s %s", tempvar, left_present, node->op, right_present);
        buildQuad("=", left_node, right_node, tempvar);
        return tempvar;
    }
    else{
        // struct expr *expression = exprstack_lookup();
        // expression->expr = malloc(50);
        // sprintf(expression->expr, "%s %s %s", left_present, operator, right_present);
        buildQuad(operator, NULL, right_node, left_node);
        return left_node;
    }
    
}
