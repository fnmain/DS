#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 101

#define min(a, b) ((a) > (b) ? (b) : (a))

int dijkstra(int g[N][N], int source, int n)
{
    int dis[N];
    bool visited[N] = {false};

    int i;
    for (i = 0; i < N; i++) {
        dis[i] = INT_MAX;
    }

    int count = 0;
    // select the unvisited node that is marked with the smallest tentative distance
    dis[source] = 0;
    while ( 1 ) {
        int smallest_id = 0;
        for (i = 1; i < N; i++) {
            if (!visited[i] && dis[i] < dis[smallest_id]) {
                smallest_id = i;
            }
        }

        if (smallest_id == 0) {
            break;
        }

        int current_node = smallest_id;

        for (i = 1; i < N; i++) {
            if (!visited[i] && g[current_node][i] != 0) {
                dis[i] = min(dis[current_node] + g[current_node][i], dis[i]);
            }
        }

        visited[current_node] = true;
        count++;
    }
    if (count == n) {
        int longest = 0;
        for (i = 1; i <= n; i++) {
            if (dis[i] > longest) {
                longest = dis[i];
            }
        }
        return longest;
    }
    return INT_MAX;
}

int main(int argc, char const *argv[])
{
    int g[N][N] = {0};
    int n, m;

    scanf("%i %i", &n, &m);

    int i;
    int a, b, w;
    for (i = 0; i < m; i++) {
        scanf("%i %i %i", &a, &b, &w);
        g[a][b] = g[b][a] = w;
    }

    int minid = 0; // 所选的动物编号
    int result[N] = {INT_MAX};

    for (i = 1; i <= n; i++) {
        result[i] = dijkstra(g, i, n);
        if (result[i] < result[minid]) {
            minid = i;
        }
    }
    if (minid != 0)
        printf("%d %d\n", minid, result[minid]);
    else
        printf("0\n");

    return 0;
}
