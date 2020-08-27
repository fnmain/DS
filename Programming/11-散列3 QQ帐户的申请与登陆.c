#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *numbers;
    char *passwd;
    int count;
};

#define HASHSIZE 100003

struct nlist *hashtab[HASHSIZE];

unsigned int hash(const char *s);
struct nlist *lookup(const char *s);
struct nlist *install(const char *s, const char *passwd);

#define ACCOUNT_LENGTH 12
#define PASSWD_LENGTH 17
int main(int argc, char const *argv[])
{
    int i, n;
    char account[ACCOUNT_LENGTH];
    char passwd[PASSWD_LENGTH];
    char cmd[3];

    if (scanf("%d", &n) == 1) {
        struct nlist *np;
        for (i = 0; i < n && scanf("%s %s %s", cmd, account, passwd) == 3; i++) {
            if (cmd[0] == 'N') {
                if (lookup(account) != NULL)
                    printf("ERROR: Exist\n");
                else
                    if (install(account, passwd) != NULL)
                        printf("New: OK\n");
                    else
                        printf("error: install()\n");
            } else {
                if ((np = lookup(account)) == NULL)
                    printf("ERROR: Not Exist\n");
                else {
                    if (strcmp(np->passwd, passwd) == 0)
                        printf("Login: OK\n");
                    else
                        printf("ERROR: Wrong PW\n");
                }
            }
        }
    }

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

struct nlist *install(const char *s, const char *passwd)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(s)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->numbers = strdup(s)) == NULL || (np->passwd = strdup(passwd)) == NULL)
            return NULL;
        np->count = 1;
        hashval = hash(s);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        np->count++;
    return np;
}