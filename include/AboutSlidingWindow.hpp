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

// 395. 至少有 K 个重复字符的最长子串
class LT395Solution
{
public:
    int longestSubstring(string s, int k)
    {
        int ret = 0;
        int n = s.length();
        // 滑动窗口支持字符种类的数量,从1 类似aaaa这种到 26 支持aababcccb这种
        for (int t = 1; t <= 26; t++)
        {
            int l = 0, r = 0;
            // 滑动窗口内部每个字符出现的次数
            vector<int> cnt(26, 0);
            // 滑动窗口内的字符种类数目
            int tot = 0;
            // 计数器 less，代表滑动窗口中当前出现次数小于 k 的字符的数量
            int less = 0;
            while (r < n)
            {
                cnt[s[r] - 'a']++; // 滑动窗口右边界添加次数
                // 次数等于1,代表新加入字符
                if (cnt[s[r] - 'a'] == 1)
                {
                    tot++;
                    less++;
                }
                // 滑动窗口中的所有字符都满足K个以上数量
                if (cnt[s[r] - 'a'] == k)
                {
                    less--;
                }
                // 当滑动窗口中字符种类数大于枚举的字符种类数量时
                // 循环移动左边界,去掉滑动窗口最左边字符
                while (tot > t)
                {
                    cnt[s[l] - 'a']--;
                    // 数量刚好不满足
                    if (cnt[s[l] - 'a'] == k - 1)
                    {
                        less++;
                    }
                    // 没有该字符,则种类数-1,同时less也统计-1
                    if (cnt[s[l] - 'a'] == 0)
                    {
                        tot--;
                        less--;
                    }
                    l++;
                }
                // 滑动窗口中字符都满足数量 >= K
                if (less == 0)
                {
                    ret = max(ret, r - l + 1);
                }
                r++;
            }
        }
        return ret;
    }
};