#include <stdio.h>

#define N 100

void shiftDown(int p, int a[], int len)
{
    int parent, child;
    int temp = a[p];
    for (parent = p; parent * 2 + 1 < len; parent = child) {
        child = parent * 2 + 1;
        if (child + 1 < len && a[child + 1] > a[child])
            child = child + 1;
        if (a[child] > temp)
            a[parent] = a[child];
        else
            break;
    }
    a[parent] = temp;
}

int main(int argc, char const *argv[])
{
    int a[N];
    int b[N];
    int i, n;
    
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    int index;
    for (i = 1; i < n; i++) {
        if (b[i] < b[i-1]) {
            index = i;
            break;
        }
    }

    int isInsertion = 1;
    for (i = index; i < n; i++) {
        if (a[i] != b[i]) {
            isInsertion = 0;
            break;
        }
    }
    
    if (isInsertion) {
        printf("Insertion Sort\n");
        int temp = b[index];
        for (i = index; i > 0 && b[i - 1] > temp; i--) {
            b[i] = b[i-1];
        }
        b[i] = temp;
    } else {
        printf("Heap Sort\n");
        int end = 0;
        for (i = 0; i < n; i++) {
            if (b[i+1] > b[0]) {
                end = i;
                int temp;
                temp = b[i];
                b[i] = b[0];
                b[0] = temp;
                break;
            }
        }
        shiftDown(0, b, end);
    }

    for (i = 0; i < n; i++) {
        printf("%d%s", b[i], i + 1 < n ? " " : "\n");
    }
    return 0;
}
