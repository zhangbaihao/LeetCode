#pragma once
#include "Util.h"
// 20. 有效的括号
class LT020Solution
{
public:
    bool isValid(string s)
    {
        stack<char> m;
        int length = s.length();
        for (int i = 0; i < length; ++i)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            {
                m.push(s[i]);
            }
            else if (s[i] == ')')
            {
                if (m.empty() || m.top() != '(')
                {
                    return false;
                }
                else
                {
                    m.pop();
                }
            }
            else if (s[i] == '}')
            {
                if (m.empty() || m.top() != '{')
                {
                    return false;
                }
                else
                {
                    m.pop();
                }
            }
            else if (s[i] == ']')
            {
                if (m.empty() || m.top() != '[')
                {
                    return false;
                }
                else
                {
                    m.pop();
                }
            }
        }
        if (!m.empty())
            return false;
        return true;
    }
};

// LT9 用两个栈实现队列
class LT9Solution
{
public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        int value = 0;
        if (!stack2.empty())
        {
            value = stack2.top();
            stack2.pop();
        }
        else
        {
            while (!stack1.empty())
            {
                int temp = stack1.top();
                stack1.pop();
                stack2.push(temp);
            }
            value = stack2.top();
            stack2.pop();
        }
        return value;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
// LT155. 最小栈
class LT155olution
{
public:
    stack<int> stack1;
    multiset<int> number;
    void push(int value)
    {
        stack1.push(value);
        number.insert(value);
    }
    void pop()
    {
        int value = stack1.top();
        number.erase(number.find(value));
        stack1.pop();
    }
    int top()
    {
        return stack1.top();
    }
    int min()
    {
        return *number.begin();
    }
};
// LT31 栈的压入、弹出序列
class LT31Solution
{
public:
    //[1,2,3,4,5],[4,5,3,2,1] true
    //[1,2,3,4,5],[4,3,5,1,2] false
    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        stack<int> temp;
        int size = pushV.size();
        int i = 0, j = 0;
        while (j < size)
        {
            if (pushV[i] != popV[j])
            {
                if (!temp.empty())
                {
                    if (temp.top() == popV[j])
                    {
                        temp.pop();
                        j++;
                        continue;
                    }
                    else
                    {
                        if (i >= size)
                            return false;
                    }
                }
                temp.push(pushV[i]);
                i++;
            }
            else
            {
                i++;
                j++;
            }
        }
        return true;
    }
};

//输入:"nowcoder. a am I"
//返回值:"I am a nowcoder."
class LT73Solution
{
public:
    string ReverseSentence(string str)
    {
        if (str.empty())
            return str;

        int i = 0;
        int size = str.size();
        while (i < size && str[i] == ' ')
            ++i;
        if (i == size)
            return str;
        istringstream ss(str);
        vector<string> ret;
        string s;
        // 拆分单词
        while (ss >> s)
            ret.push_back(s);
        reverse(ret.begin(), ret.end());
        ostringstream oss;
        // 合并成字符串
        for (int i = 0; i < ret.size() - 1; ++i)
            oss << ret[i] << ' ';
        //返回当前vector容器中末尾元素的引用。
        oss << ret.back();
        return oss.str();
    }
};
// 76. 最小覆盖子串
class LT076Solution
{
public:
    /*输入：s = "ADOBECODEBANC", t = "ABC" 输入： s = "a", t = "aa"
      输出："BANC"                         输出： ""               */
    unordered_map<char, int> window_map, t_map;
    bool check()
    { // 判断窗口中是否全包含 t 中所有字符
        for (const auto &p : t_map)
        {
            if (window_map[p.first] < p.second)
            {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t)
    {
        for (const auto &c : t)
        { // 统计 t 中字符
            ++t_map[c];
        }
        // ansLeft 存储可行窗口的左指针索引，len 为可行窗口的长度
        int len = INT_MAX, left = 0, right = -1, ansLeft = -1;
        int length_s = s.size();
        while (right < length_s)
        {
            if (t_map.find(s[++right]) != t_map.end())
            { // 若右指针移动 1 个单位后增加的字符存在 t 中则增加到 window_map 中
                ++window_map[s[right]];
            }
            while (check() && left <= right)
            { // 当前窗口包含了 t 中全部字符，开始移动左指针
                if (right - left + 1 < len)
                { // 当前窗口比上次的窗口小，记录
                    len = right - left + 1;
                    ansLeft = left;
                }
                if (t_map.find(s[left]) != t_map.end())
                { // t 包含左指针指的字符，更新 window_map
                    --window_map[s[left]];
                }
                ++left; // 左指针移动
            }
        }
        return ansLeft == -1 ? string() : s.substr(ansLeft, len);
    }
};
// 84. 柱状图中最大的矩形
class LT084Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int size = heights.size();
        int maxS = 0;
        int lasth = 0;
        for (int i = 0; i < size; i++)
        {
            //此高度下最大面积
            int h = heights[i];
            if (h != lasth)
                lasth = h;
            else
                continue;
            int left = i, right = i;
            //从左边找边界
            while (--left >= 0)
            {
                if (h > heights[left])
                {
                    break;
                }
            }
            //从右边找
            while (++right < size)
            {
                if (h > heights[right])
                {
                    break;
                }
            }
            maxS = max(maxS, (right - left - 1) * h);
        }
        return maxS;
    }
    //此方法在1方法上优化不需要两重for 采用栈找到left和rigth
    int largestRectangleArea2(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> left(n), right(n);

        //从左往右  依次找每个高度左边 第一个比他小的高度的下标
        stack<int> mono_stack;
        for (int i = 0; i < n; ++i)
        {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
            {
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
            mono_stack.push(i);
        }
        //从右往左 依次找每个高度的右边 第一个比他小的高度的下标
        mono_stack = stack<int>();
        for (int i = n - 1; i >= 0; --i)
        {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
            {
                mono_stack.pop();
            }
            right[i] = (mono_stack.empty() ? n : mono_stack.top());
            mono_stack.push(i);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
    //此方法在2方法少优化 一遍遍历即算出left和rigth数组
    int largestRectangleArea3(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> left(n), right(n, n);

        stack<int> mono_stack;
        //从左往右  依次找每个高度左边 第一个比他小的高度的下标
        for (int i = 0; i < n; ++i)
        {
            //遇到右边第一个比他小的高度
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
            {
                //每个高度的右边 第一个比他小的高度的下标
                right[mono_stack.top()] = i;
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
            mono_stack.push(i);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};
// 85. 最大矩形
class LT085Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int rows = matrix.size();
        if (rows == 0)
            return 0;
        int cols = matrix[0].size();
        vector<vector<int>> left(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (matrix[i][j] == '1')
                {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }
        int maxS = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (matrix[i][j] == '0')
                {
                    continue;
                }
                int width = left[i][j];
                int area = width;
                for (int k = i - 1; k >= 0; k--)
                {
                    width = min(width, left[k][j]);
                    area = max(area, (i - k + 1) * width);
                }
                maxS = max(maxS, area);
            }
        }
        return maxS;
    }
    //与 LT084Solution 一样柱状图解法 算出上下第一个比他小的宽度，down-up-1 = 高度 * 宽度left[i][j]
    int maximalRectangle2(vector<vector<char>> &matrix)
    {
        int m = matrix.size();
        if (m == 0)
        {
            return 0;
        }
        int n = matrix[0].size();
        vector<vector<int>> left(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == '1')
                {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }

        int ret = 0;
        for (int j = 0; j < n; j++)
        { // 对于每一列，使用基于柱状图的方法
            vector<int> up(m, 0), down(m, m);
            stack<int> stk;
            for (int i = 0; i < m; i++)
            {
                //与一遍循环找到  left[i][j]
                //左边第一个比他小的up[]和右边第一个比他小的down[]
                while (!stk.empty() && left[stk.top()][j] >= left[i][j])
                {
                    down[stk.top()] = i;
                    stk.pop();
                }
                up[i] = stk.empty() ? -1 : stk.top();
                stk.push(i);
            }
            for (int i = 0; i < m; i++)
            {
                int height = down[i] - up[i] - 1;
                int area = height * left[i][j];
                ret = max(ret, area);
            }
        }
        return ret;
    }
};
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