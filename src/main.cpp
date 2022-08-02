#include <iostream>
#include "AboutList.hpp"
#include "AboutOther.hpp"
#include "AboutSearch.hpp"
#include "AboutDynamicProgramming.hpp"
#include "AboutBack.hpp"
#include "AboutSimulation.hpp"
#include "AboutSort.hpp"
#include "AboutQueueAndStack.hpp"
#include "AboutGreedy.hpp"
#include "AboutTree.hpp"
using namespace std;

// 148. 排序链表
class Solution
{
public:
    vector<int> temp;
    ListNode *sortList(ListNode *head)
    {
        vector<int> temp;
        ListNode *t = head;
        while (t)
        {
            temp.push_back(t->val);
            t = t->next;
        }
        sort(temp.begin(),temp.end());
        t = head;
        for (auto i = temp.begin(); i != temp.end(); i++)
        {
            t->val = *i;
            t = t->next;
        }
        return head;
    }
};

int main()
{
    cout << "---Solution Call---" << endl;
    Solution test;
    return 0;
}