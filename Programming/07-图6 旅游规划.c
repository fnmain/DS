#include <stdio.h>
#include <stdbool.h>

#define N 500

#define INF 300000

struct edge {
    int dis;
    int price;
};

void init_edge(struct edge g[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            g[i][j] = (struct edge){INF, INF};
        g[i][i] = (struct edge){0, 0};
    }
}

struct edge choose(struct edge a, struct edge b, struct edge c)
{
    struct edge ret = a;
    if (b.dis + c.dis < a.dis) {
        ret.dis = b.dis + c.dis;
        ret.price = b.price + c.price;
    } else if (b.dis + c.dis == a.dis && b.price + c.price < a.price) {
        ret.dis = b.dis + c.dis;
        ret.price = b.price + c.price;
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    struct edge g[N][N];
    init_edge(g);
    int n, m, s, d;

    scanf("%i %i %i %i", &n, &m, &s, &d);

    int i, src, dest, dis, price;
    for (i = 0; i < m; i++) {
        scanf("%i %i %i %i", &src, &dest, &dis, &price);
        g[src][dest] = g[dest][src] = (struct edge){dis, price};
    }

    struct edge dis_price[N];
    bool visited[N] = {false};

    for (i = 0; i < N; i++)
        dis_price[i] = (struct edge){INF, INF};

    dis_price[s].dis = dis_price[s].price = 0;

    while ( true ) {
        // find the min
        int min = -1;
        for (i = 0; i < n; i++) {
            if (!visited[i] && dis_price[i].dis < INF) {
                if (min == -1) {
                    min = i;
                } else if (dis_price[i].dis < dis_price[min].dis) {
                    min = i;
                }
            }
        }
        if (min == -1) {
            break;
        }

        int current_node = min;

        // find the adjcent node
        for (i = 0; i < n; i++) {
            if (!visited[i] && g[s][i].dis < INF) {
                dis_price[i] = choose(dis_price[i], dis_price[current_node], g[current_node][i]);
                // printf("%i: %d %d\n", i, dis_price[i].dis, dis_price[i].price);
            }
        }
        visited[current_node] = true;
    }
    printf("%d %d\n", dis_price[d].dis, dis_price[d].price);
    return 0;
}
