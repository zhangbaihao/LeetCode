#include "Util.h"
/*
他们的最大值分别为{4,4,6,6,6,5};
针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个：
{[2,3,4],2,6,2,5,1},
{2,[3,4,2],6,2,5,1},
{2,3,[4,2,6],2,5,1},
{2,3,4,[2,6,2],5,1},
{2,3,4,2,[6,2,5],1},
{2,3,4,2,6,[2,5,1]}。
*/
class LT59Solution
{
public:
    vector<int> maxInWindows(const vector<int> &nums, int size)
    {
        vector<int> ret;
        if (nums.size() == 0 || size < 1 || nums.size() < size)
            return ret;
        int n = nums.size();
        //用来存储vector中的下标，其中front代表滑动窗口最大值，
        deque<int> dq;
        for (int i = 0; i < n; ++i)
        {
            /*
            如果arr[i+1] > arr[i], 那么还要arr[i]有什么用.
            如果arr[i+1] < arr[i],显然arr[i]还是需要保留的。
            */
            while (!dq.empty() && nums[dq.back()] < nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);
            // 判断队列的头部的下标是否过期
            if (dq.front() + size <= i)
            {
                dq.pop_front();
            }
            // 判断是否形成了窗口
            if (i + 1 >= size)
            {
                ret.push_back(nums[dq.front()]);
            }
        }
        return ret;
    }
};
//239. 滑动窗口最大值
class LT239Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> ans;
        deque<int> m_deque;
        int n = nums.size();
        int maxValue = 0;
        for (int i = 0; i < n; i++)
        {
            while (!m_deque.empty() && nums[m_deque.back()] < nums[i])
            {
                //新来的比前一个都大，前一个可以不要了
                m_deque.pop_back();
            }
            m_deque.push_back(i);
            // front是当前最大的，如果过期则抛弃
            if (m_deque.front() + k <= i)
            {
                m_deque.pop_front();
            }
            if (i + 1 >= k)
                ans.push_back(nums[m_deque.front()]);
        }
        return ans;
    }
};

//438. 找到字符串中所有字母异位词
class LT438Solution {
public:
    vector<int> findAnagrams(string s, string p)
    {
        int sLen = s.size(), pLen = p.size();
        if (sLen < pLen)
        {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        //统计出每个字符数量，sCount滑动窗口形式
        for (int i = 0; i < pLen; ++i)
        {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount)
        {
            ans.emplace_back(0);
        }
        for (int i = 0; i < sLen - pLen; ++i)
        {
            //删除第一个字符
            --sCount[s[i] - 'a'];
            //添加新的一个字符 组成依旧是pLen长度的滑动窗口
            ++sCount[s[i + pLen] - 'a'];
            if (sCount == pCount)
            {
                ans.emplace_back(i + 1);
            }
        }
        return ans;
    }
};