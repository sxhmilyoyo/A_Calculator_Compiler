void updateCommonSubExpr(){
    printf("updateCommonSubExpr\n");
    extern struct quad *head;
    struct quad *pre = head;
    struct quad *i = head->next;
    struct quad *j;

    while(i){
        if(i->operation==NULL){
            break;
        }
        j = i->next;
        while(j){
            if(j->operation==NULL){
                break;
            }
            if(strcmp(i->arg1->name, j->arg1->name)==0 && strcmp(i->arg2->name, j->arg2->name)==0 && strcmp(i->operation->name, j->operation->name)==0){
                struct variable *t = gettemp();
                struct quad *q = buildQuad(i->operation, i->arg1, i->arg2, t);
                pre->next = q;
                q->next = i;

                // upate i and j
                i->arg1 = t;
                i->arg2 = NULL;
                i->operation = NULL;
                j->arg1 = t;
                j->arg2 = NULL;
                j->operation = NULL;
            }
            j = j->next;
        }
        pre = i;
        i = i->next;
    }
}