struct copyStatement *lookupCopyTables(){
    struct copyStatement *cs;
    for(cs=copyTable; cs<&copyTable[COPYTABLESTOTAL]; cs++){
        if(cs->used==0){
            cs->used = 1;
            return cs;
        }
    }
    printf("no free room in copy tables.\n");
    exit(1);
}

void buildCopyTable(struct quad *q){
    printf("build\n");
    printf("result %s\n", q->result->name);
    printf("arg1 %s\n", q->arg1->name);    
    struct copyStatement *cs = lookupCopyTables();

    // cs->result = malloc(sizeof(struct variable));
    cs->result = q->result;

    // cs->arg = malloc(sizeof(struct variable));
    cs->arg = q->arg1;
}


void eliminateCopyfromCS(struct quad *q){
    printf("eliminate\n");
    struct copyStatement *cs;
    int f1 = 0;
    int f2 = 0;
    for(cs=copyTable; cs<&copyTable[COPYTABLESTOTAL]; cs++){
        // printf("used %d\n", cs->used);
        if(cs->used == 0){
            // printf("break\n");
            break;
        }
        if(q->arg1 && strcmp(q->arg1->name, cs->result->name)==0){
            // printf("arg1: %s\n", q->arg1->name);
            // printf("result: %s\n", cs->result->name);
            q->arg1 = cs->arg;
            f1 = 1;
        }
        if(q->arg2 && strcmp(q->arg2->name, cs->result->name)==0){
            // printf("arg1: %s\n", q->arg2->name);
            // printf("result: %s\n", cs->result->name);
            q->arg2 = cs->arg;
            f2 = 1;
        }
        if(f1==1 && f2==1){
            break;
        }
    }
    // printf("eliminateCopyfromCS finished.\n");
}

void eliminateCopy4CS(struct quad *q){
    printf("eliminateCopy4CS\n");
    extern struct quad *head;
    struct quad *h = head;

    while(h->next){
        if(strcmp(q->arg1->name, h->next->result->name)==0){
            q->arg1 = h->next->arg1;
            q->arg2 = h->next->arg2;
            q->operation = h->next->operation;
        }
        if(strcmp(q->arg1->name, h->next->arg1->name)==0 && h->next->arg2->name==NULL && strcmp(q->result->name, h->next->result->name)==0 && h->next->operation->name==NULL){
            break;
        }
        h = h->next;
    }
}


void copyElimination(){
    extern struct quad *head;
    struct quad *h = head;

    while(h->next){
        eliminateCopyfromCS(h->next);
        if(h->next->operation==NULL){
            // printf("assignment\n");
            eliminateCopy4CS(h->next);
            if(h->next->operation==NULL){
                buildCopyTable(h->next);
            }
        }

        h = h->next;
    }
}