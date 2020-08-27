#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY -1

bool primetab[10008];
void init(void);    // 构造素数表
int nextprime(int n);

typedef struct _hashtab {
    int hashsize;
    int *hashtab;
} Hashtab;

unsigned hash(Hashtab *hashtab, int key)
{

    return (unsigned)key % hashtab->hashsize;
}

Hashtab hashtab_create(int size)
{
    Hashtab h;
    h.hashsize = nextprime(size);
    h.hashtab = malloc(h.hashsize * (sizeof(int)));
    memset(h.hashtab, EMPTY, sizeof(int) * h.hashsize);
    return h;
}

int hashtab_lookup(Hashtab *hashtab, int key)
{
    // Quadratic probing (with positive increments only)
    unsigned hashval, newpos;
    int i = 1;
    hashval = hash(hashtab, key);
    newpos = hashval;
    while (hashtab->hashtab[newpos] != EMPTY && hashtab->hashtab[newpos] != key) {
        newpos = (hashval + i * i) % (hashtab->hashsize);
        if (i > 1 && newpos == hashval + 1)
            return -2;  // 放不了
        i++;
    }
    return newpos;
}

int hashtab_install(Hashtab *hashtab, int key)
{
    int pos;
    if ((pos = hashtab_lookup(hashtab, key)) != -2) {
        hashtab->hashtab[pos] = key;
    }
    return pos;
}

int main(int argc, char const *argv[])
{
    int i, m, n;
    int key;

    if (scanf("%d %d", &m, &n) == 2) {
        int pos;
        Hashtab hashtab = hashtab_create(m);
        for (i = 0; i < n && scanf("%d", &key); i++) {
            if ((pos = hashtab_install(&hashtab, key)) == -2) {
                printf(i > 0 ? " -" : "-");
            } else {
                printf(i > 0 ? " %d" : "%d", pos);
            }
        }
    }
    printf("\n");
    return 0;
}

void init(void)
{
    int i, k;
    for (i = 2; i < 10008; i++)
        primetab[i] = true;
    
    for (i = 2; i < 10008 / 2; i++) {
        if (primetab[i] == true)
            for (k = 2; k * i < 10008; k++)
                primetab[k * i] = false;
    }
}

int nextprime(int n)
{
    init();
    while (!primetab[n])
        n++;
    return n;
}
