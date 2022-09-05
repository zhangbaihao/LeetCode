#include "Util.h"
// 347. 前 K 个高频元素
class LT347Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> m_map;
        for (int i = 0; i < nums.size(); i++)
        {
            m_map[nums[i]]++;
        }
        vector<int> res;
        for (int i = 0; i < k; i++)
        {
            if (m_map.size() > k - i)
            {
                int maxValue = 0;
                int index = 0;
                for (auto it = m_map.begin(); it != m_map.end(); it++)
                {
                    if (it->second > maxValue)
                    {
                        index = it->first;
                        maxValue = it->second;
                    }
                }
                res.push_back(index);
                m_map.erase(index);
            }
            else
            {
                for (auto it = m_map.begin(); it != m_map.end(); it++)
                {
                    res.push_back(it->first);
                }
                return res;
            }
        }
        return res;
    }
    static bool cmp(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second > b.second;
    }
    vector<int> topKFrequent2(vector<int> &nums, int k)
    {
        unordered_map<int, int> m_map;
        for (int i = 0; i < nums.size(); i++)
        {
            m_map[nums[i]]++;
        }
        vector<pair<int, int>> arr;
        for (auto it = m_map.begin(); it != m_map.end(); it++)
        {
            arr.push_back(make_pair(it->first, it->second));
        }
        sort(arr.begin(), arr.end(), cmp);
        vector<int> res;
        auto it = arr.begin();
        for (int i = 0; i < k; i++)
        {
            res.push_back(it->first);
            it++;
        }
        return res;
    }
//用自定义 堆序列 小顶堆
// static bool cmp(pair<int, int> &m, pair<int, int> &n)
// {
//     return m.second > n.second;
// }

// vector<int> topKFrequent2(vector<int> &nums, int k)
// {
//     unordered_map<int, int> occurrences;
//     for (auto &v : nums)
//     {
//         occurrences[v]++;
//     }

//     // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
//     //定义一个小顶堆 其中顺序按照第二个元素该值出现的次数cmp元素，即堆顶一顶是出现次数最小的数
//     priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
//     for (auto &[num, count] : occurrences)
//     {
//         // occurrences.size()》k的情况 够 k 个数了，考虑是把堆顶更换
//         if (q.size() == k)
//         {
//             if (q.top().second < count)
//             {
//                 q.pop();
//                 q.emplace(num, count);
//             }
//         }
//         else
//         {
//             q.emplace(num, count);
//         }
//     }
//     vector<int> ret;
//     while (!q.empty())
//     {
//         ret.emplace_back(q.top().first);
//         q.pop();
//     }
//     return ret;
// }
};