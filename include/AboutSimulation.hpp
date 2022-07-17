#include "Util.h"
// LT29 顺时针打印矩阵
class LT29Solution
{
public:
    /*
    [[1,2,3,4],
    [5,6,7,8],
    [9,10,11,12],
    [13,14,15,16]]
    输出：[1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10]*/
    vector<int> printMatrix(vector<vector<int>> matrix)
    {
        vector<int> res;
        int n = matrix.size();
        //先排除特殊情况
        if (n == 0)
            return res;
        //左边界
        int left = 0;
        //右边界
        int right = matrix[0].size() - 1;
        //上边界
        int up = 0;
        //下边界
        int down = n - 1;
        //直到边界重合
        while (left <= right && up <= down)
        {
            //上边界的从左到右
            for (int i = left; i <= right; i++)
                res.push_back(matrix[up][i]);
            //上边界向下
            up++;
            if (up > down)
                break;
            //右边界的从上到下
            for (int i = up; i <= down; i++)
                res.push_back(matrix[i][right]);
            //右边界向左
            right--;
            if (left > right)
                break;
            //下边界的从右到左
            for (int i = right; i >= left; i--)
                res.push_back(matrix[down][i]);
            //下边界向上
            down--;
            if (up > down)
                break;
            //左边界的从下到上
            for (int i = down; i >= up; i--)
                res.push_back(matrix[i][left]);
            //左边界向右
            left++;
            if (left > right)
                break;
        }
        return res;
    }
};
// LT61 扑克牌顺子
class LT61Solution
{
public:
    /*1. A为1，J为11，Q为12，K为13，A不能视为14
      2. 大、小王为 0，0可以看作任意牌*/
    //输入：[6,0,2,0,4] 0 = 3 0 = 5  23456为顺子 返回值:true
    bool IsContinuous(vector<int> numbers)
    {
        sort(numbers.begin(), numbers.end());
        int zero_num = 0; //统计大小王数量
        int i = 0;
        while (numbers[i] == 0)
            zero_num++, i++;
        int interrapt = 0; //记录五张牌中最大值max到最小值min的距离
        for (; i < numbers.size() - 1; ++i)
        {
            if (numbers[i] == numbers[i + 1])
                return false;                             //出现相同的扑克牌
            interrapt += numbers[i + 1] - numbers[i] - 1; //计算距离
        }
        if (zero_num >= interrapt)
            return true;
        return false;
    }
};

/*写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。传入的字符串可能有以下部分组成:
1.若干空格
2.（可选）一个符号字符（'+' 或 '-'）
3. 数字，字母，符号，空格组成的字符串表达式
4. 若干空格

转换算法如下:
1.去掉无用的前导空格
2.第一个非空字符为+或者-号时，作为该整数的正负号，如果没有符号，默认为正数
3.判断整数的有效部分：
3.1 确定符号位之后，与之后面尽可能多的连续数字组合起来成为有效整数数字，如果没有有效的整数部分，那么直接返回0
3.2 将字符串前面的整数部分取出，后面可能会存在存在多余的字符(字母，符号，空格等)，这些字符可以被忽略，它们对于函数不应该造成影响
3.3  整数超过 32 位有符号整数范围 [−2^31,  2^31 − 1] ，需要截断这个整数，使其保持在这个范围内。
具体来说，小于 −2^31的整数应该被调整为 −2^31 ，大于 2^31 − 1 的整数应该被调整为 2^31 − 1
4.去掉无用的后导空格*/
// LT67 把字符串转换成整数(atoi)
class LT67Solution
{
public:
    int StrToInt(string s)
    {
        long res = 0;
        int index = 0;
        int n = s.length();
        //去掉前导空格，如果有
        while (index < n)
        {
            if (s[index] == ' ')
                index++;
            else
                break;
        }
        //去掉空格就什么都没有了
        if (index == n)
            return 0;
        int sign = 1;
        //处理第一个符号是正负号的情况
        if (s[index] == '+')
            index++;
        else if (s[index] == '-')
        {
            index++;
            sign = -1;
        }
        //去掉符号就什么都没有了
        if (index == n)
            return 0;
        while (index < n)
        {
            char c = s[index];
            //后续非法字符，截断
            if (c < '0' || c > '9')
                break;
            //处理越界
            res = res * 10 + sign * (c - '0');
            if (res >= INT_MAX)
                return INT_MAX;
            if (res <= INT_MIN)
                return INT_MIN;
            index++;
        }
        return res;
    }
};
// LT20 表示数值的字符串
/*科学计数法的数字(按顺序）可以分成以下几个部分:
1.若干空格
2.一个整数或者小数
3.（可选）一个 'e' 或 'E' ，后面跟着一个整数(可正可负)
4.若干空格

小数（按顺序）可以分成以下几个部分：
1.若干空格
2.（可选）一个符号字符（'+' 或 '-'）
3. 可能是以下描述格式之一:
3.1 至少一位数字，后面跟着一个点 '.'
3.2 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
3.3 一个点 '.' ，后面跟着至少一位数字
4.若干空格

整数（按顺序）可以分成以下几个部分：
1.若干空格
2.（可选）一个符号字符（'+' 或 '-')
3. 至少一位数字
4.若干空格*/
//例如，字符串["+100","5e2","-123","3.1416","-1E-16"]都表示数值。
//但是["12e","1a3.14","1.2.3","+-5","12e+4.3"]都不是数值。
class LT20Solution
{
public:
    int index = 0;
    //有符号判断
    bool integer(string &s)
    {
        if (index < s.length() && (s[index] == '-' || s[index] == '+'))
            index++;
        return unsigned_integer(s);
    }
    //无符号数判断
    bool unsigned_integer(string &s)
    {
        int temp = index;
        while (index < s.length() && (s[index] >= '0' && s[index] <= '9'))
            index++;
        return index > temp;
    }
    bool isNumeric(string str)
    {
        //先判断空串
        if (str.length() == 0)
            return false;
        //去除前面的空格
        while (index < str.length() && str[index] == ' ')
            index++;
        int n = str.length() - 1;
        //去除字符串后面的空格
        while (n >= 0 && str[n] == ' ')
            n--;
        //限制的长度应该是有效下标后一位
        n++;
        //全是空格情况
        if (n < index)
            return false;
        //判断前面的字符是否是有符号的整数
        bool flag = integer(str);
        //如果有小数点
        if (index < n && str[index] == '.')
        {
            index++;
            //小数点前后有无数字可选
            flag = unsigned_integer(str) || flag;
        }
        //如果有e
        if (index < n && (str[index] == 'e' || str[index] == 'E'))
        {
            index++;
            // e后面必须全是整数
            flag = flag && integer(str);
        }
        //是否字符串遍历结束
        return flag && (index == n);
    }
};
