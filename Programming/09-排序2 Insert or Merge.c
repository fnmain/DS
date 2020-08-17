#include <stdio.h>

#define N 100

int temp[1000000];
// 归并排序（非递归）
void bottom_up_merge(int v[], int left, int right, int end)
{
    int i, j, k;
    i = left;
    j = right;
    for (k = left; k < end; k++) {
        if (i < right && (v[i] < v[j] || j >= end)) {
            temp[k] = v[i++];
        } else {
            temp[k] = v[j++];
        }
    }
}

void copy_array(int dest[], int src[], int len)
{
    int i;

    for (i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

static inline int min(int i, int j) { return i < j ? i : j; }

void bottom_up_merge_sort(int v[], int len, int width)
{
    int i;
    for (i = 0; i < len; i += 2 * width) {
        bottom_up_merge(v, i, min(i + width, len), min(i + 2 * width, len));
    }
    copy_array(v, temp, len);
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
        printf("Merge Sort\n");
        int width;
        for (width = 1; width < n; width *= 2) {
            bottom_up_merge_sort(a, n, width);
            int equals = 1;
            for (i = 0; i < n; i++) {
                if (a[i] != b[i]) {
                    equals = 0;
                    break;
                }
            }
            if (equals) {
                width *= 2;
                bottom_up_merge_sort(a, n, width);
                copy_array(b, a, n);
                break;
            }
        }
    }

    for (i = 0; i < n; i++) {
        printf("%d%s", b[i], i + 1 < n ? " " : "\n");
    }
    return 0;
}
