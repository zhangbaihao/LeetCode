#include "Util.h"
//名字不是Solution格式 且用了特殊不支持语法的题目
//class NestedIterator
//{
//public:
//    class NestedInteger
//    {
//    public:
//        // Return true if this NestedInteger holds a single integer, rather than a nested list.
//        bool isInteger() const;
//
//        // Return the single integer that this NestedInteger holds, if it holds a single integer
//        // The result is undefined if this NestedInteger holds a nested list
//        int getInteger() const;
//
//        // Return the nested list that this NestedInteger holds, if it holds a nested list
//        // The result is undefined if this NestedInteger holds a single integer
//        const vector<NestedInteger> &getList() const;
//    };
//    //不支持pair<>
//    typedef vector<NestedInteger>::iterator NestedIntergerIterator;
//    // pair 中存储的是列表的当前遍历位置，以及一个尾后迭代器用于判断是否遍历到了列表末尾
//    stack<pair<NestedIntergerIterator, NestedIntergerIterator>> stk;
//
//public:
//    NestedIterator(vector<NestedInteger> &nestedList)
//    {
//        stk.emplace(nestedList.begin(), nestedList.end());
//    }
//
//    int next()
//    {
//        // 由于保证调用 next 之前会调用 hasNext，直接返回栈顶列表的当前元素，然后迭代器指向下一个元素
//        int number = stk.top().first->getInteger();
//        stk.top().first++;
//        return number;
//    }
//
//    bool hasNext()
//    {
//        while (!stk.empty())
//        {
//            auto &p = stk.top();
//            if (p.first == p.second)
//            { // 遍历到当前列表末尾，出栈
//                stk.pop();
//                continue;
//            }
//            if (p.first->isInteger())
//            {
//                return true;
//            }
//            // 若当前元素为列表，则将其入栈，且迭代器指向下一个元素
//            auto &lst = p.first++->getList();
//            stk.emplace(lst.begin(), lst.end());
//        }
//        return false;
//    }
//};

// 380. O(1) 时间插入、删除和获取随机元素
class RandomizedSet
{
public:
    RandomizedSet()
    {
        // srand((unsigned)time(NULL));
    }

    bool insert(int val)
    {
        if (indices.count(val))
        {
            return false;
        }
        int index = nums.size();
        nums.emplace_back(val);
        // 记录value的index
        indices[val] = index;
        return true;
    }

    bool remove(int val)
    {
        if (!indices.count(val))
        {
            return false;
        }
        int index = indices[val];
        // 这步取最后一个元素,替换删除的元素位置,再删除最后一个元素 起到在vector中删除val的作用
        int last = nums.back();
        // 要删除的元素用最后一个元素替换
        nums[index] = last;
        // 更新最后元素的下标为删除的下标
        indices[last] = index;
        // 删除最后一个元素
        nums.pop_back();

        indices.erase(val);
        return true;
    }

    int getRandom()
    {
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }

private:
    vector<int> nums;
    unordered_map<int, int> indices;
};