#include <stdio.h>

int main(int argc, char const *argv[])
{
    int count[51] = { 0 };
    int n;
    int age;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &age);
        count[age]++;
    }

    for (int i = 0; i < 51; i++) {
        if (count[i] > 0) {
            printf("%d:%d\n", i, count[i]);
        }
    }
    return 0;
}
