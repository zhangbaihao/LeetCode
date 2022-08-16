#include "Util.h"
// 15. 三数之和
class LT015Solution
{
public:
    /*输入：nums = [-1,0,1,2,-1,-4] 输出：[[-1,-1,2],[-1,0,1]]*/
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3)
            return {};

        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        // i,j,k 分别表示第一第二第三个数 其中j+k == -i 则满足i+j+k = 0
        for (int i = 0; i < n; i++)
        {
            //第一个数同样的只取一次
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            int k = n - 1;
            int target = -nums[i];
            for (int j = i + 1; j < n; j++)
            {
                //第二个数 同样的只取一次
                if (j > i + 1 && nums[j] == nums[j - 1])
                {
                    continue;
                }
                // j+k 偏大
                while (j < k && target < nums[j] + nums[k])
                {
                    k--;
                }
                if (j == k)
                    break;
                if (target == nums[j] + nums[k])
                {
                    res.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
        return res;
    }
};

// 31. 下一个排列
class LT031Solution
{
public:
    //  123->132->213->231->312->321->123
    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size();
        int i = n - 2;
        //找到第一个相临的，后面比前面大的数，
        while (i >= 0 && nums[i] >= nums[i + 1])
        {
            i--;
        }
        if (i >= 0)
        {
            //从后往前找到第一个比nums[i]大的数，与之交换
            for (int j = n - 1; j >= 0; j--)
            {
                if (nums[j] > nums[i])
                {
                    swap(nums[i], nums[j]);
                    break;
                }
            }
        }
        //其中这个i后面的都是num[i]>=num[i]+1
        reverse(nums.begin() + i + 1, nums.end());
    }
};
// 33. 搜索旋转排序数组
class LT033Solution
{
public:
    // nums = [4,5,6,7,0,1,2], target = 0
    //暴力 O(n)
    int search(vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == target)
                return i;
        }
        return -1;
    }
    //二分 O(logn)
    int search2(vector<int> &nums, int target)
    {
        int n = (int)nums.size();
        if (!n)
        {
            return -1;
        }
        if (n == 1)
        {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[0] <= nums[mid])
            {
                if (nums[0] <= target && target < nums[mid])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            else
            {
                if (nums[mid] < target && target <= nums[n - 1])
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};

// 56. 合并区间
class LT056Solution
{
public:
    /*输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
    输出：[[1,6],[8,10],[15,18]]
    解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6]*/
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < intervals.size(); i++)
        {
            int start = *intervals[i].begin();
            int end = *(intervals[i].end() - 1);
            for (int j = i + 1; j < intervals.size(); j++)
            {
                int end2 = *(intervals[j].end() - 1);
                if (end >= *intervals[j].begin())
                {
                    i = j;
                    end = max(end, end2);
                }
                else
                {
                    break;
                }
            }
            res.emplace_back(vector<int>{start, end});
        }
        return res;
    }
};
// 75. 颜色分类
class LT075Solution
{
public:
    // 输入：nums = [2,0,2,1,1,0]
    // 输出：[0,0,1,1,2,2]
    //不能用sort 且O(n) 解决
    void sortColors(vector<int> &nums)
    {
        int n = nums.size();
        int p0 = 0, p1 = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] == 1)
            {
                swap(nums[i], nums[p1]);
                ++p1;
            }
            else if (nums[i] == 0)
            {
                swap(nums[i], nums[p0]);
                if (p0 < p1)
                {
                    //原本P0位置一定为1，被交换到后面去了需要交换回来
                    swap(nums[i], nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};
// LT3 数组中重复的数字
class LT3Solution
{
public:
    //[2,3,1,0,2,5,3] 2或者3
    int duplicate(vector<int> &numbers)
    {
        // write code here
        if (numbers.empty())
            return -1;
        int num = -1;
        sort(numbers.begin(), numbers.end());
        int size = numbers.size();
        for (int i = 0; i < size - 1; i++)
        {
            if (numbers[i] == numbers[i + 1])
            {
                num = numbers[i];
                return num;
            }
        }
        return num;
    }
    int duplicate2(vector<int> &numbers)
    {
        if (numbers.empty())
            return -1;
        map<int, int> m;
        int size = numbers.size();
        int k1 = size - 1 / 2;
        int k2 = size - 1 / 2 + 1;
        for (int i = 0, j = size - 1; i < size && i < j; i++, j--)
        {
            m[numbers[i]]++;
            m[numbers[j]]++;
            if (m[numbers[i]] > 1)
                return numbers[i];
            if (m[numbers[j]] > 1)
                return numbers[j];
            if (k1 > i && k2 < j)
            {
                m[numbers[k1]]++;
                m[numbers[k2]]++;
                if (m[numbers[k1]] > 1)
                    return numbers[k1];
                if (m[numbers[k2]] > 1)
                    return numbers[k2];
                k1--;
                k2++;
            }
        }
        return -1;
    }
};
// 128. 最长连续序列
class LT128Solution
{
public:
    //输入：nums = [0,3,7,2,5,8,4,6,0,1] 输出：9 0-8 O(n)
    //暴力解法
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.empty())
        {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int in = nums[0];
        int count = 1;
        int res = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            if (in + 1 == nums[i])
            {
                count++;
            }
            else if (in == nums[i])
            {
            }
            else
            {
                count = 1;
            }
            in = nums[i];
            res = max(count, res);
        }
        return res;
    }
    //利用unordered_set 去重 且可以快速计算每个元素的个数
    int longestConsecutive2(vector<int> &nums)
    {
        unordered_set<int> num_set;
        for (const int &num : nums)
        {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int &num : num_set)
        {   // 跳过3 7 4 5 6  4567的计算
            if (!num_set.count(num - 1))
            {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1))
                {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return longestStreak;
    }
};
//238. 除自身以外数组的乘积
class LT238Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> B(n, 1);
        for (int i = 1; i < n; i++)
        {
            B[i] = B[i - 1] * nums[i - 1];
        }
        int temp = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            B[i] *= temp;
            temp *= nums[i];
        }
        return B;
    }
};
// LT51 数组中的逆序对
/*
描述
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。
即输出P mod 1000000007
数组中所有数字的值满足 val≤1000000
要求：空间复杂度 O(n)，时间复杂度 O(nlogn)
输入描述：题目保证输入的数组中没有的相同的数字
*/
class LT51sSolution
{
public:
    //[1,2,3,4,5,6,7,0]
    // 7
    int InversePairs(vector<int> data)
    {
        int size = data.size();
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = size - 1; j > i; j--)
            {
                if (data[i] > data[j])
                {
                    count++;
                }
            }
        }
        count = count % 1000000007;
        return count;
    }
    int mod = 1000000007;
    int mergeSort(int left, int right, vector<int> &data, vector<int> &temp)
    {
        //停止划分
        if (left >= right)
            return 0;
        //取中间
        int mid = (left + right) / 2;
        //左右划分合并
        int res = mergeSort(left, mid, data, temp) + mergeSort(mid + 1, right, data, temp);
        //防止溢出
        res %= mod;
        int i = left, j = mid + 1;
        for (int k = left; k <= right; k++)
            temp[k] = data[k];
        for (int k = left; k <= right; k++)
        {
            // mid左边已经全部排进data，只剩下右边，且不会再出现逆序对
            if (i == mid + 1)
                data[k] = temp[j++];
            else if (j == right + 1 || temp[i] <= temp[j])
                data[k] = temp[i++];
            //左边temp[i]>temp[j]则区间[i]-[mid]都比右边[j]大,，答案增加
            else
            {
                data[k] = temp[j++];
                //统计逆序对
                res += mid - i + 1;
            }
        }
        return res % mod;
    }
    int InversePairs2(vector<int> data)
    {
        int n = data.size();
        vector<int> res(n);
        return mergeSort(0, n - 1, data, res);
    }
};
// LT40 最小的K个数
/*描述
给定一个长度为 n 的可能有重复值的数组，找出其中不去重的最小的 k 个数。
例如数组元素是4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4(任意顺序皆可)。
数据范围：0≤k,n≤10000，数组中每个数的大小 0≤val≤1000
要求：空间复杂度 O(n) ，时间复杂度 O(nlogn)*/
class LT40Solution
{
public:
    //[4,5,1,6,2,7,3,8],4
    // 1 2 3 4 返回最小的4个数即可，返回[1,3,2,4]也可以
    //[1] 0 返回[]即可
    //暴力解法排序后 for前面k个数
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {
        vector<int> result;
        if (k == 0)
            return result;
        sort(input.begin(), input.end());
        for (int i = 0; i < k; i++)
        {
            result.push_back(input[i]);
        }
        return result;
    }
    vector<int> GetLeastNumbers_Solution2(vector<int> input, int k)
    {
        vector<int> res;
        //排除特殊情况
        if (k == 0 || input.size() == 0)
            return res;
        //优先队列（大根堆），只要限制堆的大小为k，那么堆顶就是k个数字的中最大值，
        //如果需要替换，将这个最大值拿出，加入新的元素就好了。
        priority_queue<int> q;
        //构建一个k个大小的堆
        for (int i = 0; i < k; i++)
            q.push(input[i]);
        for (int i = k; i < input.size(); i++)
        {
            //较小元素入堆
            if (q.top() > input[i])
            {
                q.pop();
                q.push(input[i]);
            }
        }
        //堆中元素取出入vector
        for (int i = 0; i < k; i++)
        {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};
// LT41 数据流中的中位数
/*如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。
数据范围：数据流中数个数满足 1≤n≤1000  ，大小满足1≤val≤1000
进阶： 空间复杂度 O(n)， 时间复杂度 O(nlogn) */
//[5,2,3,4,1,6,7,0,8]
//返回值："5.00 3.50 3.00 3.50 3.00 3.50 4.00 3.50 4.00 "
//说明：数据流里面不断吐出的是5,2,3...,则得到的平均数分别为5,(5+2)/2,3...
class LT41Solution
{
public:
    //[5,2,3,4,1,6,7,0,8]
    vector<int> datas;
    void Insert(int num)
    {
        int size = datas.size();
        if (size > 0 && num >= datas[size - 1])
        {
            datas.push_back(num);
            return;
        }
        else if (size == 0)
        {
            datas.push_back(num);
            return;
        }

        for (int i = 0; i < size; i++)
        {
            if (datas[i] > num)
            {
                datas.insert(datas.begin() + i, num);
                return;
            }
        }
    }

    double GetMedian()
    {
        int size = datas.size();
        int index = size / 2;
        if (size % 2 == 0)
        {
            return (datas[index] + datas[index - 1]) / 2.0;
        }
        else
        {
            return datas[index];
        }
    }
};

class LT004Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int size1 = nums1.size();
        int size2 = nums2.size();
        int size = size1 + size2;
        if (size == 0)
            return 0;
        int index = size / 2;
        int i, j = 0;
        vector<int> temp;
        int temp_size = 0;
        while (temp_size < index + 1)
        {
            if (i < size1 && (j >= size2 || nums1[i] <= nums2[j]))
            {
                temp.push_back(nums1[i]);
                i++;
            }
            else if (j < size2 && (i >= size1 || nums1[i] > nums2[j]))
            {
                temp.push_back(nums2[j]);
                j++;
            }
            temp_size = temp.size();
        }
        if (size % 2 == 1)
        {
            cout << temp[index]; //这里注释或者去掉会出错，leetcode真的有毛病
            return temp[index];
        }
        else
        {
            return (temp[index] + temp[index - 1]) / 2.0;
        }
    }
};
//堆排序
class HeapSortSolution
{
    //对有一定顺序的堆，当前第i个结点取根左右的最大值（这个操作称heapfiy）
    void heapify(vector<int> &nums, int n, int i)
    {
        int l = i * 2 + 1, r = i * 2 + 2;
        int max = i;
        if (l < n && nums[l] > nums[max])
            max = l;
        if (r < n && nums[r] > nums[max])
            max = r;
        if (max != i)
        {
            swap(nums[max], nums[i]);
            //因为交换了，还需要向下调整
            heapify(nums, n, max);
        }
    }
    //建立大根堆
    void heapify_build(vector<int> &nums, int n)
    {
        //由最后一个结点下标是n-1，parent = (i-1)/2
        //从最后一个结点的 倒数第二层结点开始，对每个结点进行heapify操作，然后向上走
        int temp = (n - 2) / 2;
        for (int i = temp; i >= 0; i--)
            heapify(nums, n, i);
        for (int i = 0; i < nums.size(); i++)
            cout << nums[i] << " ";
        cout << endl;
    }
    //数组 总共有n个结点
    void heapify_sort(vector<int> &nums, int n)
    {
        //建立大根堆
        heapify_build(nums, n);
        //每次交换最后一个结点和根节点（最大值），
        //对交换后的根节点继续进行heapify（此时堆的最后一位是最大值，因此不用管他，n变为n-1）
        for (int i = 0; i < n; i++)
        {
            swap(nums.front(), nums[n - i - 1]);
            heapify(nums, n - i - 1, 0);
        }
    }
};
