
struct quad *buildQuad(struct variable *operation, struct variable *arg1, struct variable *arg2, struct variable *result){
    // printf("build");
    struct quad *q;
    q = malloc(sizeof(struct quad));
    // q = lookupQuad();
    // q = malloc(sizeof(int) + 4*sizeof(struct variable) + sizeof(struct quad));
    // q->operation = malloc(sizeof(struct variable));
    // q->arg1 = malloc(sizeof(struct variable));
    // q->arg2 = malloc(sizeof(struct variable));
    // q->result = malloc(sizeof(struct variable));
    q->operation = operation;
    q->arg1 =  arg1;
    q->arg2 = arg2;
    q->result = result;
    q->next = NULL;

    return q;
}

struct variable *buildTAC(tnode *node){
    if(node->op == NULL){
        // printf("op");
        return node->var;
    }
    // char* fullStr;
    // fullStr = malloc(strlen(name)+1+4); /* make space for the new string (should check the return value ...) */
    // strcpy(name_with_extension, name); /* copy name into the new var */
    // strcat(name_with_extension, extension); /* add the extension */
    struct variable *left_node = buildTAC(node->left);
    struct variable *right_node = buildTAC(node->right);
    struct variable *operator = node->var;
    // printf("get\n");
    if(strncmp(operator->name, "=", 1) != 0){
        struct variable *t = gettemp();
        // char *tempvar = t->name;
        // struct expr *expression = exprstack_lookup();
        // expression->expr = malloc(50);
        // sprintf(expression->expr, "%s = %s %s %s", tempvar, left_present, node->op, right_present);
        buildLinkedList4TAC(buildQuad(operator, left_node, right_node, t));
        return t;
    }
    else{
        // struct expr *expression = exprstack_lookup();
        // expression->expr = malloc(50);
        // sprintf(expression->expr, "%s %s %s", left_present, operator, right_present);
        buildLinkedList4TAC(buildQuad(NULL, right_node, NULL, left_node));
        return left_node;
    }
    
}

// struct quad *lookupQuad(){
//     // printf("lookup");
//     struct quad *q;

//     for(q=quads; q<&quads[TOTAL]; q++) {
//         /* is it already here? */
//         if (q->flag == 0){
//             q = malloc(sizeof(int) + 4*sizeof(struct variable));
//             q->flag = 1;
//             printf("lookup%d\n", q->flag);
//             return q;
//         }
//     }
//     yyerror("Exceed the Total Number of Symbols...\n");
//     exit(1);
// }

// struct quadLinkedList *buildQuad4ListNode(int flag, struct variable *operation, struct variable *arg1, struct variable *arg2, struct variable *result, struct quadLinkedList *next){
//     struct quadLinkedList *q;
//     q = malloc(sizeof(struct quadLinkedList));
//     q->operation = operation;
//     q->arg1 = arg1;
//     q->arg2 = arg2;
//     q->result = result;
//     return q;
// }

struct quad *updateQuad4ListNode(struct quad *node, struct variable *result, struct quad *next){
    node->result = result;
    node->next = next;
    return node;
}

// build linked list for TAC
struct quad *buildLinkedList4TAC(struct quad *q){
    // struct quadLinkedList *head;
    struct quad *h;
    // struct quadLinkedList *node;

    // head = buildQuad4ListNode(1, NULL, NULL, NULL, NULL, NULL);
    // h->flag = 1;
    // h->next = NULL;
    extern struct quad *head;
    h = head;

    while(h->next!=NULL){
        h = h->next;
    }
    // h->next = malloc(sizeof(struct quad));
    h->next = q;
    // struct quad *q;
    // for(q=quads; q<&quads[TOTAL]; q++){
    //     if(q->flag == 1){
    //         node = buildQuad4ListNode(0, q->operation, q->arg1, q->arg2, q->result, NULL);
    //         h->next = node;
    //         h = h->next;        
    //     }
    // }
    // test
    // struct quadLinkedList *tmp;
    // tmp = head;
    // while(tmp->next!=NULL){
    //     printf("%d", tmp->flag);
    //     tmp = tmp->next;
    // }
    return head;
}

struct quad *rmDupAssign(){
    extern struct quad *head;
    struct quad *pre, *current;
    pre = head->next;
    current = pre->next;

    while(current!=NULL){
        if(current->operation == NULL && pre->result->flag == 2  && current->arg1->flag == 2 && strcmp(pre->result->name, current->arg1->name)==0){
            freetemp(pre->result);
            updateQuad4ListNode(pre, current->result, current->next);
            current = pre->next;
        }
        else{
            pre = current;
            current = current->next;
        }
    }

    // struct quad *tmp;
    // tmp = head;
    // while(tmp->next!=NULL){
    //     printf("%d", tmp->flag);
    //     tmp = tmp->next;
    // }
    return head;
}