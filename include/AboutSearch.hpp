#pragma once
#include "Util.h"
// 34. 在排序数组中查找元素的第一个和最后一个位置
class LT034Solution
{
public:
    //输入：nums = [5,7,7,8,8,10], target = 8
    //输出：[3,4]
    int binarySearch(vector<int> &nums, int target, bool lower)
    {
        int left = 0, right = nums.size();
        while (left < right)
        {
            int mid = (left + right) >> 1;
            if (nums[mid] < target || (lower && nums[mid] <= target))
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return left;
    }
    vector<int> searchRange(vector<int> &nums, int target)
    {
        // lower=false 则找第一个target下标
        int leftIdx = binarySearch(nums, target, false);
        if (leftIdx >= nums.size())
            return vector<int>{-1, -1};
        // lower=true 找第一个比target大的下标
        int rightIdx = binarySearch(nums, target, true) - 1;
        if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target)
        {
            return vector<int>{leftIdx, rightIdx};
        }
        return vector<int>{-1, -1};
    }
};

// LT53 数字在升序数组中出现的次数
class LT53Solution
{
public:
    //[1,2,3,3,3,3,3,3],3 返回值 4
    int GetNumberOfK1(vector<int> data, int k)
    {
        int count = 0;
        for (int i = 0; i < data.size(); ++i)
        {
            if (data[i] == k)
            {
                count++;
            }
            if (count == 0 && data[i] > k)
                return 0;
        }
        return count;
    }
    //二分查找
    int GetNumberOfK2(vector<int> nums, int target)
    {
        int lbound = 0, rbound = 0;
        //下界第一个等于target数
        int l = 0, r = nums.size();
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        lbound = l;
        // 寻找上界 即第一个比target大的数
        l = 0, r = nums.size();
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        rbound = l;
        return rbound - lbound;
    }
};

// LT4 二维数组中的查找
class LT4Solution
{
public:
    bool Find1(int target, vector<vector<int>> array)
    {
        for (auto i : array) // c++11语法
        {
            for (auto j : i)
            {
                if (j == target)
                    return true; //找到目标值
            }
        }
        return false; //未找到
    }
    bool BinarySearch(int target, vector<int> array)
    {
        int l = 0, r = array.size() - 1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (array[mid] == target)
            {
                return true;
            }
            else if (array[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return false;
    }
    bool Find2(int target, vector<vector<int>> array)
    {
        for (auto i : array)
        {
            if (BinarySearch(target, i))
            {
                return true;
            }
        }
        return false;
    }
    bool Find3(int target, vector<vector<int>> array)
    {
        int rows = array.size();
        int k = 0;
        for (int i = rows - 1; i >= 0; i--)
        {
            int cols = array[i].size();
            if (cols == 0)
                return false;
            if (array[i][0] > target)
            {
                continue;
            }
            for (int j = k; j < cols; j++)
            {
                if (array[i][j] == target)
                    return true;
                else if (array[i][j] > target)
                {
                    k = j - 1;
                    break;
                }
            }
        }
        return false;
    }
};
// 139. 单词拆分
class LT139Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> m;
        for (auto s : wordDict)
        {
            m.insert(s);
        }
        int size = s.length();
        //定义 dp[i] 表示字符串 s 前 i 个字符组成的字符串,s[0..i−1] 是否能被空格拆分成若干个字典中出现的单词
        vector<bool> dp(size + 1, false);
        dp[0] = true;
        for (int i = 1; i <= size; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (dp[j] && m.find(s.substr(j, i - j)) != m.end())
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[size];
    }
};
// LT11 旋转数组的最小数字
class LT11Solution
{
public:
    int minNumberInRotateArray(vector<int> rotateArray)
    {
        int l = 0;
        int r = rotateArray.size() - 1;
        while (l < r)
        {
            int mid = (l + r) / 2;
            //原本有序 旋转后说明最小值一定在右边
            if (rotateArray[mid] > rotateArray[r])
            {
                l = mid + 1;
            } //重复的值
            else if (rotateArray[mid] == rotateArray[r])
            {
                r = r - 1;
            }
            else
            {
                r = mid;
            }
        }
        return rotateArray[l];
    }
};
// LT38 字符串的排列
class LT38Solution
{
public:
    set<string> str1;
    void recursion(std::string str, int length, int n)
    {
        if (n == length)
            str1.insert(str);
        //第n个与之后的第i字母进行交换，其中i=0 则为本身不变 如Permutation("ABC",3,1) = ABC + A(BC)交换
        for (int i = 0; i + n < length; i++)
        {
            char temp = str[n + i];
            str[n + i] = str[n];
            str[n] = temp;
            recursion(str, length, n + 1);
        }
    }
    vector<string> Permutation(string str)
    {
        vector<string> res;
        if (str.length() > 0)
            recursion(str, str.length(), 0);
        for (auto a = str1.begin(); a != str1.end(); a++)
        {
            res.push_back(*a);
        }
        return res;
    }
};

// LT44 数字序列中某一位的数字
class LT44Solution
{
public:
    /*
    1-9       9个*1
    10-99     90个*2
    100-999   900个*3
    1000-9999 9000个*4
    */
    int findNthDigit(int n)
    {
        if (n == 0)
            return 0;
        long long start = 1; //起始数
        long long digit = 1; //记录位数
        long long count = 9; //记录区间个数，比如9 90 900
        while (n > count)
        {
            n -= count;
            start *= 10;
            digit++;                   // 1-9 ~ 1位  10-99 2位
            count = 9 * start * digit; // 1位数 9 -2位数 90 - 3位数 900
        }
        //从start开始第在哪个数 如100开始 + 270 则370
        long long number = start + (n - 1) / digit;
        //从这个number第几位 temp 范围应该是1~digit
        int temp = 1 + (n - 1) % digit;
        for (int i = digit; i > temp; i--)
        {
            //每次去掉最后一位
            number /= 10;
        }
        // number最后一位数字
        return number % 10;
    }
};
// 200. 岛屿数量
class LT200Solution
{
    void dfs(vector<vector<char>> &grid, int i, int j)
    {
        int h = grid.size();
        int w = grid[0].size();

        grid[i][j] = '0';
        //上下行清空
        if (i - 1 >= 0 && grid[i - 1][j] == '1')
            dfs(grid, i - 1, j);
        if (i + 1 < h && grid[i + 1][j] == '1')
            dfs(grid, i + 1, j);
        //左右列清空
        if (j - 1 >= 0 && grid[i][j - 1] == '1')
            dfs(grid, i, j - 1);
        if (j + 1 < w && grid[i][j + 1] == '1')
            dfs(grid, i, j + 1);
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int h = grid.size();
        if (!h)
            return 0;
        int w = grid[0].size();

        int num_islands = 0;
        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                if (grid[i][j] == '1')
                {
                    ++num_islands;
                    //统计完成后 把上下左右连着的岛屿 清空成0
                    dfs(grid, i, j);
                }
            }
        }
        return num_islands;
    }
};
// 240. 搜索二维矩阵 II
class LT240Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
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