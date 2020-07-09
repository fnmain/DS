/* 
最大子序和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:

输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

动态规划：

设 f(x) 是以 a[x] 结尾的「最大子序和」
ans = max{ f(x) }, 0 <= x <= n-1

怎么得到 f(x) ?
f(x) 是以 a[x] 结尾的「最大子序和」，意思是说 f(x) 的结尾包含了 a[x] 这一项，
至于从哪一项开头的不关心

那若我已经算得一个 f(x-1)，那我只需要决定要不要在 f(x-1) 加上 a[x] 这一项,
要么 f(x) = f(x-1) + a[x]， 要么是 a[x]

即 f(x) = max{ f(x-1) + a[x], a[x] }
 */

#include <stdio.h>

int max(int a, int b) { return a > b ? a : b; }

int main(int argc, char const *argv[])
{
    // int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    int a[] = {-1, 3, -2, 4, -6, 1, 6, -1};
    int len = sizeof(a)/sizeof(a[0]);

    int x;
    int f[len];
    f[0] = a[0];
    // f[0] = a[0] > 0 ? a[0] : 0;
    for (x = 1; x < len; x++) {
        f[x] = max(f[x-1] + a[x], a[x]);
        // 为什么还能这样写? 这样写必须保证最大子序和的第一项小于0时被赋值为0
        // 若 f(x-1) + a[x] < 0，a[x] 必定小于 0, 所以这一项抛弃 let f[x] = 0
        // f[x] = max(f[x-1] + a[x], 0);
        printf("f(%d) = %d\n", x, f[x]);
    }

    int maxsum = f[0];
    for (x = 0; x < len; x++) {
        if (f[x] > maxsum) {
            maxsum = f[x];
        }
    }

    printf("maximum subarray = %d\n", maxsum);

    return 0;
}
