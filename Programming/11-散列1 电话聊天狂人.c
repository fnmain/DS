#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *numbers;
    int count;
};

#define HASHSIZE 100003

struct nlist *hashtab[HASHSIZE];

unsigned int hash(const char *s);
struct nlist *lookup(const char *s);
struct nlist *install(const char *s);

#define LENGTH 12
int main(int argc, char const *argv[])
{
    int i, n;
    char buf[LENGTH];

    if (scanf("%d", &n) == 1) {
        for (i = 0; i < 2 * n && scanf("%s", buf) == 1; i++) {
            install(buf);
        }
    }

    struct nlist *np = NULL;
    char *result = "";
    int max = 0;
    int parallel = 0;
    for (i = 0; i < HASHSIZE; i++) {
        for (np = hashtab[i]; np != NULL; np = np->next) {
            if (np->count > max) {
                max = np->count;
                result = np->numbers;
                parallel = 0;
            } else if (np->count == max) {
                parallel++;
                if (strcmp(np->numbers, result) < 0) {
                    max = np->count;
                    result = np->numbers;
                }
            }
        }
    }
    if (parallel == 0)
        printf("%s %d\n", result, max);
    else
        printf("%s %d %d\n", result, max, parallel + 1);
    return 0;
}

unsigned int hash(const char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(const char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->numbers) == 0)
            return np;
    return NULL;
}

struct nlist *install(const char *s)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(s)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->numbers = strdup(s)) == NULL)
            return NULL;
        np->count = 1;
        hashval = hash(s);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        np->count++;
    return np;
}