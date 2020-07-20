/*
首先根据频率生成 Huffman Tree，计算它的 WPL
然后根据学生提交的编码生成一颗带权重的树，计算它的 WPL
然后比对两个 WPL 是否相等，和「根据学生提交的编码生成一颗带权重的树」的叶结点树是否等于 n
若「两个 WPL 相等」 且 「根据学生提交的编码生成一颗带权重的树」的叶结点树等于 n，则 Yes，否则 No
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 70

typedef struct tnode {
    int weight;
    struct tnode * left;
    struct tnode * right;
} Treenode;

void *talloc(void)
{
    return malloc(sizeof(Treenode));
}

void addheap(Treenode *p);
int sizeofheap(void);
Treenode *deletemin(void);

int huffman_wpl(Treenode *p, int depth)
{
    if (p) {
        if (p->left == NULL && p->right == NULL) {
            // printf("p->weight * depth = %d\n", p->weight * depth);
            return p->weight * depth;
        } else {
            return huffman_wpl(p->left, depth + 1) + huffman_wpl(p->right, depth + 1);
        }
    } else {
        return 0;
    }
}

int count_leafs(Treenode *p)
{
    if (p == NULL) {
        return 0;
    }
    if (p->left == NULL && p->right == NULL) {
        return 1;
    }
    return count_leafs(p->left) + count_leafs(p->right);
}

Treenode* addweight(Treenode *p, char *s, int weight)
{
    if (p) {
        p->weight += weight;
    } else {
        p = talloc();
        p->weight = weight;
        p->left = NULL;
        p->right = NULL;
    }
    if (strlen(s) > 0) {
        if (s[0] == '0') {
            p->left = addweight(p->left, s + 1, weight);
        } else if (s[0] == '1') {
            p->right = addweight(p->right, s+1, weight);
        }
    }
    return p;
}

int main(int argc, char const *argv[])
{

    int i, j, n, x;
    scanf("%i", &n);
    char c[N];
    int f[N];

    for (i = 0; i < n; i++) {
        scanf("%s", &c[i]);
        scanf("%i", &x);
        Treenode *p = talloc();
        p->left = NULL;
        p->right = NULL;
        p->weight = x;
        f[i] = x;
        addheap(p);
    }

    while (sizeofheap() > 1)
    {
        Treenode *p = talloc();
        p->left = deletemin();
        p->right = deletemin();
        // printf("p->left->weight = %d\n", p->left->weight);
        // printf("p->right->weight = %d\n", p->right->weight);
        p->weight = p->left->weight + p->right->weight;
        addheap(p);
    }
    Treenode *huffman_root = deletemin();

    int wpl =  huffman_wpl(huffman_root, 0);


    int m;
    scanf("%i", &m);


    for (i = 0; i < m; i++) {
        Treenode *root = talloc();
        root->weight = 0;
        root->left = NULL;
        root->right = NULL;
        for (j = 0; j < n; j++) {
            scanf("%s", c);
            scanf("%s", c);
            int weight = f[j];

            addweight(root, c, weight);
        }
        // printf("%i\n" , huffman_wpl(root, 0));
        if (huffman_wpl(root, 0) == wpl && count_leafs(root) == n) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
    return 0;
}

Treenode *heap[N];
int size = 1;

void addheap(Treenode *p)
{
    heap[size++] = p;
    for (int i = size - 1; heap[i/2] != NULL && heap[i] != NULL; i /= 2) {
        if (heap[i]->weight < heap[i/2]->weight) {
            Treenode *temp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = temp;
        }
    }
}

int sizeofheap(void)
{
    return size - 1;
}

void swap(Treenode **a, Treenode **b) {
    Treenode *t = *a;
    *a = *b;
    *b = t;
}

Treenode *deletemin(void)
{
    Treenode *ret = heap[1];
    heap[1] = heap[--size];
    heap[size] = NULL;
    int next;
    for (int p = 1; p * 2 < size; p = next) {
        next = p * 2;
        if (next + 1 < size && (heap[next + 1]->weight < heap[next]->weight)) {
            next = next + 1;
        }
        if (heap[next]->weight < heap[p]->weight) {
            swap(&heap[next], &heap[p]);
        } else {
            break;
        }
    }

    return ret;
}