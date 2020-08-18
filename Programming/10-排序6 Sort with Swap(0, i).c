#include <stdio.h>

#define N 100000
/* 每次都和 0 做 swap，一次归位一个数字 */
int main(int argc, char const *argv[])
{
    int a[N];
    int visited[N] = {0};
    int n, i;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int sum = 0;
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            int index = i;
            int count = 0;  /* 环的元素个数，0 个不用做 swap */
            int next;
            while (a[index] != index) {
                visited[index] = 1;
                count++;
                next = a[index];
                a[index] = index;
                index = next;
            }
            if (count != 0) {
                sum = index == 0 ? sum + count - 1 : sum + count + 1;
            }
            // printf("index = %d, count = %d\n", index, count);
        }
    }
    printf("%d\n", sum);
    return 0;
}
