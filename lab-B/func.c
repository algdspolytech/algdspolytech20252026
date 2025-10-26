#include <stdlib.h>


 struct Node{
    int vertex;
    struct Node* next
 };


 struct Graph{
    int numVertices;
    struct Node** node_list;
 };


 struct Node* create_node(int v){
    struct Node* new_node=(struct Node*)malloc(sizeof(struct Node));
    new_node->vertex=v;
    new_node->next=NULL;
    return new_node;
 }
 struct Graph* create_graph(int vertuces){
    struct Graph* new_graph=(struct Graph*)malloc(sizeof(struct Graph));
    new_graph->numVertices=vertuces;

    new_graph->node_list=(struct Node*)malloc(vertuces*sizeof(struct Node*));
    for(int i=0;i<vertuces;i++){
        new_graph->node_list=NULL;
    }
    return new_graph;
 }
