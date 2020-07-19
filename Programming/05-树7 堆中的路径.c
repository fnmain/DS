#include <stdio.h>

#define N 1001

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char const *argv[])
{
    int heap[N];
    heap[0] = -10001;

    int n, m;

    if (scanf("%d %d", &n, &m) == 2) {
        int i, j;
        for (i = 1; i <= n && scanf("%d", &heap[i]) == 1; i++) {
            for (j = i; heap[j/2] > heap[j]; j /= 2) {
                swap(&heap[j], &heap[j/2]);
            }
        }
        for (i = 0; i < m && scanf("%i", &j) == 1; i++) {
            while (j > 0) {
                printf("%i%s", heap[j], j / 2  == 0 ? "\n" : " ");
                j /= 2;
            }
        }
    }

    
    return 0;
}
