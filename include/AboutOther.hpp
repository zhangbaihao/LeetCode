#include "Util.h"
// LT66 构建乘积数组
class LT66Solution
{
public:
    //[1,2,3,4,5] [120,60,40,30,24] 120 = 2*3*4*5 60 = 1*3*4*5
    /*
    给定一个数组 A[0,1,...,n-1] ,请构建一个数组 B[0,1,...,n-1] ,其中 B 的元素 B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]
    （除 A[i] 以外的全部元素的的乘积）。程序中不能使用除法。
    （注意：规定 B[0] = A[1] * A[2] * ... * A[n-1]，B[n-1] = A[0] * A[1] * ... * A[n-2]）
    */
    vector<int> multiply(const vector<int> &A)
    {
        //初始化数组B
        vector<int> B(A.size(), 1);
        //先乘左边，从左到右
        for (int i = 1; i < A.size(); i++)
            //每多一位由数组B左边的元素多乘一个前面A的元素
            B[i] = B[i - 1] * A[i - 1];
        int temp = 1;
        //再乘除了自己以外的右边，从右到左
        for (int i = A.size() - 1; i >= 0; i--)
        {
            // temp为右边的累乘
            B[i] *= temp;
            temp *= A[i];
        }
        return B;
    }
};
// LT50 第一个只出现一次的字符
class LT50Solution
{
public:
    //"google" 4 这里是l "aa"  没有返回-1
    int FirstNotRepeatingChar(string str)
    {
        unordered_map<char, int> m;
        for (int i = 0; i < str.length(); i++)
        {
            m[str[i]]++;
        }
        for (int i = 0; i < str.length(); i++)
        {
            if (m[str[i]] == 1)
            {
                return i;
            }
        }
        return -1;
    }
};
// LT5 替换空格
class LT5Solution
{
public:
    //"We Are Happy"
    //"We%20Are%20Happy"
    string replaceSpace(string s)
    {
        string res = "";
        //遍历字符串
        for (int i = 0; i < s.length(); i++)
        {
            //非空格直接复制
            if (s[i] != ' ')
                res += s[i];
            //空格就替换
            else
                res += "%20";
        }
        return res;
    }
};
// LT21 调整数组顺序使奇数位于偶数前面(一)
class LT21Solution
{
public:
    //所有的奇数位于数组的前面部分，所有的偶数位于数组的后面部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变
    //输入：[1,2,3,4]
    //返回值：[1,3,2,4]
    vector<int> reOrderArray(vector<int> &array)
    {
        vector<int> anOddNumber;
        vector<int> anEvenNumber;
        for (auto i : array)
        {
            if (i % 2 == 0)
                anEvenNumber.push_back(i);
            else
                anOddNumber.push_back(i);
        }
        for (int i : anEvenNumber)
        {
            anOddNumber.push_back(i);
        }
        return anOddNumber;
    }
};
// LT39 数组中出现次数超过一半的数字
/*给一个长度为 n 的数组，数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
例如输入一个长度为9的数组[1,2,3,2,2,2,5,4,2]。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。*/
class LT39Solution
{
public:
    int MoreThanHalfNum_Solution(vector<int> numbers)
    {
        int length = numbers.size() / 2;
        unordered_map<int, int> m;
        for (auto i : numbers)
        {
            m[i]++;
            if (m[i] > length)
            {
                return i;
            }
        }
        return 0;
    }
};
// 需要学习其他解法
// LT43 整数中1出现的次数（从1到n整数中1出现的次数）
/*输入一个整数 n ，求 1～n 这 n 个整数的十进制表示中 1 出现的次数
例如， 1~13 中包含 1 的数字有 1 、 10 、 11 、 12 、 13 因此共出现 6 次
注意：11 这种情况算两次*/
class LT43Solution
{
public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            int k = 0;
            int number = i;
            while (number != 0)
            {
                if (number % 10 == 1)
                {
                    k++;
                }
                number = number / 10;
            }
            sum = sum + k;
        }
        return sum;
    }
    int NumberOf1Between1AndN_Solution2(int n)
    {
        int res = 0;
        // MulBase = 10^i
        long long MulBase = 1;
        //每个 十 百 千位数按照公式计算
        for (int i = 0; MulBase <= n; i++)
        {
            //根据公式添加 12345 假设计算到十位上的1
            // left= 4左边为123 123*10
            int left = n / (MulBase * 10) * MulBase;
            // right 如果 18<19则00010-00018 8-0+1总共9 如果45>19 123前缀去掉，即10-19=10
            int right = min(max(n % (MulBase * 10) - MulBase + 1, (long long)0), MulBase);
            res += left + right;
            //扩大一位数
            MulBase *= 10;
        }
        return res;
    }
    int NumberOf1Between1AndN_Solution3(int n)
    {
        int res = 0;
        long long k = 1;
        for (int i = 0; k <= n; i++)
        {
            int left = n / (k * 10) * k;
            int right = 0;
            if (n % (k * 10) > k * 2 - 1)
            {
                right = k;
            }
            else
            {
                right = n % (k * 10) - k + 1;
                if (right < 0)
                    right = 0;
            }
            res += left + right;
            k *= 10;
        }
        return res;
    }
};
// LT45 把数组排成最小的数
class LT45Solution
{
public:
    //重载排序比较方式
    static bool cmp(string &x, string &y)
    {
        //叠加
        return x + y < y + x;
    }
    string PrintMinNumber(vector<int> numbers)
    {
        string res = "";
        //空数组的情况
        if (numbers.size() == 0)
            return res;
        vector<string> nums;
        //将数字转成字符
        for (int i = 0; i < numbers.size(); i++)
            nums.push_back(to_string(numbers[i]));
        //排序
        sort(nums.begin(), nums.end(), cmp);
        //字符串叠加
        for (int i = 0; i < nums.size(); i++)
            res += nums[i];
        return res;
    }
};

// LT49 丑数
//丑数是指不能被2，3，5以外的其他素数整除的数
/*把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，
因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第 n个丑数。*/
class LT49Solution
{
public:
    // 1,2,3,4,5,6,8,9,10,12,15
    int GetUglyNumber_Solution(int index)
    {
        if (index <= 6)
        {
            return index;
        }
        int i2 = 0, i3 = 0, i5 = 0;
        vector<int> dp(index);
        dp[0] = 1;
        for (int i = 1; i < index; ++i)
        {
            int next2 = dp[i2] * 2, next3 = dp[i3] * 3, next5 = dp[i5] * 5;
            dp[i] = min(next2, min(next3, next5));
            if (dp[i] == next2)
                i2++;
            if (dp[i] == next3)
                i3++;
            if (dp[i] == next5)
                i5++;
        }
        return dp[index - 1];
    }
};
// LT74 和为S的连续正数序列
class LT74Solution
{
public: //数据范围：0<n≤100
    vector<vector<int>> FindContinuousSequence(int sum)
    {
        vector<vector<int>> array;
        for (int i = 1; i < sum; i++)
        {
            int res = 0;
            vector<int> a;
            for (int j = i; j < sum; j++)
            {
                res += j;
                a.push_back(j);
                if (res == sum)
                {
                    array.push_back(a);
                }
                else if (res > sum)
                {
                    break;
                }
            }
        }
        return array;
    }
};
// LT57 升序数组array 和为sum的两个数字
class LT57Solution
{
public: /*输入：[1,2,3,4],5
         返回值：[1,4]
         说明：返回[1,4],[4,1],[2,3],[3,2]都是可以的  */
    vector<int> FindNumbersWithSum(vector<int> array, int sum)
    {
        int i = 0;
        int j = array.size() - 1;
        vector<int> res;
        while (i < j)
        {
            int tmp = array[i] + array[j];
            if (tmp == sum)
            {
                res.push_back(array[i]);
                res.push_back(array[j]);
                return res;
            }
            else if (tmp > sum)
            {
                j--;
            }
            else
            {
                i++;
            }
        }
        return res;
    }
};
// LT58 左旋转字符串
class LT58Solution
{
public:
    //字符序列 S = ”abcXYZdef” , 要求输出循环左移 3 位后的结果，即 “XYZdefabc”
    string LeftRotateString(string str, int n)
    {
        string res = "";
        int length = str.length();
        if (length == 0 || n == 0)
            return str;
        n %= length;
        //先遍历后面的，放到前面
        for (int i = n; i < length; i++)
            res += str[i];
        //再遍历前面的放到后面
        for (int i = 0; i < n; i++)
            res += str[i];
        return res;
    }
};
//不理解公式(m+x)%n
// LT62 孩子们的游戏(圆圈中最后剩下的数)
class LT62Solution
{
public:
    //超时
    int LastRemaining_Solution(int n, int m)
    {
        //没有小朋友的情况
        if (n == 0 || m == 0)
            return -1;
        // 0表示还在 1表示走了需要跳过
        int people[5000] = {0};
        //剩下的人数
        int number = n;
        //数组下标
        int index = -1;
        //最后一个人
        int last = 0;
        //数了几个数
        int tmp = 0;
        // 每轮实际需要数的数
        int tmp_need = m;
        //还有人存活
        while (number != 0)
        {
            index++;
            if (index == n)
                index = 0;
            //此人还存在
            if (people[index] == 0)
            {
                tmp++;
            }
            //这个位置需要优化，当第m人多于剩下的人时
            if (m > number)
            {
                tmp_need = m % number;
                //如m = 4 number = 2 其实和m = 2一样
                if (tmp_need == 0)
                    tmp_need = number;
            }
            //满足数到第tmp_need人
            if (tmp == tmp_need)
            {
                //重置
                tmp = 0;
                //标记已经
                people[index] = 1;
                if (number == 1)
                {
                    last = index;
                }
                number--;
            }
        }
        return last;
    }
    int function(int n, int m)
    {
        if (n == 1)
            return 0;
        //递归
        int x = function(n - 1, m);
        //返回最后删除的那个元素
        return (m + x) % n;
    }
    int LastRemaining_Solution2(int n, int m)
    {
        //没有小朋友的情况
        if (n == 0 || m == 0)
            return -1;
        return function(n, m);
    }
};
// LT75 字符流中第一个不重复的字符
class LT75Solution
{
public:
    // Insert one char from stringstream
    unordered_map<char, int> m;
    char frist = '#';
    string str;
    int index = 0;
    void Insert(char ch)
    {
        m[ch]++;
        str += ch;
        if (frist == '#' && m[ch] == 1)
        {
            frist = ch;
            index = str.length();
            return;
        }
        if (frist == ch && m[ch] > 1)
        {
            frist = '#';
            //找到第一个出现次数为1的
            for (int i = index; i < str.length(); i++)
            {
                if (m[str[i]] == 1)
                {
                    frist = str[i];
                    index = i;
                    return;
                }
            }
        }
    }
    // return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        return frist;
    }
};
// LT14 剪绳子
class LT14Solution
{
public:
    int cutRope(int number)
    {
        //不超过3直接计算
        if (number <= 3)
            return number - 1;
        // dp[i]表示长度为i的绳子可以被剪出来的最大乘积
        vector<int> dp(number + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        dp[4] = 4;
        //遍历后续每一个长度
        for (int i = 5; i <= number; i++)
            //可以被分成两份
            for (int j = 1; j < i; j++)
                //取最大值
                dp[i] = max(dp[i], j * dp[i - j]);
        return dp[number];
    }
};
// LT81 调整数组顺序使奇数位于偶数前面(二)
class LT81Solution
{
public:
    vector<int> reOrderArrayTwo(vector<int> &array)
    {
        // write code here
        //奇数以及最后结果
        vector<int> anOddNumber;
        vector<int> anEvenNumber;
        int size = array.size();
        for (int i = 0; i < size; i++)
        {
            if (array[i] % 2 == 0)
            {
                anEvenNumber.push_back(array[i]);
            }
            else
            {
                anOddNumber.push_back(array[i]);
            }
        }
        for (int i = 0; i < anEvenNumber.size(); i++)
            anOddNumber.push_back(anEvenNumber[i]);
        return anOddNumber;
    }
};
// LT83 剪绳子（进阶版）
class LT83Solution
{
public:
    long long mod = 998244353;
    //快速乘法 5*7= 5*(0000 0111) = 5*（4+2+1）
    long long fast(long long x, long long y)
    {
        long long res = 0;
        x %= mod;
        y %= mod;
        while (y)
        {
            if (y & 1)
            {
                //加法代替乘法，防止越界
                res += x;
                if (res >= mod)
                    res -= mod;
            }
            y = y >> 1;
            x = x << 1;
            if (x >= mod)
                x -= mod;
        }
        return res;
    }
    //快速幂 7的二进制 0000 0111   5的7次方 = 5*(5*5)*(5*5*5*5)
    long long Pow(long long x, long long y)
    {
        long long res = 1;
        while (y)
        {
            //可以再往上乘一个
            if (y & 1)
                res = fast(res, x);
            //叠加
            x = fast(x, x);
            //减少乘次数
            y = y >> 1;
        }
        return res;
    }
    long long cutRope(long long number)
    {
        //不超过3直接计算
        if (number <= 3)
            return number - 1;
        //能整除3
        if (number % 3 == 0)
            return Pow(3, number / 3);
        //最后剩余1
        else if (number % 3 == 1)
            // 4*3^{n-1}
            return fast(Pow(3, number / 3 - 1), 4);
        //最后剩余2
        else
            // 2*3^n
            return fast(Pow(3, number / 3), 2);
    }
};

// LT17 打印从1到最大的n位数
class LT17Solution
{
public:
    vector<int> printNumbers(int n)
    {
        // write code here
        int max = 1;
        for (int i = 0; i < n; i++)
            max = max * 10;
        vector<int> res;
        for (int i = 1; i < max; i++)
        {
            res.push_back(i);
        }
        return res;
    }
};
//11. 盛最多水的容器
class LT011Solution {
public:
    int maxArea(vector<int>& height) {
        int maxvalue =0;
        int size = height.size();
        if(size<2)
            return 0;
        for(int i=0;i<size-1;++i){
            for(int j=1;j<size;j++){
                maxvalue = max((j-i)*min(height[i],height[j]),maxvalue);
            }
        }
        return maxvalue;
    }
};

// 169. 多数元素
class LT169Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int n = nums.size();
        int k = n / 2;
        map<int, int> m;
        for (int i = 0; i < n; i++)
        {
            m[nums[i]]++;
            if (m[nums[i]] > k)
            {
                return nums[i];
            }
        }
        return 0;
    }
};
//240. 搜索二维矩阵 II
class LT240Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int row = rows - 1, col = 0;
        while (col < cols && row >= 0)
        {
            if (matrix[row][col] == target)
                return true;
            else if (matrix[row][col] > target)
                row--;
            else
                col++;
        }
        return false;
    }
};