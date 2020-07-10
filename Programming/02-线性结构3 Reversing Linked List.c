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
        for (int i = 0; i < n &&
         scanf("%d %d %d", &node.address, &node.data, &node.next) == 3; i++)
        {
            src[node.address] = node;
        }
    }

    Node list[n];
    int i, p;
    for (p = head, i = 0; p != -1; p = src[p].next, i++) {
        list[i] = src[p];
    }
    n = i;  // 有多余结点不在链表上给出的节点数N不一定是
            // 最终形成的单链表的节点数也就是说，可能给你N个节点，但是不一定都能用得上
            // 所以保存实际能连成链表的结点数

    for (int i = 0; i < n; i++) {
        if (i % k == k - 1) {
            // 逆转 next
            int next = list[i].next;
            for (int j = i; j > i - k + 1; j--) {
                list[j].next = list[j-1].address;
            }
            list[i-k + 1].next = next;

            // 逆转结点在数组中的位置
            for (int j = i, q = i - k + 1; q < j; j--, q++) {
                Node t;
                t = list[j], list[j] = list[q], list[q] = t;
            }
        }
    }

    // 更新一遍 逆转处的 next
    for (int i = 0; i < n; i++) {
        if (i % k == k - 1) {
            if (i-k+1 > 0) {
                list[i - k].next = list[i-k+1].address;
            }
        }
    }


    // 最后 其实可以在按链表顺序存成数组后直接逆序数组，然后直接输出
    for (int i = 0; i < n - 1; i++) {
        printf("%05d %d %05d\n", list[i].address, list[i].data, list[i].next);
    }
    printf("%05d %d %d\n", list[n-1].address, list[n-1].data, list[n-1].next);
    return 0;
}
