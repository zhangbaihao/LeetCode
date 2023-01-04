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
// 301. 删除无效的括号
class LT301Solution
{
private:
    vector<string> ret;
    bool isValid(string s)
    {
        int leftCount = 0;
        for (auto c : s)
        {
            if (c == '(')
                leftCount++;
            else if (c == ')')
            {
                leftCount--;
                if (leftCount < 0)
                    return false;
            }
        }
        return leftCount == 0;
    }
    void dfs(string s, int index, int lMin, int rMin)
    {
        //多余括号去除
        if (lMin == 0 && rMin == 0)
        {
            //合法加入
            if (isValid(s))
                ret.push_back(s);
            return;
        }
        for (int i = index; i < s.size(); i++)
        {
            //剪枝：去除重复答案：回溯时跳过连续的括号 (((() 这种去掉第二个( 当前字符((()， 当前轮次for循环没必要去掉第三个(再试一次
            if (i != index && s[i] == s[i - 1])
                continue;
            //剪枝：当所有需要去除的括号数量大于剩余的字符串数量时，直接return
            if (lMin + rMin > s.size() - i)
                return;
            //利用substr删除第 i个字符，i会自动指向下个字符的索引
            if (lMin > 0 && s[i] == '(')
                dfs(s.substr(0, i) + s.substr(i + 1), i, lMin - 1, rMin);
            if (rMin > 0 && s[i] == ')')
                dfs(s.substr(0, i) + s.substr(i + 1), i, lMin, rMin - 1);
        }
    }
public:
    vector<string> removeInvalidParentheses(string s)
    {
        // lMin 代表(多出的数量 RMin代表)多出的数量
        int lMin = 0, rMin = 0;
        for (auto c : s)
        {
            if (c == '(')
            {
                lMin++;
            }
            else if (c == ')')
            {
                if (lMin == 0)
                {
                    rMin++;
                }
                else
                {
                    lMin--;
                }
            }
        }
        dfs(s, 0, lMin, rMin);
        return ret;
    }
};

// 212. 单词搜索 II 前缀树+回溯  
class LT212Solution
{
public:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // 定义前缀树
    struct TrieNode
    {
        string word;
        unordered_map<char, TrieNode *> children;
        TrieNode()
        {
            this->word = "";
        }
    };
    //建立前缀树
    void insertTrie(TrieNode *root, const string &word)
    {
        TrieNode *node = root;

        for (auto c : word)
        {   //第一次字符
            if (!node->children.count(c))
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }

        node->word = word;
    }
    bool dfs(vector<vector<char>> &board, int x, int y, TrieNode *root, set<string> &res)
    {
        // 保存用于回溯
        char ch = board[x][y];

        if (root == nullptr || !root->children.count(ch))
        {
            return false;
        }
        //oath 走到h的Node 查看word是否被匹配过了
        TrieNode *nxt = root->children[ch];
        if (nxt->word.size() > 0)
        {
            res.insert(nxt->word);
            nxt->word = "";//设置为匹配过
        }
        //结点还有后续
        if (!nxt->children.empty())
        {
            board[x][y] = '#';
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dirs[i][0];
                int ny = y + dirs[i][1];
                if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size())
                {
                    if (board[nx][ny] != '#')
                    {
                        dfs(board, nx, ny, nxt, res);
                    }
                }
            }
            board[x][y] = ch;
        }
        //当前走到的结点后续全走完 从前缀树中移除
        if (nxt->children.empty())
        {
            root->children.erase(ch);
        }

        return true;
    }

    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        TrieNode *root = new TrieNode();

        for (auto &word : words)
        {
            insertTrie(root, word);
        }

        set<string> res;
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[0].size(); ++j)
            {
                dfs(board, i, j, root, res);
            }
        }

        vector<string> ans;
        for (auto &word : res)
        {
            ans.emplace_back(word);
        }

        return ans;
    }
};

// 289. 生命游戏
class LT289Solution
{
public:
    int isLiveOrDie(vector<vector<int>> &board, int row, int col)
    {

        int surroundingLivingCells = 0;
        for (int i = row - 1; i <= row + 1; i++)
        {
            if (i >= 0 && i < board.size())
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    if (j >= 0 && j < board[i].size())
                    {
                        if (i == row && j == col)
                            continue;
                        if (board[i][j] == 1)
                            surroundingLivingCells++;
                    }
                }
            }
        }
        // 原本状态
        if (board[row][col] == 1)
        {
            if (surroundingLivingCells == 2 || surroundingLivingCells == 3)
                return 1;
            else
                return 0;
        }
        else
        {
            if (surroundingLivingCells == 3)
                return 1;
            else
                return 0;
        }
    }
    void gameOfLife(vector<vector<int>> &board)
    {
        // 活细胞->死细胞 周围活细胞数目  不等于 2和3
        // 死细胞->活细胞 周围有3个活细胞
        vector<vector<int>> nextBoard = board;
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                nextBoard[i][j] = isLiveOrDie(board, i, j);
            }
        }
        board = nextBoard;
    }
};

// 329. 矩阵中的最长递增路径
class LT329Solution
{
public:
    int dirct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int ans = 0;
    int rows;
    int cols;
    int dfs(vector<vector<int>> &matrix, int row, int col, vector<vector<int>> &flag)
    {
        if (flag[row][col] != 0)
            return flag[row][col];
        flag[row][col]++;
        // 下上右左四个方向走
        for (int i = 0; i < 4; i++)
        {
            int x = row + dirct[i][0];
            int y = col + dirct[i][1];
            if (x >= 0 && x < rows && y >= 0 && y < cols)
            {
                if (matrix[x][y] > matrix[row][col])
                {
                    flag[row][col] = max(flag[row][col], dfs(matrix, x, y, flag) + 1);
                }
            }
        }
        return flag[row][col];
    }

    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
        {
            return 0;
        }

        rows = matrix.size();
        cols = matrix[0].size();
        /*使用记忆化深度优先搜索，当访问到一个单元格 (i,j)时，如果 memo[i][j]
        ≠0说明该单元格的结果尚未被计算过，则进行搜索，并将计算得到的结果存入缓存中。
        =0说明该单元格的结果已经计算过，则直接从缓存中读取结果，遍历完矩阵中的所有单元格之后，即可得到矩阵中的最长递增路径的长度*/
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                ans = max(ans, dfs(matrix, row, col, dp));
            }
        }
        return ans;
    }
};