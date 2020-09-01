#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* len is length of pattern */
void build_match(int match[], char pattern[], int len)
{
    int i, k;

    match[0] = -1;
    for (i = 1; i < len; i++) {
        k = match[i-1];
        while ((k >= 0) && (pattern[k+1] != pattern[i]))
            k = match[k];
        if (pattern[k+1] == pattern[i])
            match[i] = k + 1;
    }
}

char* kmp(char *str, char *pattern)
{
    int n, m;
    n = strlen(str);
    m = strlen(pattern);

    if (n < m)
        return NULL;

    int *match = malloc(sizeof(int)*m);
    build_match(match, pattern, m);

    int i, j;
    i = 0, j = 0;

    while (i < n && j < m) {
        if (str[i] == pattern[j])
            i++, j++;
        else if (j > 0)
            j = match[j-1] + 1;
        else
            i++;
    }

    return j == m ? str + (i-m) : NULL;
}

#define MAXLEN 1000001

int main(int argc, char const *argv[])
{
    char string[MAXLEN];
    char pattern[MAXLEN];
    int i, n;
    char *p;

    if (scanf("%s", string) == 1 && scanf("%d", &n) == 1) {
        for (i = 0; i < n && scanf("%s", pattern) == 1; i++) {
            if ((p = kmp(string, pattern)) != NULL) {
                printf("%s\n", p);
            } else {
                printf("Not Found\n");
            }
        }
    }

    return 0;
}
