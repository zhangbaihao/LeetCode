#include <iostream>
#include "AboutList.hpp"
#include "AboutOther.hpp"
#include "AboutSearch.hpp"
#include "AboutDynamicProgramming.hpp"
#include "AboutBack.hpp"
#include "AboutSimulation.hpp"
#include "AboutSort.hpp"
#include "AboutQueueAndStack.hpp"
#include "AboutGreedy.hpp"
#include "AboutTree.hpp"
// 739. 每日温度
class LT739Solution
{
public:
    //
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        int n = temperatures.size();
        //next[温度] 代表该温度的下标
        vector<int> ans(n,0), next(101, INT_MAX);
        for (int i = n - 1; i >= 0; --i)
        {
            int warmerIndex = INT_MAX;
            //从当前温度+1°枚举 next中比当前温度高的天数
            //23 25 22 24
            //         3
            for (int t = temperatures[i] + 1; t <= 100; ++t)
            {
                //选择天数最小的
                warmerIndex = min(warmerIndex, next[t]);
            }
            if (warmerIndex != INT_MAX)
            {
                //第一个温度比当天温度高的下标 - 当前下标
                ans[i] = warmerIndex - i;
            }
            //存温度对应的下标，同样温度的下标会被更新
            next[temperatures[i]] = i;
        }
        return ans;
    }
};

int main()
{
    cout << "---Solution Call---" << endl;
    //Solution test;

    return 0;
}