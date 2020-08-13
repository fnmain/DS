#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

#define max(a, b) ((a) > (b) ? (a) : (b))

struct activity {
    int id;
    int lasting;
    struct activity *next;
};

int main(int argc, char const *argv[])
{
    int n, m;
    struct activity graph[MAX_N] = { 0 };   // 一个有向带权重的图
    int earliest[MAX_N] = { 0 };            // 从起点到任一点的 earliest

    scanf("%d %d", &n, &m);

    int i, s, e, l;
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &s, &e, &l);
        struct activity *p = malloc(sizeof(struct activity));
        p->next = NULL;
        p->id = e;
        p->lasting = l;

        struct activity *last = &graph[s];
        while ( last->next ) {
            last = last->next;
        }
        last->next = p;
    }

    // topological sorting
    int indegree[MAX_N] = { 0 };
    for (i = 0; i < n; i++) {
        struct activity *p = graph[i].next;
        while (p) {
            indegree[p->id]++;
            p = p->next;
        }
    }
    

    int q[MAX_N], h = 0, t = 0;
    for (i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q[t = (t + 1) % MAX_N] = i;
        }
    }

    for (i = 0; i < n && h != t; i++) {
        int vertex = q[h = (h + 1) % MAX_N];
        struct activity *p = graph[vertex].next;
        while (p != NULL) {
            indegree[p->id]--;
            earliest[p->id] = max(earliest[p->id], earliest[vertex] + p->lasting);
            if (indegree[p->id] == 0) {
                q[t = (t + 1) % MAX_N] = p->id;
            }
            p = p->next;
        }
    }

    if (i < n) {
        printf("Impossible\n");
    } else {
        int max = earliest[0];
        for (i = 1; i < n; i++) {
            if (earliest[i] > max) {
                max = earliest[i];
            }
        }
        printf("%i\n", max);
    }

    return 0;
}
