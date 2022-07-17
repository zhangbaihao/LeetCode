#include "Util.h"
// 17. 电话号码的字母组合
class LT017Solution
{
public:
    unordered_map<char, string> phoneMap{
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}};
    // res存放结果 index代表从digiths取到几个数字 combination代表一种结果
    void backtrack(vector<string> &res, string digiths, int index, string combination)
    {
        int size = digiths.size();
        if (index == size)
            res.push_back(combination);
        else
        {
            string str = phoneMap[digiths[index]];
            for (int i = 0; i < str.length(); ++i)
            {
                combination.push_back(str[i]);
                backtrack(res, digiths, index + 1, combination);
                combination.pop_back();
            }
        }
    }
    vector<string> letterCombinations(string digits)
    {
        vector<string> res;
        if (digits.empty())
        {
            return res;
        }
        string combination;
        backtrack(res, digits, 0, combination);
        return res;
    }
};
// 22. 括号生成
class LT022Solution
{
public:
    /*输入：n = 3
    输出：["((()))","(()())","(())()","()(())","()()()"]*/
    vector<string> res;
    void Parenthesis(string str, int n, int index1, int index2)
    {
        if (index1 == n && index2 == n)
            res.push_back(str);
        if (index1 < n)
        {
            Parenthesis(str + "(", n, index1 + 1, index2);
        }
        if (index2 < n && index1 > index2)
        {
            Parenthesis(str + ")", n, index1, index2 + 1);
        }
    }
    vector<string> generateParenthesis(int n)
    {
        string tmp = "";
        Parenthesis(tmp, n, 0, 0);
        return res;
    }
};
// 32. 最长有效括号
class LT032Solution
{
public:
    // s = ")()())" 答案：4 即()()
    //")()())" "()(()"
    //")()())()()(" "))))())()()(()"
    int longestValidParentheses(string s)
    {
        int maxans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else
            {
                stk.pop();
                //保证只有"第一个("
                if (stk.empty())
                {
                    stk.push(i);
                }
                else
                {
                    maxans = max(maxans, i - stk.top());
                }
            }
        }
        return maxans;
    }
};

// 39. 组合总和
class LT039Solution
{
public:
    //输入: candidates = [2,3,5], target = 8
    //输出: [[2,2,2,2],[2,3,3],[3,5]]
    vector<int> combine;
    void dfs(vector<int> &candidates, int target, vector<vector<int>> &ans, int idx)
    {
        if (idx == candidates.size())
        {
            return;
        }
        if (target == 0)
        {
            ans.emplace_back(combine);
            return;
        }
        // 直接跳过
        dfs(candidates, target, ans, idx + 1);
        // 选择当前数
        if (target - candidates[idx] >= 0)
        {
            combine.emplace_back(candidates[idx]);
            dfs(candidates, target - candidates[idx], ans, idx);
            combine.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        dfs(candidates, target, ans, 0);
        return ans;
    }
};
// 46. 全排列
class LT046Solution
{
public:
    // 输入：nums = [1,2,3]
    // 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    void dfs(vector<vector<int>> &res, vector<int> &nums, int idx)
    {
        int n = nums.size();
        if (idx == n)
        {
            res.emplace_back(nums);
            return;
        }
        for (int i = idx; i < n; ++i)
        {
            swap(nums[i], nums[idx]);
            dfs(res, nums, idx + 1);
            swap(nums[i], nums[idx]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        dfs(res, nums, 0);
        return res;
    }
};
// 48. 旋转图像
class LT048Solution
{
public:
    // 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    // 输出：[[7,4,1],[8,5,2],[9,6,3]
    void rotate(vector<vector<int>> &matrix)
    {
        auto new_matrix = matrix;
        int n = matrix.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                new_matrix[j][n - 1 - i] = matrix[i][j];
            }
        }
        matrix = new_matrix;
    }
};
// 78. 子集
class LT078Solution
{
public:
    vector<int> t;
    vector<vector<int>> ans;

    void dfs(int cur, vector<int> &nums)
    {
        // 满足下标
        if (cur == nums.size())
        {
            ans.push_back(t);
            return;
        }
        //取当前下标数字
        t.push_back(nums[cur]);
        dfs(cur + 1, nums);
        t.pop_back();
        //不取当前下标数字
        dfs(cur + 1, nums);
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(0, nums);
        return ans;
    }
};
// 79. 单词搜索
class LT079Solution
{
public:
    bool ok = false;
    void check(vector<vector<char>> &board, string word, int i, int j, int idx, vector<vector<bool>> &flag)
    {
        //当前字符不满足|| 当前已经走过 ||已经找到路径 
        if (board[i][j] != word[idx] || flag[i][j] || ok)
        {
            return;
        }

        if (idx == word.length() - 1)
        {
            ok = true;
            return;
        }
        //标记已经走过
        flag[i][j] = true;
        //尝试往上下左右四个方向行动
        if (i - 1 >= 0)
        {
            check(board, word, i - 1, j, idx + 1, flag);
        }
        if (i + 1 < board.size())
        {
            check(board, word, i + 1, j, idx + 1, flag);
        }
        if (j - 1 >= 0)
        {
            check(board, word, i, j - 1, idx + 1, flag);
        }
        if (j + 1 < board[i].size())
        {
            check(board, word, i, j + 1, idx + 1, flag);
        }
        flag[i][j] = false;
    }
    bool exist(vector<vector<char>> &board, string word)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                vector<vector<bool>> dp(board.size(), vector<bool>(board[i].size(), false));
                check(board, word, i, j, 0, dp);
            }
        }
        return ok;
    }
};
// LT12 矩阵中的路径
class LT12Solution
{
public:
    // k代表走过的路程大小，从(row,col)点走
    bool dfs(vector<vector<char>> matrix, string word, int k, int row, int col)
    {
        if (matrix[row][col] != word[k])
            return false;
        //把每次成功找到的走过的路径上的字符设置为*；防止str中存在重复的元素
        matrix[row][col] = '#';
        k++;
        //当找到的路径数目等于字符长度，那么说明路径已经找到了
        if (k == word.size())
            return true;
        //定义四个方向坐标 {上下,左右}
        int dirct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; i++)
        {
            //从x y往上下左右四个方向走
            int row1 = row + dirct[i][0];
            int col1 = col + dirct[i][1];
            if (col1 >= 0 && col1 < matrix[0].size() && row1 >= 0 && row1 < matrix.size())
                if (dfs(matrix, word, k, row1, col1))
                    return true;
        }
        return false;
    }
    bool hasPath(vector<vector<char>> &matrix, string word)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (dfs(matrix, word, 0, i, j))
                    return true;
            }
        }
        return false;
    }
};

// LT13 机器人的运动范围
// 10,1,100 返回值29
//说明：
/*[0,0],[0,1],[0,2],[0,3],[0,4],[0,5],[0,6],[0,7],[0,8],[0,9],[0,10],[0,11],[0,12],
[0,13],[0,14],[0,15],[0,16],[0,17],[0,18],[0,19],[0,20],[0,21],[0,22],[0,23],[0,24],
[0,25],[0,26],[0,27],[0,28] 这29种，后面的[0,29],[0,30]以及[0,31]等等是无法到达的
*/
// 0≤threshold≤15 1≤rows,cols≤100
class LT13Solution
{
public:
    int flags[100][100];
    //往              右       下      左        上
    int dx[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    void dfs(int threshold, int row, int col, int rows, int cols, int &count)
    {
        flags[row][col] = 1;
        count = count + 1;
        for (int j = 0; j < 4; j++)
        {
            int row_t = row + dx[j][0];
            int col_t = col + dx[j][1];
            if (col_t >= 0 && col_t < cols && row_t >= 0 && row_t < rows)
            {
                //这里还要防止往回走
                if (flags[row_t][col_t] == 1)
                    continue;
                int rowSum = row_t % 10 + (row_t / 10) % 10;
                int colSum = col_t % 10 + (col_t / 10) % 10;
                //不能进入行坐标和列坐标的数位之和大于 threshold 的格子
                if (rowSum + colSum > threshold)
                {
                    continue;
                }
                dfs(threshold, row_t, col_t, rows, cols, count);
            }
        }
    }
    int movingCount(int threshold, int rows, int cols)
    {
        int count = 0;
        dfs(threshold, 0, 0, rows, cols, count);
        return count;
    }
};
