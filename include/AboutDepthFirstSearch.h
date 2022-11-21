#pragma once
#include "Util.h"

// 130. 被围绕的区域
class LT130Solution
{
public:
    int n, m;
    // 将从边界开始未O连起来的 做一个标记A
    void dfs(vector<vector<char>> &board, int x, int y)
    {
        if (x < 0 || x >= n || y < 0 || y >= m || board[x][y] != 'O')
        {
            return;
        }
        board[x][y] = 'A';
        dfs(board, x + 1, y);
        dfs(board, x - 1, y);
        dfs(board, x, y + 1);
        dfs(board, x, y - 1);
    }

    void solve(vector<vector<char>> &board)
    {
        n = board.size();
        if (n == 0)
        {
            return;
        }
        m = board[0].size();
        // 遍历左边界与右边界
        for (int i = 0; i < n; i++)
        {
            dfs(board, i, 0);
            dfs(board, i, m - 1);
        }
        // 遍历上边界与下边界
        for (int i = 1; i < m - 1; i++)
        {
            dfs(board, 0, i);
            dfs(board, n - 1, i);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            { // 已经被标记的
                if (board[i][j] == 'A')
                {
                    board[i][j] = 'O';
                } // 真正被X包围的O
                else if (board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

// 131. 分割回文串
class LT131Solution
{
private:
    vector<vector<int>> dp;
    vector<vector<string>> ret;
    vector<string> ans;
    int n;

public:
    void dfs(const string &s, int i)
    {
        if (i == n)
        {
            ret.push_back(ans);
            return;
        }
        for (int j = i; j < n; ++j)
        {
            if (dp[i][j])
            {
                ans.push_back(s.substr(i, j - i + 1));
                // aadb aa放入后 从d开始深度搜索
                dfs(s, j + 1);
                // 回溯
                ans.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s)
    {
        n = s.size();
        // 创建一个dp[i][j] 代表是s[i]-s[j]是回文字符串
        dp.assign(n, vector<int>(n, true));
        // 检测s[i-j]是回文字符串
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }

        dfs(s, 0);
        return ret;
    }
};