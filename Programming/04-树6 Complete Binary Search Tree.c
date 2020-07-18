#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1001

// the height of a perfect binary tree
// n is the number of tnode
int pbtheight(int n)
{
    return log2(n);
}

// the number of node of a perfect binary tree
int pbtnodes(int height)
{
    return pow(2, height) - 1;
}

// the number of leaf node of a complete binary tree
// n is the number of tnode
int cbtleafs(int n)
{
    return n - (pow(2, pbtheight(n)) - 1);
}

// maximum the number of node complete binary tree on left of last layer
int maxcbtleftleafs(int n)
{
    return pow(2, pbtheight(n) - 1);
}

// left subtree nodes of perfect binary tree
int pbtleftsubtreenodes(int n)
{
    return (pbtnodes(pbtheight(n)) - 1) / 2;
}

// left subtree nodes of complete binary tree
int cbtleftsubtreenodes(int n)
{
    return pbtleftsubtreenodes(n) + (cbtleafs(n) > maxcbtleftleafs(n) ? maxcbtleftleafs(n) : cbtleafs(n));
}


void generate_tree(int *a, int left, int right, int *tree, int root)
{
    if (left <= right) {
        int offset = cbtleftsubtreenodes(right - left + 1);
        // printf("offset = %d\n", left + offset);
        tree[root] = a[left + offset];
        // printf("tree[%d] = %d\n", root, tree[root]);
        generate_tree(a, left, left + offset - 1, tree, root * 2);
        generate_tree(a, left + offset + 1, right, tree, root * 2 + 1);
    }
}

int cmp(const void *a, const void *b)
{
    return (*(int*)a) - (*(int*)b);
}

int main(int argc, char const *argv[])
{
    int n = 15;
    int a[N];
    int tree[N];
    if (scanf("%d", &n) == 1) {
        for (int i = 0; i < n && scanf("%d", &a[i]); i++)
            ;

        qsort(a, n, sizeof(int), cmp);

        generate_tree(a, 0, n - 1, tree, 1);

        for (int i = 1; i <= n; i++) {
            printf("%d%s", tree[i], i == n ? "\n" : " ");
        }
    }
    return 0;
}
