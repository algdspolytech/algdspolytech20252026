#include "Node.h"

pNode createNode(int key, int priority)
{
    pNode node = (pNode)malloc(sizeof(struct Node));

    if (!node) return; // if there is not enough space

    node->key = key;
    node->priority = priority;
    node->l = NULL;
    node->r = NULL;

    return node;
}

void split(pNode t, int x, pNode* l, pNode* r)
{
    if (!t)
    {
        *l = NULL;
        *r = NULL;
    }
    else if (t->key > x)
    {
        split(t->l, x, l, &(t->l));
        *r = t;
    }
    else
    {
        split(t->r, x, &(t->r), r);
        *l = t;
    }
}

void merge(pNode* t, pNode l, pNode r)
{
    if (!l) {
        *t = r;
    }
    else if (!r) {
        *t = l;
    }
    else if (l->priority < r->priority) {
        merge(&(l->r), l->r, r);
        *t = l;
    }
    else {
        merge(&(r->l), l, r->l);
        *t = r;
    }
}

void removeAt(pNode* t, int key)
{
    if (!*t) {
        return;
    }
    if ((*t)->key == key) {
        pNode tmp = *t;
        merge(t, (*t)->l, (*t)->r);
        free(tmp);
    }
    else {
        if ((*t)->key < key) {
            removeAt(&(*t)->r, key);
        }
        else {
            removeAt(&(*t)->l, key);
        }
    }
}

void add(pNode* t, pNode a)
{
    if (*t == NULL) {
        *t = a;
    }
    else if (a->priority < (*t)->priority) {
        split(*t, a->key, &(a->l), &(a->r));
        *t = a;
    }
    else
    {
        if ((*t)->key < a->key) {
            add(&((*t)->r), a);
        }
        else {
            add(&((*t)->l), a);
        }
    }
}

void freeTree(pNode t) { // accurate
    if (!t) return;
    freeTree(t->l);
    freeTree(t->r);
    free(t);
}

void printTree(pNode root, int space) {
    if (!root) return;


    space += 5;

    printTree(root->r, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d(%d)\n", root->key, root->priority);

    printTree(root->l, space);
}