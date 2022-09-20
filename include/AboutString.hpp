#include "Util.h"
// 6. Z 字形变换
class LT006Solution
{
public:
    string convert(string s, int numRows)
    {
        if (numRows < 2)
            return s;
        vector<string> temp(numRows, "");
        int i = 0;
        int flag = -1;
        for (auto x : s)
        {
            temp[i] += x;
            if (i == 0 || i == numRows - 1)
                flag = -flag;
            i += flag;
        }
        string res = "";
        for (int i = 0; i < numRows; i++)
        {
            res += temp[i];
        }
        return res;
    }
};

// 7. 整数反转
class LT007Solution
{
public:
    int reverse(int x)
    {
        int rev = 0;
        while (x != 0)
        {
            //INT_MAX=2147483647
            //若此时数 > 2147483640 无论下面digit是多少都会>INT_MAX
            if (rev < INT_MIN / 10 || rev > INT_MAX / 10)
            {
                return 0;
            }
            int digit = x % 10;
            x /= 10;
            rev = rev * 10 + digit;
        }
        return rev;
    }
};

// 647. 回文子串
class LT647Solution
{
public:
    int countSubstrings(string s)
    {
        int n = s.size(), ans = 0;
        for (int i = 0; i < 2 * n - 1; ++i)
        {
            //以i/2为中心
            int l = i / 2;
            int r = i / 2 + i % 2;
            while (l >= 0 && r < n && s[l] == s[r])
            {
                --l;
                ++r;
                ++ans;
            }
        }
        return ans;
    }
};