#include <stdio.h>
#include <stdlib.h>

#define N 30

// implementation stack
static int val[N];
static int sp = 0;

void push(int number)
{
    if (sp < N)
        val[sp++] = number;
    else
        printf("error: stack full, can't push %d\n", number);
}

int pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0;
    }
}

// queue
int q[N];
int h = 0;
int t = 0;

// treenode
struct tnode {
    int data;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void)
{
    return malloc(sizeof(struct tnode));
}

int findId(int a[], int left, int right)
{
    int key = q[h = (h + 1) % N];
    int i, ret;
    for (i = left; i <= right; i++) {
        if (a[i] == key) {
            ret = i;
        }
    }
    return ret;
}

struct tnode *generateTreeFromArray(int a[], int left, int right)
{
    struct tnode *p = NULL;
    
    if (left <= right) {
        int id = findId(a, left, right);
        p = talloc();
        p->data = a[id];
        p->left = generateTreeFromArray(a, left, id - 1);
        p->right = generateTreeFromArray(a, id + 1, right);
    }
    return p;
}

int thefirst;
void postorder_treeprint(struct tnode *p)
{
    if (p != NULL) {
        postorder_treeprint(p->left);
        postorder_treeprint(p->right);
        printf("%d%s", p->data, p->data == thefirst ? "\n" : " ");
    }
}

/* 
构造树的时候要按照 push 的顺序找根结点
 */

int main(int argc, char const *argv[])
{
    // push 的顺序为 preorder
    int n;

    scanf("%d", &n);

    int i, x;
    char cmd[N];
    int seq[N];

    int idx = 0;
    int preidx = 0;

    for (i = 0; i < 2 * n; i++) {
        scanf("%s", cmd);
        if (cmd[1] == 'u') {
            scanf("%d", &x);
            push(x);
            q[t = (t + 1) % N] = x;
        } else {
            seq[idx++] = pop();
        }
    }
    thefirst = q[h+1];
    struct tnode *root;
    root = generateTreeFromArray(seq, 0, n - 1);

    postorder_treeprint(root);

    return 0;
}
