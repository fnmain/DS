#include <stdio.h>
#include <stdbool.h>

struct item {
    int data;
    bool taken;
};

#define HASHSIZE 1001
struct item hashtab[HASHSIZE];

struct node {
    int value;
    int index;
};

struct node heap[HASHSIZE+5] = {{-1}};

static int p = 1;
static int heap_size = 0;

void shiftUp(void)
{
    int current;
    struct node temp = heap[heap_size];
    for (current = heap_size; heap[current / 2].value > temp.value; current = current / 2) {
        heap[current] = heap[current/2];
    }
    heap[current] = temp;
}

void shiftDown(void)
{
    int parent, child;
    struct node temp = heap[1];
    for (parent = 1; parent * 2 < p; parent = child) {
        child = parent * 2;
        if (child + 1 < p && heap[child + 1].value < heap[child].value) {
            child = child + 1;
        }
        if (heap[child].value < temp.value) {
            heap[parent] = heap[child];
        } else {
            break;
        }
    }
    heap[parent] = temp;
}

void heap_add(int value, int index)
{
    heap[p].value = value;
    heap[p].index = index;
    p++;
    heap_size++;
    shiftUp();
}

struct node heap_pop(void)
{
    struct node ret = heap[1];
    heap[1] = heap[heap_size];
    heap_size--;
    p--;

    shiftDown();
    return ret;
}

int hsize(void)
{
    return heap_size;
}

// find a min-value's id, the min-value grater than base
// int find_min(int base, int n)
// {
//     int i;
//     int min = 0x7FFFFFFF;   // INT_MAX for 4 Bytes
//     int index = -1;

//     for (i = 0; i < n; i++) {
//         if ((!hashtab[i].taken && hashtab[i].data > base) && hashtab[i].data < min) {
//             min = hashtab[i].data;
//             index = i;
//         }
//     }
//     return index;
// }
/**
 * 0. base = -1
 * 1. 找大于 base 的还没被 taken 的最小值, 得到这个最小值的下标 minid
 * 2. 从 hashval 到 minid 是否都被 taken 了（如果 minid 小于 hashval，要从 hashval 向后找再求余数从头找到 minid）
 *      * 是，这个最小值可以这个时候插入，输出这个最小值，重新让（base = -1)
 *      * 否，找一个大于这个最小值的最小值，再做步骤 2（i.e. base = 当前的最小值）
 * 用暴力查找最小值会超时，维护一个最小堆
 */
int main(int argc, char const *argv[])
{
    int i, n;
    int first = 1;
    if (scanf("%d", &n) == 1) {
        for (i = 0; i < n && scanf("%d", &hashtab[i].data) == 1; i++) {
            if (hashtab[i].data <= -1)
                hashtab[i].taken = true;
            else
                heap_add(hashtab[i].data, i);
        }

        int minid = -1, hashval;
        struct node q[HASHSIZE];
        int h = 0, t = 0;
        while (hsize() > 0) {
            bool flag = true;
            struct node node = heap_pop();
            minid = node.index;
            hashval = hashtab[minid].data % n;
            for (i = hashval; i < minid || i > minid; i = (i + 1) % n) {
                if (hashtab[i].taken == false) {
                    flag = false;
                    q[t = (t + 1) % HASHSIZE] = node;
                    break;
                }
            }
            if (flag == true) {
                hashtab[minid].taken = true;
                printf(first ? "%d" : " %d", hashtab[minid].data);
                first = 0;

                while (h != t) {
                    h = (h+1) % HASHSIZE;
                    heap_add(q[h].value, q[h].index);
                }
            }
        }
    }
    printf("\n");
    return 0;
}

