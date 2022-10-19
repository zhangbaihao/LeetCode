#include <iostream>
#include "AboutAnOperation.hpp"
#include "AboutBack.hpp"
#include "AboutChart.hpp"
#include "AboutCheckAndSet.hpp"
#include "AboutDynamicProgramming.hpp"
#include "AboutGreedy.hpp"
#include "AboutHard.hpp"
#include "AboutHash.hpp"
#include "AboutHeap.hpp"
#include "AboutList.hpp"
#include "AboutOther.hpp"
#include "AboutQueueAndStack.hpp"
#include "AboutSearch.hpp"
#include "AboutSimulation.hpp"
#include "AboutSlidingWindow.hpp"
#include "AboutSort.hpp"
#include "AboutStack.hpp"
#include "AboutTree.hpp"
#include "AboutSum.hpp"
//44. 通配符匹配
class LT044Solution
{
public:
    bool isMatch(string s, string p)
    {
        int m = s.size();
        int n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i)
        {
            if (p[i - 1] == '*')
            {
                dp[0][i] = true;
            }
            else
            {
                break;
            }
        }
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

int main()
{
    Solution s;

    cout << "---Solution Call---" << endl;
    return 0;
}