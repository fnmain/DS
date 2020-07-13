#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct tnode {
    int data;
    struct tnode *left;
    struct tnode *right;
};

// 添加 number 到树上
struct tnode *addtree(struct tnode *p, int number);
// 从输入生成一颗树
struct tnode *readtree(struct tnode *p, int n);
struct tnode *talloc(void);
bool isomorphism(struct tnode *p, struct tnode *q);
struct tnode *treefree(struct tnode *p);

int main(int argc, char const *argv[])
{
    int N;
    int L;

    while ((scanf("%d", &N) == 1 && N > 0) && scanf("%d", &L) == 1) {
        // struct tnode *root = NULL;
        // for (int i = 0; i < N && scanf("%d", &number) == 0; i++) {
        //     root = addtree(root, number);
        // }
        struct tnode *root = NULL;
        root = readtree(root, N);
        for (int i = 0; i < L; i++) {
            struct tnode *tree = readtree(NULL, N);
            if (isomorphism(root, tree)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
            tree = treefree(tree);
        }
        root = treefree(root);
    }

    return 0;
}

struct tnode *addtree(struct tnode *p, int number)
{
    if (p == NULL) {
        p = talloc();
        p->data = number;
        p->left = p->right = NULL;
    } else if (number > p->data) {
        p->right = addtree(p->right, number);
    } else {
        p->left = addtree(p->left, number);
    }
    return p;
}

struct tnode *readtree(struct tnode *p, int n)
{
    int number;
    for (int i = 0; i < n && scanf("%d", &number) == 1; i++) {
        p = addtree(p, number);
    }
    return p;
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

bool isomorphism(struct tnode *p, struct tnode *q)
{
    bool yes = 0;
    if ((p && q) && p->data == q->data) {
        yes = isomorphism(p->left, q->left)
        && isomorphism(p->right, q->right);
    } else if (q == NULL && p == NULL) {
        yes = true;
    }
    return yes;
}

struct tnode *treefree(struct tnode *p)
{
    if (p != NULL) {
        p->left = treefree(p->left);
        p->right = treefree(p->right);
        if (p->left == NULL && p->right == NULL) {
            free(p);
            p = NULL;
        }
    }
    return p;
}