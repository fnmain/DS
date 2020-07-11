#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _stack {
    int *val;
    int maxval;
    int sp;
} Stack;

Stack stack_create(int size)
{
    Stack stack;
    stack.maxval = size;
    stack.sp = 0;
    stack.val = malloc(sizeof(int)*stack.maxval);
    return stack;
}

void stack_free(Stack *p)
{
    free(p->val);
    p->sp = 0;
    p->maxval = 0;
    p->val = NULL;
}

// push 成功返回 0
// push 失败返回 -1
int stack_push(Stack *s, int x)
{
    if (s->sp < s->maxval) {
        s->val[s->sp++] = x;
        return 0;
    } else {
        return -1;
    }
}

int stack_pop(Stack *s)
{
    if (s->sp == 0) {
        return -1;
    } else {
        return s->val[--(s->sp)];
    }
}

int stack_peek(Stack *s)
{
    if (s->sp > 0) {
        return s->val[s->sp-1];
    } else {
        return -1;
    }
}

void stack_clear(Stack *s)
{
    s->sp = 0;
}

int main(int argc, char const *argv[])
{
    int m, n, k;
    int i, j, p;
    scanf("%d %d %d", &m, &n, &k);
    Stack stack = stack_create(m);

    for (i = 0; i < k; i++) {
        bool yes = true;
        int x, temp;
        stack_push(&stack, 1);
        for (j = 0, p = 2; j < n; j++) {
            scanf("%d", &x);
            while (yes) {
                temp = stack_peek(&stack);
                if (temp != x) {
                    if (stack_push(&stack, p++) == -1) {
                        yes = false;
                    }
                } else {
                    if (stack_pop(&stack) == -1) {
                        yes = false;
                    } else {
                        break;
                    }
                }
            }
        }
        printf("%s\n", yes ? "YES" : "NO");
        stack_clear(&stack);
    }

    stack_free(&stack);
    return 0;
}
