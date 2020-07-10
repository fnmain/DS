#include <stdio.h>

int max(int a, int b) { return a > b ? a : b; }

int main(int argc, char const *argv[])
{
    int x, n;
    int maxsum = 0;
    int sum = 0;

    if (scanf("%d", &n) == 1) {
        for (int i = 0; i < n && scanf("%d", &x) == 1; i++) {
            sum = max(sum + x, x);
            maxsum = max(maxsum, sum);
        }
    }

    printf("%d\n", maxsum);

    return 0;
}
