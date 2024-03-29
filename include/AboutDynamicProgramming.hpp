﻿#pragma once
#include "Util.h"
// 5. 最长回文子串
class LT005Solution
{
public:
    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n < 2)
        {
            return s;
        }
        int maxLen = 1;
        int begin = 0;
        // dp[i][j] 表示 s[i..j] 是否是回文串
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        // 初始化：所有长度为 1 的子串都是回文串
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = true;
        }
        // 递推开始
        // 先枚举子串长度
        for (int L = 2; L <= n; L++)
        {
            // 枚举左边界，左边界的上限设置可以宽松一些
            for (int i = 0; i < n; i++)
            {
                // 由 L 和 i 可以确定右边界，即 j - i + 1 = L 得
                int j = L + i - 1;
                // 如果右边界越界，就可以退出当前循环
                if (j >= n)
                {
                    break;
                }

                if (s[i] != s[j])
                {
                    dp[i][j] = false;
                }
                else
                {
                    if (j - i < 3)
                    {
                        dp[i][j] = true;
                    }
                    else
                    {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                // 只要 dp[i][L] == true 成立，就表示子串 s[i..L] 是回文，此时记录回文长度和起始位置
                if (dp[i][j] && j - i + 1 > maxLen)
                {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
};
// LT042. 接雨水
class LT042Solution
{
public:
    // height = [0,1,0,2,1,0,1,3,2,1,2,1] 6
    int trap(vector<int> &height)
    {
        int n = height.size();
        vector<int> leftHeight(n, 0);
        leftHeight[0] = height[0];
        for (int i = 1; i < n; i++)
        {
            leftHeight[i] = max(height[i], leftHeight[i - 1]);
        }

        vector<int> rightHeight(n, 0);
        rightHeight[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            rightHeight[i] = max(height[i], rightHeight[i + 1]);
        }
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            res += min(leftHeight[i], rightHeight[i]) - height[i];
        }
        return res;
    }
};
// LT42 最大子数组和
class LT053Solution
{
public:
    //输入：[1,-2,3,10,-4,7,2,-5]
    //子数组[3,10,-4,7,2]可以求得最大和为18
    int maxSubArray(vector<int> &nums)
    {
        int now = 0;             //表示当前累加和，要是<0 前面都可以不需要了
        int max_value = INT_MIN; //用来保存最大值
        for (int i = 0; i < nums.size(); i++)
        { // now<0,则舍去前面的
            if (now < 0)
                now = nums[i];
            else
            {
                now += nums[i]; //比0大则直接加上去
            }
            max_value = max(now, max_value); //更新最大值
        }
        return max_value;
    }
    //动态规划 dp[n]为以第n个数为结尾，得到的子数组的和的最大值
    int maxSubArray(vector<int> nums)
    {
        int size = nums.size();
        // dp[i] 第i个数时最大合
        vector<int> dp;
        dp.push_back(nums[0]);
        int max_value = dp[0];
        for (int i = 1; i < size; i++)
        {
            dp.push_back(max(nums[i], dp[i - 1] + nums[i]));
            max_value = max(max_value, dp[i]);
        }
        return max_value;
    }
};

// LT85 连续子数组的最大和(二)
class LT85Solution
{
public:
    //输入：[1,-2,3,10,-4,7,2,-5]子数组[3,10,-4,7,2]可以求得最大和为18
    //输入：[1,-2,3,10,-4,7,2,-1,1,-5] 子数组[3,10,-4,7,2,-1,1] 返回长度较长的子数组
    vector<int> FindGreatestSumOfSubArray(vector<int> &array)
    {
        vector<int> res;
        int c_max = array[0];  //当前轮
        int maxsum = array[0]; //历史和最大值
        int left = 0, right = 0;
        int resl = 0, resr = 0;
        for (int i = 1; i < array.size(); i++)
        {
            right++;
            if (c_max + array[i] < array[i])
            {
                left = right;
                c_max = array[i];
            }
            else
            {
                c_max = c_max + array[i];
            }
            // c_max当前轮循环最后一个数结尾子数组的和的最大值
            if (c_max > maxsum || c_max == maxsum && (right - left + 1) > (resr - resl + 1))
            {
                maxsum = c_max;
                resl = left;
                resr = right;
            }
        }
        for (int i = resl; i <= resr; i++)
        {
            res.push_back(array[i]);
        }
        return res;
    }
};
// 62. 不同路径
class LT062Solution
{
public:
    //超时
    int count = 0;
    void findOnePath(int i, int j, int m, int n, vector<vector<bool>> flag)
    {
        if (flag[i][j])
            return;
        flag[i][j] = true;
        if (i == m - 1 && j == n - 1)
        {
            count++;
            return;
        }
        int dirct[2][2] = {{1, 0}, {0, 1}};
        for (int k = 0; k < 2; k++)
        {
            //从x y往下右四个方向走
            int row1 = i + dirct[k][0];
            int col1 = j + dirct[k][1];
            if (col1 < n && row1 < m)
            {
                findOnePath(row1, col1, m, n, flag);
            }
        }
    }
    int uniquePaths(int m, int n)
    {
        vector<vector<bool>> flag(m, vector<bool>(n, false));
        findOnePath(0, 0, m, n, flag);
        return count;
    }
    int uniquePaths2(int m, int n)
    {
        vector<vector<int>> f(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            f[i][0] = 1;
        }
        for (int j = 0; j < n; ++j)
        {
            f[0][j] = 1;
        }
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
        return f[m - 1][n - 1];
    }
};
// 64. 最小路径和
class LT064Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int sum = 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> f(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            sum += grid[i][0];
            f[i][0] = sum;
        }
        sum = 0;
        for (int j = 0; j < n; ++j)
        {
            sum += grid[0][j];
            f[0][j] = sum;
        }
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                f[i][j] = min(f[i - 1][j], f[i][j - 1]) + grid[i][j];
            }
        }
        return f[m - 1][n - 1];
    }
};
// LT70. 爬楼梯
class LT070Solution
{
public:
    //数据范围: 1≤n≤45
    int climbStairs(int n)
    {
        int dp[46] = {0};
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        int k = 3;
        while (k <= n)
        {
            dp[k] = dp[k - 1] + dp[k - 2];
            k++;
        }
        return dp[n];
    }
};
// LT10 斐波那契数列
class LT10Solution
{
public:
    // fib(1)=1,fib(2)=1,fib(3)=fib(3-1)+fib(3-2)=2
    int Fibonacci(int n)
    {
        if (n <= 2)
            return 1;
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
    int Fibonacci2(int n)
    {
        int dp[41];
        dp[0] = dp[1] = dp[2] = 1;
        int k = 3;
        while (k <= n)
        {
            dp[k] = dp[k - 1] + dp[k - 2];
            k++;
        }
        return dp[n];
    }
};
// LT19 正则表达式匹配
class LT19Solution
{
public:
    //会超时
    bool match(const string &str, const string &pattern)
    {
        if (str.empty() && pattern.empty())
            return true;
        if (!str.empty() && pattern.empty())
            return false;
        if (pattern[1] == '*')
        {
            if (pattern[0] == str[0] || (pattern[0] == '.' && !str.empty()))
            {
                //进入下一状态 "" "a" *只用来匹配一次
                bool ok1 = match(str.substr(1), pattern.substr(2));
                //留在当前状态 "" *继续匹配
                bool ok2 = match(str.substr(1), pattern);
                //忽略一个'*'
                bool ok3 = match(str, pattern.substr(2));
                return ok1 || ok2 || ok3;
            }
            else
            {
                //忽略一个'*'
                return match(str, pattern.substr(2));
            }
        }
        //正常进入下一个阶段
        if (str[0] == pattern[0] || (pattern[0] == '.' && !str.empty()))
            return match(str.substr(1), pattern.substr(1));

        return false;
    }
    // dp[i][j]表示str的前i个字符与pattern的前j个字符是否匹配 当前的表示为j-1
    //""和 “a*c*"匹配过程"
    // j=1 pattern[1-1] == 'a' dp[0][1] = 0
    // j=2 pattern[2-1] == '*' dp[0][2] = dp[0][0] == 1
    // j=3 pattern[3-1] == 'c' dp[0][3] = 0
    // j=4 pattern[4-1] == 'c' dp[0][4] = dp[0][2] == 1
    // "a"  "a*"
    //第j个字符是'*' 在str下标0开始默认需要-1
    // dp[i][j] 表示前面i个字符和pattern前面j个字符匹配
    int dp[35][35] = {0};
    bool match2(string str, string pattern)
    {
        int len1 = str.length();
        int len2 = pattern.length();
        dp[0][0] = 1;
        for (int i = 0; i <= len1; i++) // i==0是处理空str串,非空pattern串的情况
        {
            for (int j = 1; j <= len2; j++)
            {
                //正常字符匹配
                if (i > 0 && (pattern[j - 1] == '.' || pattern[j - 1] == str[i - 1]))
                { //如果模式串字符与str字符匹配,和如果模式串字符为.,则dp[i][j]=dp[i-1][j-1]
                    dp[i][j] = dp[i - 1][j - 1];
                } //这里题目好像保证了输入*一定不会出现在pattern第1个字符但还是j>=2 好一些
                else if (j >= 2 && pattern[j - 1] == '*')
                {
                    if (i > 0 && (pattern[j - 2] == '.' || pattern[j - 2] == str[i - 1]))
                    {
                        dp[i][j] = dp[i - 1][j]; //*用了至少1次 则应该跟少一个字符dp相等
                    }
                    dp[i][j] |= dp[i][j - 2]; //字符 *号 使用0次
                }
            }
        }
        return dp[len1][len2] == 1;
    }
};
// 44. 通配符匹配
class LT044Solution
{
public:
    bool isMatch(string s, string p)
    {
        int m = s.size();
        int n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i)
        {
            if (p[i - 1] == '*')
            {
                dp[0][i] = true;
            }
            else
            {
                break;
            }
        }
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

//给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
// 你可以对一个单词进行如下三种操作：
// 1.插入一个字符 2.删除一个字符 32替换一个字符
// 输入：word1 = "horse", word2 = "ros" 输出：3
// 解释：horse -> rorse (将 'h' 替换为 'r') rorse -> rose (删除 'r') rose -> ros (删除 'e')
// 72. 编辑距离
class LT072Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int len1 = word1.length();
        int len2 = word2.length();

        vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
        for (int i = 0; i < len1; i++)
        {
            dp[i][0] = i;
        }
        for (int j = 0; j < len2; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                int temp = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
                dp[i][j] = min(temp, dp[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]));
            }
        }
        return dp[len1][len2];
    }
};
// 121. 买卖股票的最佳时机
class LT121Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int profits = 0;
        int days = prices.size();
        if (days <= 0)
            return profits;
        int buyingPrice = prices[0];
        for (int i = 1; i < days; ++i)
        {
            profits = max(profits, prices[i] - buyingPrice);
            buyingPrice = min(prices[i], buyingPrice);
        }
        return profits;
    }
};
// 122. 买卖股票的最佳时机 II
class LT122Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.empty())
        {
            return 0;
        }
        // f[i][0]: 手上持有股票的最大收益
        // f[i][1]: 手上不持有股票，累计最大收益
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(2));
        f[0][0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            // 今天买入股票和前一天买入股票对比 手上的钱
            f[i][0] = max(f[i - 1][0], f[i - 1][1] - prices[i]);
            // 今天卖出股票和前一天没有买入股票对比
            f[i][1] = max(f[i - 1][1], f[i - 1][0] + prices[i]);
        }
        return max(f[n - 1][1], 0);
    }
};
// LT71 跳台阶扩展问题
/*描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶(n为正整数)总共有多少种跳法。
数据范围：1≤n≤20
进阶：空间复杂度 O(1)O(1) ， 时间复杂度 O(1)O(1)
输入：3返回值：4
输入：1
返回值：1
*/
class LT71Solution
{
public:
    int jumpFloorII(int number)
    {
        int dp[21] = {0};
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= number; i++)
        {
            int sum = 0;
            for (int j = i; j > 1; j--)
            {
                sum += dp[j - 1];
            }
            dp[i] = sum + 1; //直接跳上来
        }
        return dp[number];
    }
};

// LT70 矩形覆盖
/*
我们可以用 2*1 的小矩形横着或者竖着去覆盖更大的矩形。请问用 n 个 2*1 的小矩形无重叠地覆盖一个 2*n 的大矩形，从同一个方向看总共有多少种不同的方法？
进阶：0≤n≤38 空间复杂度 O(1)\O(1)  ，时间复杂度 O(n)\O(n)
注意：约定 n == 0 时，输出 0
比如n=3时，2*3的矩形块有3种不同的覆盖方法(从同一个方向看)：
*/
class LT70Solution
{
public:
    int rectCover(int number)
    {
        int a[39] = {0};
        a[1] = 1;
        a[2] = 2;
        for (int i = 3; i <= number; i++)
        {
            a[i] = a[i - 1] + a[i - 2];
        }
        return a[number];
    }
};

// LT47 礼物的最大价值
class LT47Solution
{
public:
    int maxValue(vector<vector<int>> &grid)
    {
        // dp[x][y] 代表第x行 y列时礼物的最大值
        int dp[201][201];
        dp[1][1] = grid[0][0];
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int x = i + 1, y = j + 1;
                dp[x][y] = max(dp[x - 1][y], dp[x][y - 1]) + grid[i][j];
            }
        }
        return dp[n][m];
    }
    int maxValue2(vector<vector<int>> &grid)
    {
        // dp[x][y] 代表第x行 y列时礼物的最大值
        int dp[201][201] = {0};
        dp[1][1] = grid[0][0];
        int rows = grid.size();
        int cols = grid[0].size();
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
            }
        }
        return dp[rows][cols];
    }
};
// LT03 最长不含重复字符的子字符串
class LT03Solution
{
public:
    //"abcabcbb" 3
    int lengthOfLongestSubstring(string s)
    {
        if (s.size() == 0)
        {
            return 0;
        }
        int maxValue = 1, cur = 0, begin = 0;

        for (int i = 1; i < s.size(); i++)
        {
            for (int j = begin; j < i; j++)
            {
                if (s[j] == s[i])
                {
                    begin = j + 1;
                }
            }
            if (i - begin + 1 > maxValue)
            {
                maxValue += 1;
            }
        }
        return maxValue;
    }
    int lengthOfLongestSubstring2(string s)
    {
        unordered_map<char, int> m;
        int start = 0;
        int maxValue = 0;
        for (int i = 0; i < s.size(); i++)
        {
            //查找
            if (m.find(s[i]) != m.end())
            {
                //起始位置更新为之前该字符位置的后一个位置
                start = max(start, m[s[i]] + 1);
            }
            maxValue = max(maxValue, i - start + 1);
            //存储字符的位置
            m[s[i]] = i;
        }
        return maxValue;
    }
};
// LT46 把数字翻译成字符串
class LT46Solution
{
public:
    //有一种将字母编码成数字的方式：'a'->1, 'b->2', ... , 'z->26'
    //输入："12" 返回值：2   2种可能的译码结果（”ab” 或”l”）
    //数据范围：字符串长度满足 0<n≤90
    //"31717126241541717"
    int solve(string nums)
    {
        // dp[i] 代表第i个数字的solve最大数量
        int dp[91] = {0};
        dp[0] = 1;
        int length = nums.length();
        for (int i = 1; i <= length; i++)
        {
            if (nums[i - 1] != '0')
            {
                dp[i] += dp[i - 1];
            }
            // i-1代表nums当前字符,下标i-2上一个数字，考虑是否能和当前数字结合<=26(z)
            if (i >= 2 && nums[i - 2] != '0' && (nums[i - 2] - '0') * 10 + (nums[i - 1] - '0') <= 26)
                dp[i] += dp[i - 2];
        }
        return dp[length];
    }
};
// 91. 解码方法
class LT091Solution
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        //dp[i]表示字符串 s 的前 i 个字符 dp[1..i]的解码方法数
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            // 当前字符!=0 则解码数和之前一个字符一致
            if (s[i - 1] != '0')
            {
                dp[i] += dp[i - 1];
            }
            //至少两个字符 前面字符不为0  当前字符和前一个字符组合 <=26  
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26))
            {
                dp[i] += dp[i - 2];
            }
        }
        return dp[n];
    }
};
// 118. 杨辉三角
class LT118Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ans(numRows);
        for (int i = 0; i < numRows; i++)
        {
            ans[i].resize(i + 1);
            ans[i][0] = ans[i][i] = 1;
            //不用取到第i+1列 下标i 值为1
            for (int j = 1; j < i; j++)
            {
                ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
            }
        }
        return ans;
    }
};
// 152. 乘积最大子数组
class LT152Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            int mx = maxF, mn = minF;
            //最大三种情况 1.继承前面乘积*当前值>0 2.之前乘积<当前值 3.之前乘积是负数（最小值）*当前值负数
            maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
            // 1.计算之前乘积最小值 *当前值 2.当前值最小值 3.当前之前乘积最大值 * 当前值<0
            minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
            ans = max(maxF, ans);
        }
        return ans;
    }
};
// 198. 打家劫舍
class LT198Solution
{
public:
    int rob(vector<int> &nums)
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        if (nums.size() == 1)
        {
            return nums[0];
        }
        vector<int> dp(nums.size() + 1, 0);
        dp[1] = nums[0];
        for (int i = 2; i <= nums.size(); i++)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
        }
        return dp[nums.size()];
    }
};

// 279. 完全平方数
class LT279Solution
{
public:
    int numSquares(int n)
    {
        // f[i] 表示最少需要多少个数的平方来表示整数 i。
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int minn = INT_MAX;
            for (int j = 1; j * j <= i; j++)
            {
                minn = min(minn, f[i - j * j]);
            }
            f[i] = minn + 1;
        }
        return f[n];
    }
};

// 300. 最长递增子序列
class LT300Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        // dp[i] 代表以nums[i]结尾的最长递增子序列的元素个数
        vector<int> dp(n, 0);

        for (int i = 0; i < n; i++)
        {
            dp[i] = 1;
            for (int j = 0; j < i; j++)
            { // dp[j]的数量 + 当前的值 构成子序列数量
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        // dp是一个没有顺序的可能 前一个元素是比较大dp[i-1]=3 后一个以一个很小元素结尾 则dp[i] = 1
        return *max_element(dp.begin(), dp.end());
    }
};

// 309. 最佳买卖股票时机含冷冻期
class LT309Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.empty())
        {
            return 0;
        }

        int n = prices.size();
        // f[i][0]: 手上持有股票的最大收益
        // f[i][1]: 手上不持有股票，并且处于冷冻期中的累计最大收益
        // f[i][2]: 手上不持有股票，并且不在冷冻期中的累计最大收益
        vector<vector<int>> f(n, vector<int>(3));
        f[0][0] = -prices[0];
        for (int i = 1; i < n; ++i)
        {
            f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i]); //今天买入股票
            f[i][1] = f[i - 1][0] + prices[i];                   //今天卖出股票
            f[i][2] = max(f[i - 1][1], f[i - 1][2]);
        }
        return max(f[n - 1][1], f[n - 1][2]);
    }
};

// 322. 零钱兑换
class LT322Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int Max = amount + 1;
        // dp[i]代表组成i元 需要的硬币最少数量
        // dp[i-coins[j]]+1
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        //从1元开始算起
        for (int i = 1; i <= amount; ++i)
        {
            for (int j = 0; j < (int)coins.size(); ++j)
            {
                if (coins[j] <= i)
                {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

// 338. 比特位计数
class LT338Solution
{
public:
    vector<int> countBits(int n)
    {
        // dp[i] 代表二进制 值i中1的数量
        vector<int> dp(n + 1);
        //最高有效位
        int highBit = 0;
        for (int i = 1; i <= n; i++)
        {
            //枚举i到对应值时更新最高有效位  1 2 4 8 .... 256
            if ((i & (i - 1)) == 0)
            {
                highBit = i;
            }
            // dp[15] = dp[15-8] + 1 = dp[7-4] + 2 = dp[3-2] + 3 = dp[1]+4
            dp[i] = dp[i - highBit] + 1;
        }
        return dp;
    }
};
// 416. 分割等和子集
class LT416Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
        {
            return false;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        //总和为奇数 则两个子集一定不相等
        if (sum % 2 != 0)
            return false;
        //题目指定nums[] >= 1
        int maxNum = *max_element(nums.begin(), nums.end());
        //计算每个子集合target
        int target = sum / 2;
        if (maxNum > target)
        {
            return false;
        }
        // dp[i][j]表示下标nums[0]-nums[i]和等于j
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        for (int i = 0; i < n; i++)
        {
            dp[i][0] = true;
        }
        //满足本身 {nums[0]} 符合子集1 空{}子集2
        dp[0][nums[0]] = true;
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= target; j++)
            {
                //第一种情况本身 nums[i]就符合j，单独分出一个子集{j} {其他}
                if (nums[i] == j)
                {
                    dp[i][j] = 1;
                }
                else if (dp[i - 1][j] == 1)
                {
                    //不取nums[i]
                    dp[i][j] = 1;
                }
                else if (j >= nums[i])
                {
                    dp[i][j] = dp[i - 1][j - nums[i]];
                }
            }
        }
        if (dp[n - 1][target] == 1)
            return true;
        else
            return false;
    }
};

// 494. 目标和
class LT494Solution
{
public:
    int ans = 0;
    void dfs(vector<int> &nums, int index, int target)
    {
        if (index == nums.size())
        {
            if (target == 0)
            {
                ans++;
            }
            return;
        }
        dfs(nums, index + 1, target + nums[index]);
        dfs(nums, index + 1, target - nums[index]);
    }
    int findTargetSumWays(vector<int> &nums, int target)
    {
        dfs(nums, 0, target);
        return ans;
    }

    int findTargetSumWays2(vector<int> &nums, int target)
    {
        int sum = 0;
        for (int &num : nums)
        {
            sum += num;
        }
        int diff = sum - target;
        // neg = (sum - target) / 2
        if (diff < 0 || diff % 2 != 0)
        {
            return 0;
        }
        // neg 代表负数和 其中 (sum - neg) - neg= target
        int neg = diff / 2;
        // dp[neg] = 代表num[0] + .... num[n] = neg的数量
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
        dp[0][0] = 1;
        // dp[i][j] 表示在数组 nums的前i个数中选取元素，使得这些元素之和等j的方案数
        for (int i = 1; i <= n; i++)
        {
            int num = nums[i - 1];
            //枚举当选择前i个数时，和为j的方案数
            for (int j = 0; j <= neg; j++)
            {
                //如果不选num，上个的方案数量
                dp[i][j] = dp[i - 1][j];
                //如果选num 则方案数+dp[i - 1][j - num];
                if (j >= num)
                {
                    dp[i][j] += dp[i - 1][j - num];
                }
            }
        }
        return dp[n][neg];
    }
};
