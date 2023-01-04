#include "Util.h"
//16. 最接近的三数之和
class LT016Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < n; ++i)
        {
            int start = i + 1, end = n - 1;
            while (start < end)
            {
                int sum = nums[i] + nums[start] + nums[end];
                if (abs(target - sum) < abs(target - ans))
                {
                    ans = sum;
                }

                if (sum > target)
                {
                    end--;
                }
                else if (sum < target)
                {
                    start++;
                }
                else
                {
                    //合位target则直接返回target
                    return ans;
                }
            }
        }
        return ans;
    }
};
// 18. 四数之和
class LT018Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        vector<vector<int>> res;

        int n = nums.size();
        if (n < 4)
        {
            return res;
        }
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 3; ++i)
        {
            //跳过重复的第一个数字
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
            {
                break;
            }
            if ((long)nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
            {
                continue;
            }
            long temp1 = target - nums[i];
            for (int j = i + 1; j < n - 2; ++j)
            {
                //跳过重复的第二个数字
                if (j > i + 1 && nums[j] == nums[j - 1])
                {
                    continue;
                }

                if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
                {
                    break;
                }
                if ((long)nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
                {
                    continue;
                }
                long temp2 = temp1 - nums[j];
                int left = j + 1;
                int right = n - 1;
                while (left < right)
                {
                    long sum = nums[left] + nums[right];
                    if (sum > temp2)
                    {
                        right--;
                    }
                    else if (sum < temp2)
                    {
                        left++;
                    }
                    else if (sum == temp2)
                    {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1])
                        {
                            left++;
                        }
                        left++;
                        while (left < right && nums[right] == nums[right - 1])
                        {
                            right--;
                        }
                        right--;
                    }
                }
            }
        }
        return res;
    }
};
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

// 149. 直线上最多的点数
class LT149Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        if (n == 1)
            return 1;
        sort(points.begin(), points.end());
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int tmp = 0;
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int dy = y1 - y2, dx = x1 - x2;
                //暴力解法 
                for (auto &p : points)
                {
                    //point1 和 point2的斜率 跟 point1和所有点的斜率比较
                    //dy / dx  == (p[1]-y1)/(p[0]-x1)
                    if (dy * (p[0] - x1) == dx * (p[1] - y1))
                        tmp++;
                }
                ans = max(ans, tmp);
            }
        }
        return ans;
    }
};


// 227. 基本计算器 II
class LT227Solution
{
public:
    int calculate(string s)
    {
        // 记录所有剩下只需要求和的数
        vector<int> stk;
        char preSign = '+';
        int num = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i)
        {
            if (isdigit(s[i]))
            {
                num = num * 10 + int(s[i] - '0');
            }
            // 遇到下一个符号或者结尾，才计算上个符号操作
            // 3-2*2 遇到*，上个是- 则处理为-2入栈,记录符号，等待下个数准备计算
            if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1)
            {
                switch (preSign)
                {
                case '+':
                    stk.push_back(num);
                    break;
                case '-':
                    stk.push_back(-num);
                    break;
                case '*':
                    stk.back() *= num;
                    break;
                default:
                    stk.back() /= num;
                }
                preSign = s[i];
                num = 0;
            }
        }
        // 全部求和
        return accumulate(stk.begin(), stk.end(), 0);
    }
};

// 454. 四数相加 II
class LT454Solution
{
public:
    int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
    {
        // 利用map存AB数组和
        unordered_map<int, int> countAB;
        for (int u : A)
        {
            for (int v : B)
            {
                ++countAB[u + v];
            }
        }
        int ans = 0;
        // map中查找在CD数组中key=-(c+d)的次数,如a+b = 4  c+d = -4->key=4  可以找到
        for (int u : C)
        {
            for (int v : D)
            {
                int key = -(u + v);
                if (countAB.count(key))
                {
                    ans += countAB[key];
                }
            }
        }
        return ans;
    }
};