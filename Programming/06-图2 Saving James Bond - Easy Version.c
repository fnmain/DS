#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 100

struct location {
    double x;
    double y;
};

double land = 15 / 2;  // 岛的半径
int yes = 0;

void dfs(struct location loc[], int n, double d, bool visited[], struct location v)
{
    d = d + land;
    if (v.x - d <= -50 || v.x + d >= 50 || v.y + d  >= 50 || v.y - d <= -50) {
        yes = 1;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            double distance = sqrt(pow((v.x - loc[i].x), 2) + pow(v.y - loc[i].y, 2));
            if (distance <= d) {
                land = 0;
                visited[i] = true;
                dfs(loc, n, d, visited, loc[i]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    // 只是存储了所有的点,搜寻能跳到的点,用 dfs 遍历
    struct location loc[N];
    bool visited[N] = {false};
    int n, d;

    scanf("%i %i", &n, &d);

    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &loc[i].x, &loc[i].y);
    }

    dfs(loc, n, d, visited, (struct location){0, 0});

    if (yes) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}
