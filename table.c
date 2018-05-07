struct RWTable *buildRWTable(){
    extern struct quad *head;
    struct quad *h;
    h = head;

    struct RWTable *RWTableHead = malloc(sizeof(struct RWTable));
    RWTableHead->var = NULL;
    RWTableHead->next = NULL;

    struct RWTable *RWTableH = RWTableHead;
    int i = 1;
    while(h->next != NULL){
        if(h->next->result != NULL){
            struct RWTable *node = lookupRWTable(RWTableHead, h->next->result);
            int idx = lookupWriteFreeIndex(node);
            // printf("resutl: write free index %d\n", idx);
            node->write[idx] = i;
        }
        if(h->next->arg1 != NULL && h->next->arg1->flag!=0){
            struct RWTable *node = lookupRWTable(RWTableHead, h->next->arg1);
            int idx = lookupReadFreeIndex(node);
            // printf("arg1: read free index %d\n", idx);            
            node->read[idx] = i;
        }
        if(h->next->arg2 != NULL && h->next->arg2->flag!=0){
            struct RWTable *node = lookupRWTable(RWTableHead, h->next->arg2);
            int idx = lookupReadFreeIndex(node);
            // printf("arg2: read free index %d\n", idx);                        
            node->read[idx] = i;
        }
        // break;
        i++;
        h = h->next;
    }
    return RWTableHead;
}

struct RWTable *lookupRWTable(struct RWTable *head, struct variable *var){
    // printf("%s\n", var->name);
    struct RWTable *h = head;
    while(h->next != NULL){
        if(strcmp(h->next->var->name, var->name)==0){
            return h->next;
        }
        h = h->next;
    }
    struct RWTable *node = malloc(sizeof(struct RWTable));
    cleanupRWTable(node);
    node->var = malloc(sizeof(struct variable));
    node->var = var;
    node->next = NULL;
    h->next = node;
    return node;
}

int lookupReadFreeIndex(struct RWTable *node){
    int i = 0;
    for(int i=0; i<RWTOTAL; i++){
        if(node->read[i] == 0){
            return i;
        }
    }
    printf("no free room in read.\n");
    exit(1);
}

int lookupWriteFreeIndex(struct RWTable *node){
    int i = 0;
    for(int i=0; i<RWTOTAL; i++){
        // printf("%d", node->write[i]);
        if(node->write[i] == 0){
            return i;
        }
    }
    printf("no free room in write.\n");
    exit(1);
}

struct RWTable *cleanupRWTable(struct RWTable *node){
    // printf("clean\n");
    for(int i=0; i<RWTOTAL; i++){
        node->read[i] = 0;
        node->write[i] = 0;
    }
    // for(int i=0; i<RWTOTAL; i++){
    //     printf("%d", node->read[i]);
    //     printf("%d", node->write[i]);
    // }
    return node;
}

void showRWTable(struct RWTable *head){
    struct RWTable *h = head;
    while(h->next){
        printf("variable %s\t", h->next->var->name);
        printf("read\t");          
        for(int i=0; i<RWTOTAL; i++){
            printf("%d ", h->next->read[i]);  
        }
        printf("write\t");                  
        for(int i=0; i<RWTOTAL; i++){
            printf("%d ", h->next->write[i]);  
        }
        printf("\n");
        h = h->next;
    }
}

void getDataDepend(struct RWTable *head){
    struct RWTable *h = head;
    while(h->next){
        // write
        if(h->next->var->flag!=0){
            for(int i=0; i<RWTOTAL; i++){
                if(h->next->write[i] == 0){
                    break;
                }
                // read
                for(int j=0; j<RWTOTAL; j++){
                    if(h->next->read[j] == 0){
                        break;
                    }

                    // write then read
                    if(h->next->write[i] < h->next->read[j]){
                        h->next->flag = 1;
                        struct dataDependTable *flowddt = lookupFlowDataDependTable(h->next->write[i], h->next->read[j]);
                        flowddt->i = h->next->write[i];
                        flowddt->j = h->next->read[j];
                    }
                    // read then write
                    if(h->next->write[i] > h->next->read[j]){
                        struct dataDependTable *antiddt = lookupAntiDataDependTable();
                        antiddt->i = h->next->read[j];
                        antiddt->j = h->next->write[i];
                    }
                }
                // write then write
                if(h->next->write[i+1]!=0){
                    struct dataDependTable *outputddt = lookupOutputDataDependTable();
                    outputddt->i = h->next->write[i];
                    outputddt->j = h->next->write[i+1];
                }
            }
        }
        h = h->next;
    }
}

struct dataDependTable *lookupFlowDataDependTable(int write, int read){
    struct dataDependTable *ddt;
    for(ddt=flow; ddt<&ddt[RWTOTAL]; ddt++){
        if(ddt->used == 1){
            if(ddt->i > write && ddt->j == read){
                return ddt;
            }
        }
        if(ddt->used == 0){
            ddt->used = 1;
            return ddt;
        }
    }
    printf("no available data depend table.");
    exit(1);
}

struct dataDependTable *lookupOutputDataDependTable(){
    struct dataDependTable *ddt;
    for(ddt=output; ddt<&ddt[RWTOTAL]; ddt++){
        if(ddt->used == 0){
            ddt->used = 1;            
            return ddt;
        }
    }
    printf("no available data depend table.");
    exit(1);
}

struct dataDependTable *lookupAntiDataDependTable(){
    struct dataDependTable *ddt;
    for(ddt=anti; ddt<&ddt[RWTOTAL]; ddt++){
        if(ddt->used == 0){
            ddt->used = 1;
            return ddt;
        }
    }
    printf("no available data depend table.");
    exit(1);
}

void showDataDependTable(){
    printf("flow data dependence\t");
    for(int i=0; i<RWTOTAL; i++){
        if(flow[i].used == 1){
            printf("%d -> %d\t", flow[i].i, flow[i].j);
        }
    }
    printf("\n");

    printf("output data dependence\t");
    for(int i=0; i<RWTOTAL; i++){
        if(output[i].used == 1){
            printf("%d -> %d\t", output[i].i, output[i].j);
        }
    }
    printf("\n");

    printf("anti data dependence\t");
    for(int i=0; i<RWTOTAL; i++){
        if(anti[i].used == 1){
            printf("%d -> %d\t", anti[i].i, anti[i].j);
        }
    }
    printf("\n");
}

void transfer2sentence(){
    extern struct quad *head;
    struct quad *h = head;
    FILE *fp = fopen("dataDependence.txt", "w+");
    
    int idx = 1;
    int flag;
    while(h->next){
        fprintf(fp, "S%d\n", idx);
        
        //flow data dependence
        flag = 0;
        fprintf(fp, "\tFlow dependence: ");        
        for(int i=0; i<RWTOTAL; i++){
            if(flow[i].used == 1 && flow[i].i == idx){
                fprintf(fp, "S%d\t", flow[i].j);
                flag = 1;
            }
        }
        if(flag==0){
            fprintf(fp, "%s\t", "None");
        }
        fprintf(fp, "\n");        

        //output data dependence
        flag = 0;        
        fprintf(fp, "\tOutput dependence: ");        
        for(int i=0; i<RWTOTAL; i++){
            if(output[i].used == 1 && output[i].i == idx){
                fprintf(fp, "S%d\t", output[i].j);
                flag = 1;                
            }
        }
        if(flag==0){
            fprintf(fp, "%s\t", "None");
        }
        fprintf(fp, "\n");        
        
        fprintf(fp, "\tAnti dependence: ");
        // anti data dependence
        flag = 0;        
        for(int i=0; i<RWTOTAL; i++){
            if(anti[i].used == 1 && anti[i].i == idx){
                fprintf(fp, "S%d\t", anti[i].j);
                flag = 1;                
            }
        }
        if(flag==0){
            fprintf(fp, "%s\t", "None");
        }
        fprintf(fp, "\n");    

        idx ++;
        h = h->next;    
        
    }
}