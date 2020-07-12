#include <stdio.h>

struct node {
    char left;
    char right;
};

int main(int argc, char const *argv[])
{
    struct node a[10];

    int i, n;
    int flag[10] = {0};

    if (scanf("%d\n", &n) == 1) {

        for (i = 0; i < n && scanf("%c %c\n", &a[i].left, &a[i].right); i++) {
            if (a[i].left != '-') {
                a[i].left -= '0';
                flag[a[i].left] = 1;
            }
            if (a[i].right != '-') {
                a[i].right -= '0';
                flag[a[i].right] = 1;
            }

        }

        int root;
        for (i = 0; i < n; i++) {
            if (flag[i] == 0) {
                root = i;
            }
        }

        int isfirst = 1;
        int q[10];
        int h, t;
        h = t = 0;
        q[t = (t + 1) % 10] = root;

        while (h != t) {
            root = q[h = (h + 1) % 10];
            if (a[root].left != '-')
                q[t = (t + 1) % 10] = a[root].left;
            if (a[root].right != '-')
                q[t = (t + 1) % 10] = a[root].right;
            if (a[root].left == '-' && a[root].right == '-') {
                printf("%s%d", isfirst ? "" : " ",root);
                isfirst = 0;
            }
        }
    }
    printf("\n");
    
    return 0;
}
