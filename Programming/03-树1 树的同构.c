#include <stdio.h>

struct tnode {
    char data;
    char left;
    char right;
};

int read(struct tnode a[], int n)
{
    int i;
    int flag[n];
    for (i = 0; i < n; i++) {
        flag[i] = 1;
    }
    for (i = 0; i < n; i++) {
        scanf("%c %c %c\n", &a[i].data, &a[i].left, &a[i].right);
        if (a[i].left != '-') {
            a[i].left -= '0';
            flag[a[i].left] = 0;
        }
        if (a[i].right != '-') {
            a[i].right -= '0';
            flag[a[i].right] = 0;
        }
    }

    int root = -1;
    for (i = 0; i < n; i++) {
        if (flag[i]) {
            root = i;
            break;
        }
    }
    return root;
}

int isomorphism(struct tnode a[], struct tnode b[], int roota, int rootb)
{
    int yes = 0;
    // 两个空树 或者 这个结点的左右都没有子结点
    if ((roota == -1 && roota == rootb) || ((roota == '-') && (rootb == '-'))) {
        yes = 1;
    } else {
        // 如果子树的根结点相同则左右子树都同构 或者 交换一下构成同构
        if (a[roota].data == b[rootb].data) {
            yes = (isomorphism(a, b, a[roota].left, b[rootb].left) 
            && isomorphism(a, b, a[roota].right, b[rootb].right))
            || (isomorphism(a, b, a[roota].left, b[rootb].right)
            && isomorphism(a, b, a[roota].right, b[rootb].left));
        }
    }

    return yes;
}

int main(int argc, char const *argv[])
{
    int i, an, bn;
    int roota, rootb;
    struct tnode a[10], b[10];
    scanf("%d\n", &an);
    roota = read(a, an);
    scanf("%d\n", &bn);
    rootb = read(b, bn);
    
    printf("%s\n", isomorphism(a, b, roota, rootb) ? "Yes" : "No");
    return 0;
}
