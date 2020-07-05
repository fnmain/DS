#include <stdio.h>

int maxSubseqSum1(int a[], int n)
{
    int maxsum = 0;
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            int sum = 0;
            for (k = i; i <= j; k++) {
                sum += a[k];
            }
            if (sum > maxsum) {
                maxsum = sum;
            }
        }
    }
    return maxsum;
}

// 中间子序列的增长每次都是增加一个，所以可以更优化一步
int maxSubseqSum2(int a[], int n)
{
    int maxsum = 0;
    int i, j, k;
    for (i = 0; i < n; i++) {
        int sum = 0;
        for (j = i; j < n; j++) {
            sum += a[j];
            if (sum > maxsum) {
                maxsum = sum;
            }
        }
    }
    return maxsum;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
