#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
    List dummy = malloc(sizeof(struct Node));
    dummy->Next = NULL;

    int i, n, x;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        PtrToNode p = malloc(sizeof(struct Node));
        p->Data = x;
        p->Next = NULL;

        PtrToNode last = dummy->Next;
        if (last != NULL) {
            while (last->Next) {
                last = last->Next;
            }
            last->Next = p;
        } else {
            dummy->Next = p;
        }
    }
    return dummy;
}

void Print( List L )
{
    if (L->Next == NULL) {
        printf("NULL\n");
        return;
    }
    for (PtrToNode p = L->Next; p != NULL; p = p->Next) {
        printf("%d%s", p->Data, p->Next ? " " : "\n");
    }
}

/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 )
{
    PtrToNode p1 = L1->Next;
    PtrToNode p2 = L2->Next;
    PtrToNode temp = NULL, q;
    PtrToNode ret = malloc(sizeof(struct Node));
    ret->Next = L1->Next;
    if (p1 != NULL && p2 != NULL) 
    {
        if (p1->Data >= p2->Data) {
            ret->Next = L2->Next;
        }
    }
    while (p1 != p2 && p1 != NULL && p2 != NULL) {
        q = p1;
        while (p1 != NULL && p1->Data < p2->Data) {
            q = p1;
            p1 = p1->Next;
        }
        p1 = q;

        if (p1->Data < p2->Data) {
            temp = p1->Next;
            p1->Next = p2;
            p1 = temp;
        } else {
            q = p2;
            while (p2 != NULL && p1->Data >= p2->Data) {
                q = p2;
                p2 = p2->Next;
            }
            p2 = q;
            temp = p2->Next;
            p2->Next = p1;
            p2 = temp;
        }
    }
   
    L1->Next = NULL;
    L2->Next = NULL; 
    return ret;
}
