#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 1001

struct node {
    int start;
    int dest;
    int cost;
};

#define SWAP(a, b) do { struct node t; t = (a), (a) = (b), (b) = (t); } while (0)

struct node heap[N] = {{0, 0, INT_MAX}};
int size = 0;

void addheap(int s, int d, int cost)
{
    size++;
    heap[size].start = s;
    heap[size].dest = d;
    heap[size].cost = cost;

    for (int p = size; p / 2 && heap[p/2].cost > heap[p].cost; p /= 2) {
        SWAP(heap[p/2], heap[p]);
    }
}

int heapsize(void)
{
    return size;
}

struct node delete_min(void)
{
    struct node ret = heap[1];
    heap[1] = heap[size--];
    int child;
    for (int p = 1; p * 2 <= size; p = child) {
        child = p * 2;
        if (child != size && heap[child].cost > heap[child + 1].cost) {
            child = child + 1;
        }
        if (heap[child].cost < heap[p].cost) {
            SWAP(heap[child], heap[p]);
        } else {
            break;
        }
    }
    return ret;
}

int findroot(int set[], int n)
{
    while (set[n] > 0) {
        n = set[n];
    }
    return n;
}

void setunion(int set[], int r1, int r2)
{
    if (set[r1] < set[r2]) {
        set[r1] -= set[r2];
        set[r2] = r1;
    } else {
        set[r2] -= set[r1];
        set[r1] = r2;
    }
}


/* 
用最小堆来保存预算成本，然后用 Kruskal 算法，每次选最短的路，
对于这条路的两个城市做一下并查集(Disjoint-set)，如果不是一个
集合的就连接起来，如果恰好选了 n - 1 条边就完成了
 */
int main(int argc, char const *argv[])
{
    int n, m;

    scanf("%d %d", &n, &m);

    int i, s, d, cost;
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &s, &d, &cost);
        addheap(s, d, cost);
    }

    int set[N];
    memset(set, -1, N);
    
    int min_cost = 0;
    int count = 0;
    while (heapsize() > 0) {
        struct node t = delete_min();
        int r1 = findroot(set, t.start);
        int r2 = findroot(set, t.dest);
        if (r1 != r2) {
            setunion(set, r1, r2);
            min_cost += t.cost;
            count++;
        }
    }

    printf("%d\n", count == n - 1 ? min_cost : -1);
    return 0;
}
