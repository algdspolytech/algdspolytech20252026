#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrioQueue.h"


//fInitTests


int DefRead() {
    PrioQueueUnit* root;
    FILE* fptr = fopen("q1.txt", "r");
    root = fInitPrioQueue(fptr);
    fclose(fptr);
    return ((root->el.prio == 2) && (root->el.data == 3));
};

int EmptyRead() {
    PrioQueueUnit* root;
    FILE* fptr = fopen("Emq.txt", "r");
    root = fInitPrioQueue(fptr);
    fclose(fptr);
    return root == NULL;
};

int RndRead() {
    PrioQueueUnit* root1, *root2;
    FILE* fptr1 = fopen("Rndq.txt", "r");
    FILE* fptr2 = fopen("Sortq.txt", "r");
    root1 = fInitPrioQueue(fptr1);
    root2 = fInitPrioQueue(fptr2);
    fclose(fptr1);
    fclose(fptr2);
    return QueueCmp(root1, root2);
};

//QueueCmpTests

int SameQ() {
    PrioQueueUnit* root;
    FILE* fptr = fopen("q2.txt", "r");
    root = fInitPrioQueue(fptr);
    fclose(fptr);
    return QueueCmp(root, root);
};

int DifSizeQ() {
    PrioQueueUnit* root1, *root2;
    FILE* fptr1 = fopen("q1.txt", "r");
    FILE* fptr2 = fopen("q2.txt", "r");
    root1 = fInitPrioQueue(fptr1);
    root2 = fInitPrioQueue(fptr2);
    fclose(fptr1);
    fclose(fptr2);
    return !QueueCmp(root1, root2);
};

int DifElQ() {
    PrioQueueUnit* root1, *root2;
    FILE* fptr1 = fopen("q2.txt", "r");
    FILE* fptr2 = fopen("q3.txt", "r");
    root1 = fInitPrioQueue(fptr1);
    root2 = fInitPrioQueue(fptr2);
    fclose(fptr1);
    fclose(fptr2);
    return !QueueCmp(root1, root2);
};

int NullQ() {
    PrioQueueUnit* root1, *root2 = InitPrioQueue();
    FILE* fptr1 = fopen("q2.txt", "r");
    root1 = fInitPrioQueue(fptr1);
    fclose(fptr1);
    return !QueueCmp(root1, root2);
};

int BothNullQ() {
    PrioQueueUnit* root = InitPrioQueue();
    return QueueCmp(root, root);
};

//PopElementTests

int DefPop(){
    PrioEl el = {2, 3}, popel;
    FILE* fptr = fopen("q1.txt", "r");
    PrioQueueUnit* root = fInitPrioQueue(fptr);
    fclose(fptr);
    popel = PopElement(root);
    return((el.prio == popel.prio) && (el.data == popel.data));
};

//PushElementTests

int DefPush() {
    PrioQueueUnit* root1, *root2 = InitPrioQueue();
    PrioEl el = {2, 3};
    FILE* fptr1 = fopen("q1.txt", "r");
    root1 = fInitPrioQueue(fptr1);
    PushElement(&root2, el);
    fclose(fptr1);
    return QueueCmp(root1, root2);
};

int main() {
    /*
    //fInitQueue
    printf("%d\n", DefRead());
    printf("%d\n", EmptyRead());
    printf("%d\n", RndRead());
    printf("\n");
    //QueueCmpTests
    printf("%d\n", SameQ());
    printf("%d\n", DifSizeQ());
    printf("%d\n", DifElQ());
    printf("%d\n", NullQ());
    printf("%d\n", BothNullQ());
    printf("\n");
    //PopElement
    printf("%d\n", DefPop());
    printf("\n");
    //PushEle,ent
    printf("%d\n", DefPush());
    */
    if(DefRead()*EmptyRead()*RndRead()*SameQ()*DifSizeQ()*DifElQ()*NullQ()*BothNullQ()*DefPop()*DefPush())
        printf("Tests completed");
    else
        printf("Tests failed");
};
