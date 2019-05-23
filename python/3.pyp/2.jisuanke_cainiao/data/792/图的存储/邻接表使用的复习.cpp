#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000

typedef struct Node {
    int vertex;
    struct Node *next;
} Node, *LinkedList;

LinkedList insert_node(LinkedList head, int index) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->vertex = index;
    node->next = head;
    head = node;
    return head;
}

typedef struct Graph {
    LinkedList edges[MAX_N];
    int n;
} Graph;

void init(Graph *g, int n) {
    g->n = n;
    for(int i = 0; i < g->n; i++){
        g->edges[i] = NULL;
    }
}

void insert(Graph *g, int a, int x, int y) {
   if(x < 0 || x >= g->n || y < 0 || y >= g->n){
       return ;
   } 
    g->edges[x] = insert_node(g->edges[x],y);
    a == 1 && (g->edges[y] = insert_node(g->edges[y],x),1);
    return ;
}

void output(Graph *g) {
    for(int i = 0; i < g->n; i++){
        printf("%d:",i);
        for(Node *j = g->edges[i]; j != NULL; j = j->next){
            printf(" %d",j->vertex);
        }
        printf("\n");
    }
}

void clear(Graph *g) {
    for(int i = 0; i < g->n; i++){
        Node *head = g->edges[i];
        while(head != NULL){
            Node *delete_node = head;
            head = head->next;
            free(delete_node);
        }
    }
    free(g->edges);
    free(g);
}

int main() {
    int n,m,a,b,c;
    scanf("%d%d",&n,&m);
    Graph *g = (Graph *)malloc(sizeof(Graph));
    init(g,n);
    for(int i = 0; i< m; i++){
        scanf("%d%d%d",&a,&b,&c);
        insert(g,a,b,c);
    }
    output(g);
    return 0;
}