#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 100

#define min(a, b) ((a) > (b) ? (b) : (a))

struct location
{
    double x;
    double y;
};

double land = 15 / 2; // 岛的半径

int q[N], h = 0, t = 0;

int bfs(struct location loc[], int n, double d, int s, int path[])
{
    int i;
    bool visited[N] = {false};
    // printf("s = %i\n", s);
    h = 0, t = 0;
    q[t = (t + 1) % N] = s;
    visited[s] = true;

    while (t != h)
    {
        int v = q[h = (h + 1) % N];
        // visited[v] = true;
        // printf("from %i: %g %g\n", v, loc[v].x, loc[v].y);
        if (loc[v].x - d <= -50 || loc[v].x + d >= 50 || loc[v].y + d >= 50 || loc[v].y - d <= -50)
        {
            // printf("successful\n");
            return v;
        }

        // find adjcent
        for (i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                double distance = sqrt(pow((loc[v].x - loc[i].x), 2) + pow(loc[v].y - loc[i].y, 2));
                if (distance <= d)
                {
                    visited[i] = true;
                    q[t = (t + 1) % N] = i;
                    // printf("  to %i: %g %g\n", i, loc[i].x, loc[i].y);
                    // the path to i from v
                    path[i] = v;
                    // printf("path[%i] = %i\n", i, v);
                }
            }
        }
    }
    return -1;
}

/* 写编程题的时候可能会用到队列或者堆栈，
如果可以的话，有个很好的偷懒的方式，函数的递归调用就是堆栈，
所以要用堆栈的直接写成递归，其实不过是在用编程语言就提供的堆栈。
如果编程语言自带的库没有提供队列这种数据结构，那就直接写个数组，
当循环队列用。这两种方法结合起来，即便是编程语言没有自带堆栈和队列也可以省去自己实现的麻烦 */

void pathprint(struct location loc[], int path[], int idx, int depth)
{
    if (idx != -1)
    {
        pathprint(loc, path, path[idx], depth + 1);
        printf("%g %g\n", loc[idx].x, loc[idx].y);
    } else {
        printf("%d\n", depth);
    }
}

double distance(struct location a, struct location b)
{
    return sqrt(pow((a.x - b.x), 2) + pow(a.y - b.y, 2));
}

void saveshortestpath(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main(int argc, char const *argv[])
{
    // 无权图的单源最短路径
    struct location loc[N];
    int path[N];
    int shortest_path[N];
    int n, d, yes = 0;

    scanf("%i %i", &n, &d);

    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%lf %lf", &loc[i].x, &loc[i].y);
    }

    if (d > 42) {
        printf("1\n");
    } else {

        int begin, end;
        for (i = 0; i < n; i++)
        {
            double dis = sqrt(pow((0 - loc[i].x), 2) + pow(0 - loc[i].y, 2));
            if (dis <= d + land && dis > land)
            {
                path[i] = -1;
                int ret;
                if ((ret = bfs(loc, n, d, i, path)) != -1)
                {
                    if (yes && dis < distance((struct location){0, 0}, loc[begin]))
                    { // 若之前有能走通的路 并且跳出的距离更短
                        begin = i;
                        end = ret;
                        saveshortestpath(path, shortest_path, N);
                    }
                    else if ( !yes )
                    {
                        saveshortestpath(path, shortest_path, N);
                        yes = 1;
                        begin = i;
                        end = ret;
                    }
                }
            }
        }

        if (yes)
        {
            pathprint(loc, shortest_path, end, 1);
        }
        else
        {
            printf("0\n");
        }
    }
    return 0;
}
