#include "Util.h"
// 162. 寻找峰值
class LT162Solution
{
public:
    // 首先明白改题目没有重复的值，则一定会又最大值 for找最大值则O(n) 两端要是较大值也行
    //  二分法O(logn)
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size();
        // 辅助函数，输入下标 i，返回一个二元组 (0/1, nums[i])
        // 方便处理 nums[-1] 以及 nums[n] 的边界情况
        auto get = [&](int i) -> pair<int, int>
        {
            if (i == -1 || i == n)
            {
                return {0, 0};
            }
            return {1, nums[i]};
        };

        int left = 0, right = n - 1, ans = -1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (get(mid - 1) < get(mid) && get(mid) > get(mid + 1))
            {
                ans = mid;
                break;
            }
            // 如果 nums[i]<nums[i+1]，那么我们抛弃[l,i] 的范围，在剩余[i+1,r] 的范围内继续随机选取下标
            if (get(mid) < get(mid + 1))
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return ans;
    }
};