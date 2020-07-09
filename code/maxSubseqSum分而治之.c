#include <stdio.h>

int maxSubseqSum(int a[], int left, int right)
{
    if (left == right) {
        return a[left];
    }

    int lmaxsum, rmaxsum;

    lmaxsum = maxSubseqSum(a, left, (left + right) / 2);
    rmaxsum = maxSubseqSum(a, (left + right) / 2 + 1, right);

    
    int current_sum = 0;
    int crossLeftSum, crossRightSum;
    crossLeftSum = crossRightSum = 0;
    for (int i = (left + right) / 2; i >= left; i--) {
        current_sum += a[i];
        if (current_sum > crossLeftSum) {
            crossLeftSum = current_sum;
        }
    }

    current_sum = 0;
    for (int i = (left + right) / 2 + 1; i <= right; i++) {
        current_sum += a[i];
        if (current_sum > crossRightSum) {
            crossRightSum = current_sum;
        }
    }
    int crossSum = crossLeftSum + crossRightSum;

    int ret = 0;
    if (lmaxsum > rmaxsum) {
        ret = lmaxsum;
    } else {
        ret = rmaxsum;
    }

    if (crossSum > ret) {
        ret = crossSum;
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    // int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    int a[] = {-1, 3, -2, 4, -6, 1, 6, -1};
    int len = sizeof(a)/sizeof(a[0]);


    printf("maximum subarray = %d\n", maxSubseqSum(a, 0, len-1));

    return 0;
}
