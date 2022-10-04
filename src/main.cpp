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
//28. 找出字符串中第一个匹配项的下标
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
    //KMP
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
            //ababc->00120
            //  j=2 -> j=0
            //ababc -> ababc
            //    i=4 计算c字符时
            while (j > 0 && needle[i] != needle[j])
            {
                j = next[j - 1];
            }
            //0-j位置是匹配的 从下个位置开始
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
int main()
{
    Solution s;
    s.strStr2("abababbcccc", "abababc");

    cout << "---Solution Call---" << endl;
    return 0;
}