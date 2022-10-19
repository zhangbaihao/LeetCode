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
            // INT_MAX=2147483647
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
// 8. 字符串转换整数 (atoi)
class LT008Solution
{
public:
    //状态机
    unordered_map<string, vector<string>> theStateMachine = {
        {"start", {"start", "sign", "in_number", "end"}},
        {"sign", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}};
    int get(char c)
    {
        if (isspace(c))
        {
            return 0;
        }
        else if (c == '+' or c == '-')
        {
            return 1;
        }
        else if (isdigit(c))
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
    int myAtoi(string str)
    {
        string state = "start";
        long long ans = 0;
        int sign = 1;
        for (auto c : str)
        {
            state = theStateMachine[state][get(c)];
            if (state == "in_number")
            {
                ans = ans * 10 + c - '0';
                ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
            }
            else if (state == "sign")
            {
                sign = c == '+' ? 1 : -1;
            }
        }
        return sign * ans;
    }
};
// 9. 回文数
class LT009Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0 || (x % 10 == 0 && x != 0))
        {
            return false;
        }
        string str = to_string(x);
        int length = str.length();
        for (int i = 0, j = length - 1; i < length && i < j; ++i, --j)
        {
            if (str[i] != str[j])
                return false;
        }
        return true;
    }
};
// 12. 整数转罗马数字
class LT012Solution
{
public:
    //单位的数量 单位最小 中间 最高 如:输入百位的个数 "X" = 100,"L" == 500 ,"C" = 1000
    string Roman(string res, int count, string lower, string mid, string upper)
    {
        if (count > 0)
        {
            if (count < 4)
            {
                while (count--)
                {
                    res += lower;
                }
            }
            else if (count == 4)
            {
                res += lower;
                res += mid;
            }
            else if (count == 5)
            {
                res += mid;
            }
            else if (count == 9)
            {
                res += lower;
                res += upper;
            }
            else
            { //范围在mid-upper
                res += mid;
                while (count-- > 5)
                {
                    res += lower;
                }
            }
        }
        return res;
    }
    string intToRoman(int num)
    {
        int thousand = num / 1000;
        int best = (num - thousand * 1000) / 100;
        int ten = (num - thousand * 1000 - best * 100) / 10;
        int singleDigits = num % 10;
        string str = "";
        while (thousand--)
        {
            str += "M";
        }
        //依次计算千 百 个 的罗马数字
        str = Roman(str, best, "C", "D", "M");
        str = Roman(str, ten, "X", "L", "C");
        str = Roman(str, singleDigits, "I", "V", "X");
        return str;
    }
};
// 13. 罗马数字转整数
class LT013Solution
{
private:
    unordered_map<char, int> symbolValues = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

public:
    int romanToInt(string s)
    {
        int ans = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i)
        {
            int value = symbolValues[s[i]];
            //"CM" symbolValues[C] < symbolValues[M] 先-100 后+1000
            if (i < n - 1 && value < symbolValues[s[i + 1]])
            {
                ans -= value;
            }
            else
            {
                ans += value;
            }
        }
        return ans;
    }
};
// 14. 最长公共前缀
class LT014Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        string res = "";
        if (strs.empty())
            return res;
        long long resLength = strs[0].length();
        for (int i = 0; i < resLength; ++i)
        {
            for (int j = 0; j < strs.size() - 1; ++j)
            {
                //更新最小的长度
                if (strs[j].length() < resLength)
                {
                    resLength = strs[j].length();
                    //下标已经超过最小的字符串长度
                    if (i >= resLength)
                        break;
                }
                //当前字符不符合前缀
                if (strs[j][i] != strs[j + 1][i])
                    return res;
            }
            res += strs[0][i];
        }
        return res;
    }
};
// 28. 找出字符串中第一个匹配项的下标
class LT028Solution
{
public:
    int strStr(string haystack, string needle)
    {
        if (needle.size() > haystack.size())
            return -1;
        for (int i = 0; i <= haystack.length() - needle.length(); i++)
        {
            int j = 0;
            int temp = i;
            while (haystack[temp] == needle[j])
            {
                temp++;
                j++;
                if (j == needle.length())
                    return i;
            }
        }
        return -1;
    }
    // KMP
    int strStr2(string haystack, string needle)
    {
        int n = haystack.size(), m = needle.size();
        if (m == 0)
        {
            return 0;
        }
        vector<int> next(m);

        //通过needle字符串计算next数组
        for (int i = 1, j = 0; i < m; i++)
        {
            // ababc->00120
            //   j=2 -> j=0
            // ababc -> ababc
            //     i=4 计算c字符时
            while (j > 0 && needle[i] != needle[j])
            {
                j = next[j - 1];
            }
            // 0-j位置是匹配的 从下个位置开始
            if (needle[i] == needle[j])
            {
                j++;
            }
            next[i] = j;
        }
        //在i一直前进的情况，匹配ababc 如匹配到c不对 可以直接j回到第二个ab 的a
        for (int i = 0, j = 0; i < n; i++)
        {
            while (j > 0 && haystack[i] != needle[j])
            {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j])
            {
                j++;
            }
            if (j == m)
            {
                return i - m + 1;
            }
        }
        return -1;
    }
};
//38. 外观数列
class LT038Solution {
public:
    string countAndSay(int n)
    {
        string prev = "1";
        //n=2  n=3 n=4   n=5
        //11   21  1211  111221
        for (int i = 2; i <= n; ++i)
        {
            string curr = "";
            int start = 0;
            int pos = 0;

            while (pos < prev.size())
            {
                //找到第一个与前面字符不一样的如1112的2->312
                while (pos < prev.size() && prev[pos] == prev[start])
                {
                    pos++;
                }
                curr += to_string(pos - start) + prev[start];
                start = pos;
            }
            prev = curr;
        }

        return prev;
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