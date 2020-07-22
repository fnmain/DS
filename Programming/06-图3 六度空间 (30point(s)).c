#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 1001

struct vertex {
    int id;
    struct vertex* next;
};

void addedge(struct vertex g[], int from, int to)
{
    struct vertex *p = &g[from];
    while (p->next) {
        p = p->next;
    }
    p->next = malloc(sizeof(struct vertex));
    p->next->id = to;
    p->next->next = NULL;
}

int q[N], h = 0, t = 0;

int bfs(struct vertex g[], int from)
{
    bool visited[N] = {false};
    int count = 0;
    int last = from;
    int layer = 0;
    h = t = 0;
    q[t = (t + 1) % N] = from;
    visited[from] = true;
    while ( t != h && layer <= 6) {
        int current_v = q[h = (h + 1) % N];
        count++;
        
        // enqueue adjcent vertex
        struct vertex *p = NULL;
        for (p = g[current_v].next; p != NULL; p = p->next) {
            if (!visited[p->id]) {
                visited[p->id] = true;
                q[t = (t + 1) % N] = p->id;
            }
        }

        if (current_v == last) {
            if ( t != h) {
                last = q[t];
            }
            layer++;
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    struct vertex g[N] = { 0 };

    int n, e;

    scanf("%i %i", &n, &e);

    int i;
    for (i = 0; i < e; i++) {
        int row, col;
        scanf("%i %i", &row, &col);
        addedge(g, row, col);
        addedge(g, col, row);
    }

    for (i = 1; i <= n; i++) {
        printf("%i: %.2f%%\n", i, bfs(g, i) * 100.0 / n);
    }
    return 0;
}
