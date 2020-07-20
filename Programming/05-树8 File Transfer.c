#include <stdio.h>

#define N 10001
#define NIL 0

struct set {
    int up;
    int count;
};

int findroot(struct set *s, int c)
{
    while (s[c].up != NIL) {
        c = s[c].up;
    }
    return c;
}

int main(int argc, char const *argv[])
{
    int n;
    int i;
    char ch[2];
    int c1, c2;

    struct set s[N];

    for (i = 0; i < N; i++) {
        s[i].up = NIL;
        s[i].count = 1;
    }

    scanf("%i", &n);

    do {
        scanf("%s", ch);
        if (ch[0] == 'S') {
            break;
        }
        
        scanf("%i %i", &c1, &c2);

        int r1 = findroot(s, c1);
        int r2 = findroot(s, c2);
        if (ch[0] == 'C') {
            if (r1 == r2) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else if (ch[0] == 'I') {
            if (s[r1].count < s[r2].count) {
                s[r1].up = r2;
                s[r2].count += s[r1].count;
            } else {
                s[r2].up = r1;
                s[r1].count += s[r2].count;
            }
        }

    } while (ch[0] != 'S');

    int count = 0;
    for (i = 1; i <= n; i++) {
        if (s[i].up == NIL) {
            count++;
        }
    }
    if (count == 1) {
        printf("The network is connected.\n");
    } else {
        printf("There are %i components.\n", count);
    }
    return 0;
}
