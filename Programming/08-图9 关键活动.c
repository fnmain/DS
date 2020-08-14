#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX 105
#define INF INT_MAX

static int queue[MAX];
static int front = 0, rear = 0;

static void enqueue(int val) { queue[rear = (rear + 1) % MAX] = val; }
static int dequeue(void) { return queue[front = (front + 1) % MAX]; }
static bool isEmpty(void) { return front == rear; }
static void clear(void) { front = rear = 0; }

static inline int maximum(int a, int b) { return a > b ? a : b; }
static inline int minimum(int a, int b) { return a < b ? a : b; }

typedef struct _graph {
    int *g;
    int n;
} Graph;

Graph create_graph(int n)
{
    Graph graph;
    int *p = (int*)malloc(sizeof(int) * (MAX * MAX));
    graph.n = n;
    for (int i = 0; i < (MAX * MAX); i++)
        p[i] = INF;
    graph.g = (void*)p;
    return graph;
}

void add_edge(Graph *g, int start, int end, int weight)
{
    int (*a)[MAX] = (void*)g->g;
    a[start - 1][end - 1] = weight;
}

void graph_free(Graph *g)
{
    free(g->g);
    g->n = 0;
    g->g = NULL;
}

int D[MAX][MAX];

// flag 0 indegree, 1 outdegree
void get_degree(Graph *g, int degree[], int flag)
{
    int (*a)[MAX] = (void*)g->g;
    int n = g->n;
    memset(degree, 0, sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != INF) {
                degree[flag == 0 ? j : i]++;
            }
        }
    }
}

void enqueue_zero_dgree(int degree[], int n)
{
    clear();
    for (int i = 0; i < n; i++) {
        if (degree[i] == 0) {
            enqueue(i);
        }
    }
}

int topological_sort(Graph *g)
{
    int n = g->n;
    int degree[MAX] = { 0 };
    int earlist[MAX] = { 0 };
    int (*a)[MAX] = (void*)g->g;

    get_degree(g, degree, 0);

    enqueue_zero_dgree(degree, n);
    
    int cnt, result = -1;
   
    memset(earlist, 0, sizeof(int)*n);
    for (cnt = 0; cnt < n && !isEmpty(); cnt++) {
        int v = dequeue();
        for (int i = 0; i < n; i++) {
            if (a[v][i] != INF) {
                if (--degree[i] == 0) {
                    enqueue(i);
                }
                earlist[i] = maximum(earlist[i], earlist[v] + a[v][i]);
                result = maximum(result, earlist[i]);
            }
        }
    }

    if (cnt == n) {
        int outdegree[MAX] = { 0 };
        get_degree(g, outdegree, 1);
        
        int latest[MAX];
        for (int i = 0; i < n; i++) latest[i] = result;
        
        enqueue_zero_dgree(outdegree, n);

        for (int k = 0; k < n; k++) {
            int v = dequeue();
            for (int i = 0; i < n; i++) {
                if (a[i][v] != INF) {
                    if (--outdegree[i] == 0) {
                        enqueue(i);
                    }

                    latest[i] = minimum(latest[i], latest[v] - a[i][v]);
                    D[i][v] = latest[v] - earlist[i] - a[i][v];
                }
            }
        }
    }
    
    return cnt == n ? result : -1;
}

int main(int argc, char const *argv[])
{
    int n, m;

    scanf("%d %d", &n, &m);

    Graph graph = create_graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            D[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        int s, e, l;
        scanf("%d %d %d", &s, &e, &l);
        add_edge(&graph, s, e, l);
    }

    int result;
    if ((result = topological_sort(&graph)) > 0) {
        printf("%d\n", result);
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0; j--) {
                if (D[i][j] == 0) {
                    printf("%d->%d\n", i + 1, j + 1);
                }
            }
        }
    } else {
        printf("0\n");
    }

    return 0;
}
