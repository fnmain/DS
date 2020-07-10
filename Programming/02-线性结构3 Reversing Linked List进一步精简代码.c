#include <stdio.h>

typedef struct _node
{
    int address;
    int data;
    int next;
} Node;

int main(int argc, char const *argv[])
{
    Node src[100000];

    int head, k, n;
    if (scanf("%d %d %d", &head, &n, &k) == 3) {
        Node node;
        while (scanf("%d %d %d", &node.address, &node.data, &node.next) == 3)
        {
            src[node.address] = node;
        }
    }

    Node list[n];
    int p, i;
    for (p = head, i = 0; p != -1; p = src[p].next, i++) {
        list[i] = src[p];
    }
    n = i;

    for (int i = k - 1; i < n; i += k) {
        if (i % k == k - 1) {
            for (int j = i, q = i - k + 1; q < j; j--, q++) {
                Node t;
                t = list[j], list[j] = list[q], list[q] = t;
            }
        }
    }

    for (int i = 0; i < n - 1; i++) {
        printf("%05d %d %05d\n", list[i].address, list[i].data, list[i+1].address);
    }
    printf("%05d %d %d\n", list[n-1].address, list[n-1].data, -1);
    return 0;
}
