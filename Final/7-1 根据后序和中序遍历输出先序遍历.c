#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int value;
    struct tnode *left;
    struct tnode *right;
};

struct tnode* talloc(void)
{
    return (struct tnode*)malloc(sizeof(struct tnode));
}

struct tnode* build_tree(int post_order[], int i, int j, int mid_order[], int p, int q)
{
    if (i <= j) {
        int k;
        struct tnode *root = talloc();
        root->value = post_order[j];

        for (k = p; k <= q; k++) {
            if (mid_order[k] == post_order[j])
                break;
        }

        root->left = build_tree(post_order, i, i + (k - p)-1, mid_order, p, k-1);
        root->right = build_tree(post_order, i + (k - p), j - 1, mid_order, k+1, q);
        return root;
    } else
        return NULL;
}

void treeprint(struct tnode *root)
{
    if (root != NULL) {
        printf(" %d", root->value);
        treeprint(root->left);
        treeprint(root->right);
    }
}

#define N 30

int main(int argc, char const *argv[])
{
    int post_order[N];
    int mid_order[N];

    int i, n;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &post_order[i]);
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &mid_order[i]);
    }
    
    struct tnode *root = build_tree(post_order, 0, n-1, mid_order, 0, n-1);

    printf("Preorder:");
    treeprint(root);
    printf("\n");
    return 0;
}
