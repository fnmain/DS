#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UNSUBMMITED -2

#define K 5
#define N 10000

typedef struct _user {
    int user_id;
    int problems[K];
    int total_score;
    int solved;
    bool show;
} User;

int fullmark[K];

int cmp(const void *p1, const void *p2)
{
    User a = *(User*)p1;
    User b = *(User*)p2;

    int ret;
    if (a.total_score < b.total_score)
        ret = 1;
    else if (a.total_score > b.total_score)
        ret = -1;
    else
    {
        if (a.solved < b.solved)
            ret = 1;
        else if (a.solved > b.solved)
            ret = -1;
        else
        {
            if (a.user_id < b.user_id)
                ret = -1;
            else
                ret = 1;
        }
        
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int n, m, k;
    int i, j;
    int uid, pid, score;

    User users[N];

    scanf("%d %d %d", &n, &k, &m);

    for (i = 0; i < n; i++) {
        users[i].user_id = i + 1;
        users[i].show = false;
        users[i].solved = 0;
        users[i].total_score = 0;
        for (j = 0; j < k; j++)
            users[i].problems[j] = UNSUBMMITED;
    }

    for (i = 0; i < k; i++) {
        scanf("%d", &fullmark[i]);
    }

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &uid, &pid, &score);
        if (score == fullmark[pid-1] && users[uid-1].problems[pid-1] != score) {
            users[uid-1].solved ++;
        }
        if (users[uid-1].problems[pid-1] < score) {
            if (score >= 0) {
                users[uid-1].show = true;
            }
            users[uid-1].problems[pid-1] = score;
        }
    }

    // 计算 total_score
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) {
            if (users[i].problems[j] > 0) {
                users[i].total_score += users[i].problems[j];
            }
        }
    }

    qsort(users, n, sizeof(User), cmp);

    int last_score = 0, rank = 0;
    for (i = 0; i < n; i++) {
        if (users[i].show) {
            if (last_score != users[i].total_score)
                rank = i + 1;
            printf("%d %05d %d", rank, users[i].user_id, users[i].total_score);
            last_score = users[i].total_score;
            for (j = 0; j < k; j++) {
                int score = users[i].problems[j];
                if (users[i].problems[j] == -1) {
                    score = 0;
                }
                if (score >= 0) {
                    printf(" %d", score);
                } else {
                    printf(" -");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
