#include "Util.h"
//1.两数之和
class LT01Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
// 49. 字母异位词分组
class LT049Solution
{
public:
    //输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    //输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
    //字母异位词 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> m;
        for (string str : strs)
        {
            string key = str;
            sort(key.begin(),key.end());
            m[key].emplace_back(str);
        }
        vector<vector<string>> res;
        for(auto i = m.begin();i != m.end();i++){
            res.emplace_back(i->second);
        }
        return res;
    }
};

// 217. 存在重复元素
class LT217Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        set<int> temp;
        for (auto x : nums)
        {
            temp.insert(x);
        }
        if (temp.size() != nums.size())
            return true;
        return false;
    }
};


// 334. 递增的三元子序列
class LT334Solution
{
public:
    bool increasingTriplet(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
        {
            return false;
        }
        // leftMin[i]记录下标i左边最小的值
        vector<int> leftMin(n);
        leftMin[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            leftMin[i] = min(leftMin[i - 1], nums[i]);
        }
        // rightMax[i]记录下标i右边最大的值
        vector<int> rightMax(n);
        rightMax[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            rightMax[i] = max(rightMax[i + 1], nums[i]);
        }
        for (int i = 1; i < n - 1; i++)
        {
            // 当值值符合 比左边最小的大,必右边最大的小
            if (nums[i] > leftMin[i - 1] && nums[i] < rightMax[i + 1])
            {
                return true;
            }
        }
        return false;
    }
};

// 350. 两个数组的交集 II
class LT350Solution
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        map<int, int> m_map;
        for (int i = 0; i < nums1.size(); i++)
        {
            m_map[nums1[i]]++;
        }
        vector<int> res;
        for (int i = 0; i < nums2.size(); i++)
        {
            int temp = nums2[i];
            if (m_map[temp] > 0)
            {
                m_map[temp]--;
                res.push_back(temp);
            }
        }
        return res;
    }
};
