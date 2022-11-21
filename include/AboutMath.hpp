#include "Util.h"
// 166. 分数到小数
class LT166Solution
{
public:
    string fractionToDecimal(int numerator, int denominator)
    {
        long numeratorLong = numerator;
        long denominatorLong = denominator;
        if (numeratorLong % denominatorLong == 0)
        {
            return to_string(numeratorLong / denominatorLong);
        }

        string ans;
        //^优先级 低于 < >
        if (numeratorLong < 0 ^ denominatorLong < 0)
        {
            ans.push_back('-');
        }

        // 整数部分
        numeratorLong = abs(numeratorLong);
        denominatorLong = abs(denominatorLong);
        long integerPart = numeratorLong / denominatorLong;
        ans += to_string(integerPart);
        ans.push_back('.');

        // 小数部分
        string fractionPart;
        unordered_map<long, int> remainderIndexMap;
        long remainder = numeratorLong % denominatorLong;
        int index = 0;
        // 利用一个map记录是否余数有重复
        while (remainder != 0 && !remainderIndexMap.count(remainder))
        {
            remainderIndexMap[remainder] = index;
            remainder *= 10;
            fractionPart += to_string(remainder / denominatorLong);
            remainder %= denominatorLong;
            index++;
        }
        if (remainder != 0)
        { // 有循环节
            // 重复余数的下标0.333 则返回index=0
            int insertIndex = remainderIndexMap[remainder];
            fractionPart = fractionPart.substr(0, insertIndex) + '(' + fractionPart.substr(insertIndex);
            fractionPart.push_back(')');
        }
        ans += fractionPart;

        return ans;
    }
};
// 171. Excel 表列序号
class LT171Solution
{
public:
    int titleToNumber(string columnTitle)
    {
        int ans = 0;
        int index = 1;
        int n = columnTitle.length();
        for (auto x : columnTitle)
        {
            int i = x - 'A' + 1;
            // ZYY = Z*26*26 + Y*26 + Y*1
            ans = ans + pow(26, (n - index)) * i;
            index++;
        }
        return ans;
    }
};

// 204. 计数质数
class LT204Solution
{
public:
    bool isaPrimeNumber(int number)
    {
        if (number <= 1)
            return false;
        int i = 2;
        while (i * i <= number)
        {
            if (number % i == 0)
                return false;
            i++;
        }
        return true;
    }
    // 超时
    int countPrimes2(int n)
    {
        if (n <= 1)
            return 0;
        // dp[i]代表小于i的质数数量
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 0;
        dp[2] = 0;
        for (int i = 3; i <= n; i++)
        {
            if (isaPrimeNumber(i - 1))
            {
                dp[i]++;
            }
            dp[i] += dp[i - 1];
        }
        return dp[n];
    }
    // 优化
    int countPrimes(int n)
    {
        vector<int> isPrime(n, 1);
        int ans = 0;
        for (int i = 2; i < n; ++i)
        {
            if (isPrime[i])
            {
                ans += 1;
                // n=7 i=2
                if ((long long)i * i < n)
                {
                    // 检测2的倍数 4 6 都不是质数
                    // 从 2x 开始标记其实是冗余的，应该直接从 x⋅x 开始标记
                    for (int j = i * i; j < n; j += i)
                    {
                        isPrime[j] = 0;
                    }
                }
            }
        }
        return ans;
    }
};
// 172. 阶乘后的零
class LT172Solution
{
public:
    // n!尾零即为n!中因为10的个数，而10=2*5
    int trailingZeroes(int n)
    {
        int ans = 0;
        // 遍历出5的倍数
        for (int i = 5; i <= n; i += 5)
        {
            // 50->10->2
            for (int x = i; x % 5 == 0; x /= 5)
            {
                ++ans;
            }
        }
        return ans;
    }
};


// 179. 最大数
class LT179Solution
{
public:
    string largestNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end(), [](const int &x, const int &y)
             {
            long sx = 10, sy = 10;
            while (sx <= x) {
                sx *= 10;
            }
            while (sy <= y) {
                sy *= 10;
            }
            //xy > yx
            return sy * x + y > sx * y + x; });
        if (nums[0] == 0)
        {
            return "0";
        }
        string ret;
        for (int &x : nums)
        {
            ret += to_string(x);
        }
        return ret;
    }
};
// 189. 轮转数组
class LT189Solution
{
public:
    void rotate(vector<int> &nums, int k)
    { // K=4
        k %= nums.size();
        // 123456->654321
        reverse(nums.begin(), nums.end());
        // 654321->345621
        reverse(nums.begin(), nums.begin() + k);
        // 345621->345612
        reverse(nums.begin() + k, nums.end());
    }
};

// 191. 位1的个数
class LT191Solution
{
public:
    int hammingWeight(uint32_t n)
    {
        int ans = 0;
        while (n)
        {
            n &= n - 1;
            ans++;
        }
        return ans;
    }
};

// 202. 快乐数
class LT202Solution
{
public:
    bool isHappy(int n)
    {
        while (n != 1)
        {
            // 这几个数最终都会变成20
            if (n == 0 || n == 2 || n == 3 || n == 4)
            {
                return false;
            }
            int temp = pow(n % 10, 2);
            while (n / 10 > 0)
            {
                n = n / 10;
                temp += pow(n % 10, 2);
            }
            n = temp;
        }
        return true;
    }
};