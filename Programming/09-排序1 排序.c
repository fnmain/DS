#include <stdio.h>
#include <stdlib.h>

int max(int a[], int len)
{
    int maxid = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] > a[maxid]) {
            maxid = i;
        }
    }
    return maxid;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);

    int *const a = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = n; i > 0; i--) {
        int maxid = max(a, i);
        int t = a[maxid];
        a[maxid] = a[i - 1];
        a[i - 1] = t;
    }

    for (int i = 0; i < n; i++) {
        printf("%d%s", a[i], i + 1 == n ? "\n" : " ");
    }
    
    return 0;
}
