void buildQuad(char *operation, char *arg1, char *arg2, char *result){
    struct quad *q;
    q = lookupQuad();
    strcpy(q->operation, operation);
    strcpy(q->arg1, arg1);
    strcpy(q->arg2, arg2);
    strcpy(q->result, result);
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
        buildQuad(operator, left_node, right_node, tempvar);
        return tempvar;
    }
    else{
        // struct expr *expression = exprstack_lookup();
        // expression->expr = malloc(50);
        // sprintf(expression->expr, "%s %s %s", left_present, operator, right_present);
        buildQuad("", right_node, "", left_node);
        return left_node;
    }
    
}

struct quad *lookupQuad(){
    struct quad *q;

    for(q=quads; q<&quads[TOTAL]; q++) {
        /* is it already here? */
        if (q->flag == 0){
            q->flag = 1;
            return q;
        }
    }
    yyerror("Exceed the Total Number of Symbols...\n");
    exit(1);
}

struct quadLinkedList *buildQuad4ListNode(int flag, char *operation, char *arg1, char *arg2, char *result, struct quadLinkedList *next){
    struct quadLinkedList *q;
    q = malloc(sizeof(struct quadLinkedList));
    q->flag = flag;
    strcpy(q->operation, operation);
    strcpy(q->arg1, arg1);
    strcpy(q->arg2, arg2);
    strcpy(q->result, result);
    q->next = next;
    return q;
}

struct quadLinkedList *updateQuad4ListNode(struct quadLinkedList *node, char *result, struct quadLinkedList *next){
    strcpy(node->result, result);
    node->next = next;
    return node;
}

// build linked list for TAC
struct quadLinkedList *buildLinkedList4TAC(){
    printf("test");
    struct quadLinkedList *head;
    struct quadLinkedList *h;
    struct quadLinkedList *node;

    head = buildQuad4ListNode(1, "", "", "", "", NULL);
    // h->flag = 1;
    // h->next = NULL;
    h = head;

    struct quad *q;
    for(q=quads; q<&quads[TOTAL]; q++){
        if(q->flag == 1){
            node = buildQuad4ListNode(0, q->operation, q->arg1, q->arg2, q->result, NULL);
            h->next = node;
            h = h->next;        
        }
    }
    // test
    // struct quadLinkedList *tmp;
    // tmp = head;
    // while(tmp->next!=NULL){
    //     printf("%d", tmp->flag);
    //     tmp = tmp->next;
    // }
    return head;
}

struct quadLinkedList *rmDupAssign(){
    struct quadLinkedList *head, *pre, *current;
    pre = head;
    current = pre->next;

    while(current!=NULL){
        if(current->flag==0 && strcmp(current->operation, "")==0 && strcmp(pre->result, current->arg1)==0){
            updateQuad4ListNode(pre, current->result, current->next);
            current = pre->next;
        }
        else{
            pre = current;
            current = current->next;
        }
    }

    struct quadLinkedList *tmp;
    tmp = head;
    while(tmp->next!=NULL){
        printf("%d", tmp->flag);
        tmp = tmp->next;
    }
    return head;
}