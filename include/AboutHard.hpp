#include "Util.h"
// 312. 戳气球 恶心
class LT312Solution
{
public:
    vector<vector<int>> rec;
    vector<int> val;

public:
    int solve(int left, int right)
    {
        //
        if (left >= right - 1)
        {
            return 0;
        }
        //
        if (rec[left][right] != -1)
        {
            return rec[left][right];
        }
        //
        //递归 归并算法以i中心 插入val[i] 开始left 和 right 为1
        //输入：3 1 5 8
        //插3：1 3 1 插1：1 5 1 插5：1 5 1 插8：1 8 1
        //在插入第一个数情况下继续插入 往第一个数solve(left, i)或者solve(i, right)插入的情况
        for (int i = left + 1; i < right; i++)
        {
            int sum = val[left] * val[i] * val[right];
            sum += solve(left, i) + solve(i, right);
            rec[left][right] = max(rec[left][right], sum);
        }
        return rec[left][right];
    }

    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();
        val.resize(n + 2);
        //左右默认两个1，中间赋值（1）3 1 5 8（1）
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++)
        {
            val[i] = nums[i - 1];
        }
        // rec[left][right]代表以left下标到right下标 开区间得分最大值 即val[1]-val[n]
        rec.resize(n + 2, vector<int>(n + 2, -1));
        return solve(0, n + 1);
    }
    //动态规划
    // int maxCoins2(int *nums, int numsSize)
    // {
    //     //dp[i][j] i-j区间代表最大最大金币
    //     int dp[numsSize + 2][numsSize + 2];
    //     memset(dp, 0, sizeof(dp)); //初始化dp数组
    //     int val[numsSize + 2];
    //     val[0] = val[numsSize + 1] = 1;     //构造新数组
    //     for (int i = 1; i <= numsSize; i++) //初始化
    //     {
    //         val[i] = nums[i - 1];
    //     }
    //     for (int i = numsSize - 1; i >= 0; i--) //更新dp数组值
    //     {
    //         for (int j = i + 2; j <= numsSize + 1; j++)
    //         {
    //             for (int k = i + 1; k < j; k++)
    //             {
    //                 // 最后一个戳破k 得分
    //                 int sum = val[i] * val[k] * val[j];
    //                 sum += dp[i][k] + dp[k][j];
    //                 dp[i][j] = fmax(dp[i][j], sum);
    //             }
    //         }
    //     }
    //     return dp[0][numsSize + 1];
    // }
};
