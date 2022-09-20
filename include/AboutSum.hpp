#include "Util.h"
// 560. 和为 K 的子数组
class LT560Solution
{
public:
    //超时
    int subarraySum(vector<int> &nums, int k)
    {
        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int sum = 0;
            for (int j = i; j >= 0; j--)
            {
                sum += nums[j];
                if (sum == k)
                    count++;
            }
        }
        return count;
    }
    
    int subarraySum2(vector<int> &nums, int k)
    {
        int count = 0;
        map<int,int> m_map;
        //和为0的数量为1
        m_map[0] = 1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            //查找之前和，如果map有则说明，k=sum-pre_sum不取和为pre_sum 的元素
            int pre_sum = sum-k;
            if(m_map.find(pre_sum) != m_map.end()){
                count += m_map[pre_sum];
            }
            m_map[sum]++;
        }
        return count;
    }
};
