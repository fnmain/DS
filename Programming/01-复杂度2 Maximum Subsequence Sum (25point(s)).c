#include <stdio.h>

//int max(int a, int b) { return a > b ? a : b; }

#define max(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char const *argv[])
{
    // 每次开始新的子序列记录一个位置，当更新最大子序列和的时候更新最大子序列和的 start 和 end。
    int x, n;
    int maxsum = -1;    // for case 5 如果都是负数和 0，则 maxsum 会更新为 0，这样就会 更新 first 和 last
    int sum = 0;        // 如果全是负数，maxsum 最终会小于 0, 所以在第 30 行的输出加上判断

    if (scanf("%d", &n) == 1) {
        int a[n];
        int first = 0, last = n - 1, t = 0;
        for (int i = 0; i < n && scanf("%d", &x) == 1; i++) {
            a[i] = x;
            if (sum + x < x) {
                t = i;
            }
            sum = max(sum + x, x);
            if (sum > maxsum) {
                first = t;
                last = i;
            }
            maxsum = max(maxsum, sum);
        }
    
        printf("%d %d %d\n", maxsum < 0 ? 0 : maxsum, a[first], a[last]);
    }


    return 0;
}
