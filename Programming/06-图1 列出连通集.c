#include <stdio.h>

#define N 10

void dfs(int g[][N], int v, int n, int *visited)
{
    int i, j;
    printf("%d ", v);
    visited[v] = 1;
    for (i = 0; i < n; i++) {
        if (g[v][i] && !visited[i]) {
            dfs(g, i, n, visited);
        }
    }
}

void bfs(int g[][N], int v, int n, int *visited)
{
    int q[N];
    int h, t;
    h = t = 0;

    q[t = (t + 1) % N] = v;
    printf("%d ", v);
    visited[v] = 1;
    while (t > h) {
        int vertex = q[h = (h + 1) % N];
        for (int i = 0; i < n; i++) {
            if (g[vertex][i] && !visited[i]) {
                printf("%d ", i);
                visited[i] = 1;
                q[t = (t + 1) % N] = i;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int g[N][N] = {0};
    int visited[N] = {0};
    int n, e;
    int i, col, row;

    scanf("%i %i", &n, &e);
    for (i = 0; i < e; i++) {
        scanf("%i %i", &col, &row);
        g[col][row] = g[row][col] = 1;
    }

    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("{ ");
            // DFS
            dfs(g, i, n, visited);
            printf("}\n");
        }
    }

    // reset visited[]
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("{ ");
            // BFS
            bfs(g, i, n, visited);
            printf("}\n");
        }
    }

    return 0;
}
