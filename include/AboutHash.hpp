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