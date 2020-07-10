#include <stdio.h>
#include <stdlib.h>

typedef struct _term {
    double coe; // coefficient
    int exp;    // exponent
} Term;

typedef struct _node {
    Term term;
    struct _node *next;
} Node;

typedef struct _polynomial {
    Node *head;
} Polynomial;

// 以指数递降方式输入一个多项式非零项系数和指数
// 数字间以空格分隔
Polynomial polynomial_create(void)
{
    Polynomial p;
    p.head = NULL;
    int n;
    if (scanf("%d", &n) == 1) {
        double coe;
        int exp;
        for (int i = 0; i < n && scanf("%lf %d", &coe, &exp) == 2; i++) {
            Node* t = (Node*)malloc(sizeof(Node));
            t->term.coe = coe;
            t->term.exp = exp;
            t->next = NULL;
            // find the last
            Node* last = p.head;
            if (last != NULL) {
                while (last->next) {
                    last = last->next;
                }
                last->next = t;
            } else {
                p.head = t;
            }
        }
    }
    return p;
}

void polynomial_free(Polynomial *p)
{
    for (Node *t = p->head, *q = NULL; t != NULL; t = q) {
        q = t->next;
        free(t);
    }
    p->head = NULL;
}

void polynomial_show(Polynomial *p)
{
    if (p->head == NULL) {
        printf("0 0\n");
    } else {
        for (Node* t = p->head; t != NULL; t = t->next) {
            printf("%d %d%s", (int)(t->term.coe), t->term.exp, t->next ? " " : "\n");
        }
    }

}

Polynomial add(Polynomial *p1, Polynomial *p2)
{
    Node *t1 = p1->head;
    Node *t2 = p2->head;
    Polynomial p;
    p.head = NULL;

    while (t1 != NULL && t2 != NULL) {
        double sum;
        int exp;
        if (t1->term.exp == t2->term.exp) {
            sum = t1->term.coe + t2->term.coe;
            exp = t1->term.exp;
            t1 = t1->next;
            t2 = t2->next;
        } else if (t1->term.exp > t2->term.exp) {
            sum = t1->term.coe;
            exp = t1->term.exp;
            t1 = t1->next;
        } else {
            sum = t2->term.coe;
            exp = t2->term.exp;
            t2 = t2->next;
        }
        if (sum != 0) {
            Node*t = (Node*)malloc(sizeof(Node));
            t->term.coe = sum;
            t->term.exp = exp;
            t->next = NULL;

            Node *last = p.head;
            if (last != NULL) {
                while (last->next) {
                    last = last->next;
                }
                last->next = t;
            } else {
                p.head = t;
            }
        }
    }


    while (t1 != NULL) {
        Node*t = (Node*)malloc(sizeof(Node));
        t->term.coe = t1->term.coe;
        t->term.exp = t1->term.exp;
        t->next = NULL;

        Node *last = p.head;
        if (last != NULL) {
            while (last->next) {
                last = last->next;
            }
            last->next = t;
        } else {
            p.head = t;
        }

        t1 = t1->next;
    }

    while (t2 != NULL) {
        Node*t = (Node*)malloc(sizeof(Node));
        t->term.coe = t2->term.coe;
        t->term.exp = t2->term.exp;
        t->next = NULL;

        Node *last = p.head;
        if (last != NULL) {
            while (last->next) {
                last = last->next;
            }
            last->next = t;
        } else {
            p.head = t;
        }

        t2 = t2->next;
    }
    return p;
}

Polynomial product(Polynomial *p1, Polynomial *p2)
{
    Polynomial p, y;
    p.head = NULL;
    for (Node *i = p1->head; i != NULL; i = i->next) {
        for (Node *j = p2->head; j != NULL; j = j->next) {
            Term x = {i->term.coe * j->term.coe, i->term.exp + j->term.exp};
            Node node;
            node.term = x;
            node.next = NULL;
            Polynomial t;
            t.head = &node;

            y = add(&p, &t);
            polynomial_free(&p);
            p = y;
        }
    }
    return p;
}

int main(int argc, char const *argv[])
{
    Polynomial p1 = polynomial_create();
    Polynomial p2 = polynomial_create();

    Polynomial s = add(&p1, &p2);
    Polynomial y = product(&p1, &p2);

    polynomial_show(&y);
    polynomial_show(&s);

    polynomial_free(&p1);
    polynomial_free(&p2);
    polynomial_free(&s);
    return 0;
}
