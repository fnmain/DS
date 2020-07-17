#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int data;
    struct tnode *left;
    struct tnode *right;
    int height;
};

int max(int a, int b);
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *p, int num);
int height(struct tnode *p);

int main(int argc, char const *argv[])
{
    int n;
    if (scanf("%d", &n) == 1) {
        int i, number;
        struct tnode *root = NULL;
        for (i = 0; i < n && scanf("%d", &number) == 1; i++) {
            root = addtree(root, number);
        }
        if (root)
            printf("%d\n", root->data);
    }
    return 0;
}


int max(int a, int b)
{
    return a > b ? a : b;
}

int height(struct tnode *p)
{
    if (p == NULL) {
        return 0;
    }
    return p->height;
}

struct tnode *talloc(void)
{
    return malloc(sizeof(struct tnode));
}

struct tnode *rightRotation(struct tnode *p)
{
    struct tnode *temp;
    temp = p->left;
    p->left = temp->right;
    temp->right = p;
    p->height = max(height(p->left), height(p->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    p = temp;
    return p;
}

struct tnode *leftRotation(struct tnode *p)
{
    struct tnode *temp;
    temp = p->right;
    p->right = temp->left;
    temp->left = p;
    p->height = max(height(p->left), height(p->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    p = temp;
    return p;
}

struct tnode *addtree(struct tnode *p, int num)
{
    if (p == NULL) {
        p = talloc();
        p->data = num;
        p->left = p->right = NULL;
        p->height = 1;
        return p;
    } else if (num > p->data) {
        p->right = addtree(p->right, num);
    } else if (num < p->data) {
        p->left = addtree(p->left, num);
    }

    p->height = max(height(p->left), height(p->right)) + 1;

    // printf("p->data = %d, height(p->left) = %d, height(p->right)=%d\n", p->data, subtreeheight(p->left), subtreeheight(p->right));
    // check balance
    if (height(p->left) - height(p->right) > 1) {
        if (height(p->left->left) > height(p->left->right)) {
            // right rotation
            p = rightRotation(p);
        } else {
            // left right rotation
            p->left = leftRotation(p->left);
            p = rightRotation(p);
        }
    } else {
        if (height(p->right) - height(p->left) > 1) {
            if (height(p->right->right) > height(p->right->left)) {
                // left rotation
                p = leftRotation(p);
            } else {
                // right left rotation
                p->right = rightRotation(p->right);
                p = leftRotation(p);
            }
        }
    }
    return p;
}