#include "Util.h"
// LT65 不用加减乘除做加法
class LT65Solution
{
public:
    int Add(int num1, int num2)
    {
        // add表示进位值
        int add = num2;
        // sum表示总和
        int sum = num1;
        // 当不再有进位的时候终止循环
        while (add != 0)
        {
            // 将每轮的无进位和与进位值做异或求和
            int temp = sum ^ add;
            // 进位值是用与运算产生的
            add = (sum & add) << 1;
            // 更新sum为新的和
            sum = temp;
        }
        return sum;
    }
};
// LT15 二进制中1的个数
class LT15Solution
{
public:
    int NumberOf1(int n)
    {
        int res = 0;
        //当n为0时停止比较
        while (n)
        {
            n &= n - 1;
            res++;
        }
        return res;
    }
};
// LT16 数值的整数次方
class LT16Solution
{
public:
    double Power(double base, int exponent)
    {
        double result = 1;
        int count = abs(exponent);
        while (count)
        {
            count--;
            if (exponent >= 0)
                result *= base;
            else
                result /= base;
        }
        return result;
    }
    double Power(double base, int exponent)
    {
        //处理负数次方
        if (exponent < 0)
        {
            base = 1 / base;
            exponent = -exponent;
        }
        double res = 1.0;
        //累乘
        for (int i = 0; i < exponent; i++)
            res *= base;
        return res;
    }
};
// 136. 只出现一次的数字
class LT136Solution
{
public:
    //
    int singleNumber(vector<int> &nums)
    {
        unordered_map<int, int> m;
        for (auto i : nums)
        {
            m[i]++;
        }
        for (auto it = m.begin(); it != m.end(); it++)
        {
            if (it->second == 1)
                return it->first;
        }
        return 0;
    }
    int singleNumber2(vector<int> &nums)
    {
        int ret = 0;
        for (auto e : nums)
            ret ^= e;
        return ret;
    }
};
// LT56 数组中只出现一次的两个数字
class LT56Solution
{
public:
    //输入：[1,4,1,6]  输出：4 6
    vector<int> FindNumsAppearOnce(vector<int> &array)
    {
        // write code here
        map<int, int> m;
        vector<int> result;
        for (auto i : array)
        {
            m[i]++;
        }
        for (auto it = m.begin(); it != m.end(); it++)
        {
            if (it->second == 1)
                result.push_back(it->first);
        }
        return result;
    }
    //输入：3 7 2 2 4 4
    vector<int> FindNumsAppearOnc2(vector<int> &array)
    {
        // 答案数组
        vector<int> ans(2);
        int res = 0;
        //对数组遍历进行异或运算
        for (int x : array)
        {
            res ^= x;
        }
        // res:0100 m:0100
        int m = 1;
        // 找到二进制上第一个1，该位置上两数二进制不同
        while (!(m & res))
            m <<= 1;
        //对数组遍历进行异或运算
        // 3:0011 7:0111 m:0100
        for (int x : array)
        {
            if (m & x)
                ans[1] ^= x; // 7:0111
            else
                ans[0] ^= x; // 2:0010 2:0010 3:0011
        }
        //交换结果集
        if (ans[0] > ans[1])
            swap(ans[0], ans[1]);
        return ans;
    }
    vector<int> FindNumsAppearOnc2(vector<int> &array)
    {
        //答案数组
        vector<int> ans(2);
        int x = 0;
        //只剩下两个出现一次数的异或结果x
        for (auto i : array)
        {
            x ^= i;
        }
        int m = 1;
        while (!(m & x))
        {
            m <<= 1;
        }
        for (auto i : array)
        {
            if(m & i){
                ans[0] ^= i;
            }else{
                ans[1] ^= i;
            }
        }
        return ans;
    }
};
// LT64 求1+2+3+...+n
//求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
class LT64Solution
{
public:
    //输入：5 输出：15 = 1+2+3+4+5
    int Sum_Solution(int n)
    {
        //&&逻辑与的短路执行特性，只要遇到一个假，后面则不再执行，直接返回假
        //即&& 等于 if(n<=0) return n;
        n && (n += Sum_Solution(n - 1));
        return n;
    }
};

//461. 汉明距离
class LT461Solution {
public:
    int hammingDistance(int x, int y)
    {
        int s = x ^ y;//进行异或
        int ret = 0;
        //统计1的个数
        while (s)
        {
            ret += s & 1;
            s = s >> 1;
        }
        return ret;
    }
};