#pragma once
#include "Util.h"

struct ListNode
{
    int val;
    struct ListNode *next;
    ListNode(){
        next = nullptr;
    }
    ListNode(int x) : val(x), next(NULL)
    {
    }
};
void printList(ListNode *head)
{
    ListNode *p = head;
    cout << "List:";
    while (p)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}
// 2.两数相加
class LT002Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = nullptr, *tail = nullptr;
        int carry = 0;
        while (l1 || l2)
        {
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + carry;
            if (!head)
            {
                head = tail = new ListNode(sum % 10);
            }
            else
            {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            if (l1)
            {
                l1 = l1->next;
            }
            if (l2)
            {
                l2 = l2->next;
            }
        }
        if (carry > 0)
        {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};
// 19. 删除链表的倒数第 N 个结点
class LT019Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *fast = head;
        ListNode *slow = head;
        int k = n;
        while (fast && k > 0)
        {
            fast = fast->next;
            k--;
        }
        if (!fast && k != 0)
            return nullptr;
        ListNode *pre = slow;
        while (fast)
        {
            fast = fast->next;
            pre = slow;
            slow = slow->next;
        }
        //如果删除的是头节点
        if (slow == head)
        {
            ListNode *res = slow->next;
            delete slow;
            slow = nullptr;
            return res;
        }
        pre->next = slow->next;
        delete slow;
        slow = nullptr;
        return head;
    }
};
// 21. 合并两个有序链表
class LT021Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
        {
            return l2;
        }
        else if (l2 == nullptr)
        {
            return l1;
        }
        else if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
// 23. 合并K个升序链表
//  输入：lists = [[1,4,5],[1,3,4],[2,6]]
//  输出：[1,1,2,3,4,4,5,6]
//  解释：链表数组如下：
//  [
//    1->4->5,
//    1->3->4,
//    2->6
//  ]
//  将它们合并到一个有序链表中得到。
//  1->1->2->3->4->4->5->6

class LT023Solution
{
public:
    //[[]]
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *head = new ListNode(0);
        ListNode *cur = head;
        //删除所有无效的链表指针
        for (auto iter = lists.begin(); iter != lists.end();)
        {
            if (!*iter)
            {
                iter = lists.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        while (!lists.empty())
        {
            int k = -1;
            int minValue = 10001;
            int n = lists.size();
            ListNode *temp = nullptr;
            for (int i = 0; i < n; i++)
            {
                if (lists[i]->val < minValue)
                {
                    temp = lists[i];
                    minValue = lists[i]->val;
                    k = i;
                }
            }
            if (k >= 0)
            {
                cur->next = temp;
                cur = cur->next;
                lists[k] = lists[k]->next;
                if (!lists[k])
                {
                    lists.erase(lists.begin() + k);
                }
            }
        }
        return head->next;
    }
};

// LT6 从尾到头打印链表
//输入一个链表的头节点，按链表从尾到头的顺序返回每个节点的值
class LT6Solution
{
public:
    vector<int> printListFromTailToHead(ListNode *head)
    {
        vector<int> arr;
        ListNode *c = head;
        while (c)
        {
            arr.push_back(c->val);
            c = c->next;
        }
        reverse(arr.begin(), arr.end());
        return arr;
    }
};

// LT24 反转链表
class LT24Solution
{
public:
    ListNode *ReverseList(ListNode *pHead)
    {
        if (!pHead || !pHead->next)
            return pHead;
        ListNode *a = nullptr;
        ListNode *b = pHead;
        ListNode *c = nullptr;
        while (b)
        {
            c = b->next;
            b->next = a;
            a = b;
            b = c;
        }
        return a;
    }
};
// LT25 合并两个排序的链表
class LT25Solution
{
public:
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *pHead3 = new ListNode(-1);
        ListNode *c = pHead3;
        while (pHead1 && pHead2)
        {
            if (pHead1->val < pHead2->val)
            {
                c->next = pHead1;
                pHead1 = pHead1->next;
            }
            else
            {
                c->next = pHead2;
                pHead2 = pHead2->next;
            }
            c = c->next;
        }
        c->next = pHead1 ? pHead1 : pHead2;
        return pHead3->next;
    }
};
// 160. 相交链表
class LT160Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *a1 = headA;
        ListNode *b1 = headB;
        bool flaga = false;
        bool flagb = false;
        while (a1 && b1)
        {
            if (a1 == b1)
                return a1;
            if (!flaga && !a1->next)
            {
                a1 = headB;
                flaga = true;
            }
            else
            {
                a1 = a1->next;
            }
            if (!flagb && !b1->next)
            {
                b1 = headA;
                flagb = true;
            }
            else
            {
                a1 = a1->next;
            }
        }
        return nullptr;
    }
};
// 141. 环形链表
class LT141Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (!head)
            return false;
        ListNode *fast = head->next;
        ListNode *slow = head;
        while (fast && fast->next && fast->next->next)
        {
            if (fast == slow)
                return true;
            fast = fast->next->next;
            slow = slow->next;
        }
        return false;
    }
};
// 142. 环形链表 II
class LT142Solution
{
public:
    ListNode *detectCycle2(ListNode *head)
    {
        unordered_set<ListNode *> seen;
        while (head != nullptr)
        {
            if (seen.count(head))
            {
                return head;
            }
            seen.insert(head);
            head = head->next;
        }
        return nullptr;
    }
    //设 slow 走了x 则fast走了 2x 则一圈长度等于2x-x=n
    // fast与slow相遇点到环入口点的距离 等于 从原点走到环入口的距离
    ListNode *detectCycle(ListNode *head)
    {
        if (!head || !head->next || !head->next->next)
            return nullptr;
        ListNode *slow = head->next;
        ListNode *fast = head->next->next;
        while (fast != slow)
        {
            if (fast->next == nullptr || fast->next->next == nullptr)
                return nullptr;
            slow = slow->next;
            fast = fast->next->next;
        }
        //这里fast肯定等于slow
        fast = head;
        while (fast != slow)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
// 146. LRU 缓存
class LRUCache
{
    struct CLinkedHashMap
    {
        int key, value;
        CLinkedHashMap *prev;
        CLinkedHashMap *next;
        CLinkedHashMap() : key(0), value(0), prev(nullptr), next(nullptr) {}
        CLinkedHashMap(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
    };

private:
    unordered_map<int, CLinkedHashMap *> cache;
    CLinkedHashMap *head;
    CLinkedHashMap *tail;
    int size;
    int capacity;
    void moveToHead(CLinkedHashMap *node)
    {
        if (node->next)
            node->next->prev = node->prev;

        if (node->prev)
            node->prev->next = node->next;

        head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
    }

public:
    LRUCache(int capacity) : capacity(capacity), size(0)
    {
        head = new CLinkedHashMap();
        tail = new CLinkedHashMap();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (cache.count(key) == 0)
        {
            return -1;
        }
        int value = cache[key]->value;
        moveToHead(cache[key]);
        return value;
    }

    void put(int key, int value)
    {
        if (!cache.count(key))
        { //容量未满时，添加新的
            if (size < capacity)
            {
                CLinkedHashMap *node = new CLinkedHashMap(key, value);
                moveToHead(node);
                size++;
                cache.insert(make_pair(key, node));
            }
            else
            {
                CLinkedHashMap *node = tail->prev;
                cache.erase(node->key);
                cache.insert(make_pair(key, node));
                node->key = key;
                node->value = value;
                moveToHead(node);
            }
        }
        else
        {
            //有对应key值 更新value 并且移动到链表头既可以
            CLinkedHashMap *node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
};

// 148. 排序链表
class LT148Solution
{
public:
    ListNode *sortList(ListNode *head)
    {
        return sortList(head, nullptr);
    }
    ListNode *sortList(ListNode *head, ListNode *tail)
    {
        if (!head)
        {
            return head;
        }
        if (head->next == tail)
        {
            head->next = nullptr;
            return head;
        }
        ListNode *slow = head, *fast = head;
        while (fast != tail)
        {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail)
            {
                fast = fast->next;
            }
        }
        ListNode *mid = slow;
        return merge(sortList(head, mid), sortList(mid, tail));
    }

    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        ListNode *dummyHead = new ListNode(0);
        ListNode *temp = dummyHead, *temp1 = head1, *temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr)
        {
            if (temp1->val <= temp2->val)
            {
                temp->next = temp1;
                temp1 = temp1->next;
            }
            else
            {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr)
        {
            temp->next = temp1;
        }
        else if (temp2 != nullptr)
        {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
    //方法二
    vector<int> temp;
    ListNode *sortList2(ListNode *head)
    {
        vector<int> temp;
        ListNode *t = head;
        while (t)
        {
            temp.push_back(t->val);
            t = t->next;
        }
        sort(temp.begin(), temp.end());
        t = head;
        for (auto i = temp.begin(); i != temp.end(); i++)
        {
            t->val = *i;
            t = t->next;
        }
        return head;
    }
};

class LT23Solution
{
public:
    ListNode *EntryNodeOfLoop(ListNode *pHead)
    {
        unordered_set<ListNode *> st;
        while (pHead)
        {
            if (st.find(pHead) == st.end())
            {
                st.insert(pHead);
                pHead = pHead->next;
            }
            else
            {
                return pHead;
            }
        }
        return nullptr;
    }

    ListNode *EntryNodeOfLoop2(ListNode *pHead)
    {
        if (!pHead->next || !pHead->next->next)
            return nullptr;
        ListNode *slow = pHead->next;
        ListNode *fast = pHead->next->next;

        while (fast)
        {
            if (fast->next && fast->next->next)
            {
                if (fast == slow)
                {
                    fast = pHead;
                    while (fast != slow)
                    {
                        fast = fast->next;
                        slow = slow->next;
                    }
                    return fast;
                }
            }
            fast = fast->next->next;
            slow = slow->next;
        }
        return nullptr;
    }
};
// LT22 链表中倒数最后k个结点
class LT22Solution
{
public:
    ListNode *FindKthToTail(ListNode *pHead, int k)
    {
        // write code here
        ListNode *fast = pHead;
        while (fast && k--)
            fast = fast->next; // 移动右侧指针造成 k 的距离差
                               // k的大小大于链表长度
        if (k > 0)
            return nullptr; // 此时说明 k 比链表长度长

        ListNode *slow = pHead;
        while (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

struct RandomListNode
{
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL){}
};
// LT35 复杂链表的复制
class LT35Solution
{
public:
    //先建一个二合一链表 old->new->old2->new2->..... oldEnd->newEnd->nullptr
    //再拆分链表new出来
    RandomListNode *Clone(RandomListNode *pHead)
    {
        if (!pHead)
            return pHead; // 为空则返回
        RandomListNode *cur = pHead;
        while (cur)
        { //拷贝节点
            RandomListNode *tmp = new RandomListNode(cur->label);
            tmp->next = cur->next;
            cur->next = tmp;
            cur = tmp->next;
        }

        RandomListNode *old = pHead, *clone = pHead->next;
        RandomListNode *newpHead = pHead->next;
        //给新链表建立random指向
        while (old)
        {
            clone->random = old->random == NULL ? NULL : old->random->next; // 处理拷贝节点的随机指针
            if (old->next)
                old = old->next->next; // 注意特判空指针
            if (clone->next)
                clone = clone->next->next;
        }
        //拆分链表
        old = pHead, clone = pHead->next;
        while (old)
        {
            if (old->next)
                old->next = old->next->next;
            if (clone->next)
                clone->next = clone->next->next;
            old = old->next;
            clone = clone->next;
        }

        return newpHead;
    }
    RandomListNode *Clone2(RandomListNode *pHead)
    {
        if (!pHead || pHead->random == pHead)
            return pHead;
        RandomListNode *pHead2 = new RandomListNode(0);
        RandomListNode *p1 = pHead;
        RandomListNode *p2 = pHead2;
        //使用一个unordered_map存储new的链表中val值对应的结点
        unordered_map<int, RandomListNode *> search;
        while (p1)
        {
            p2->next = new RandomListNode(p1->label);
            p2 = p2->next;
            p1 = p1->next;
            search[p2->label] = p2;
        }
        p1 = pHead;
        p2 = pHead2->next;
        while (p2)
        {
            //查询p1链表 random 指向的值的对p2中的结点
            if (p1->random)
                p2->random = search[p1->random->label];
            p1 = p1->next;
            p2 = p2->next;
        }
        return pHead2->next;
    }
};

// LT76 删除链表中重复的结点
class LT76Solution
{
public:
    /*在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。
    例如，链表 1->2->3->3->4->4->5  处理后为 1->2->5*/
    ListNode *deleteDuplication(ListNode *pHead)
    {
        //空链表
        if (pHead == NULL)
            return NULL;
        ListNode *res = new ListNode(0);
        //在链表前加一个表头
        res->next = pHead;
        ListNode *cur = res;
        while (cur->next != NULL && cur->next->next != NULL)
        {
            //遇到相邻两个节点值相同
            if (cur->next->val == cur->next->next->val)
            {
                int temp = cur->next->val;
                //将所有相同的都跳过
                while (cur->next != NULL && cur->next->val == temp)
                    cur->next = cur->next->next;
            }
            else
                cur = cur->next;
        }
        //返回时去掉表头
        return res->next;
    }
};
// LT18 删除链表的节点
class LT18Solution
{
public:
    ListNode *deleteNode(ListNode *head, int val)
    {
        // write code here
        ListNode *p = head;
        ListNode *pre = nullptr;
        if (head->val == val)
            return head->next;
        while (p)
        {
            if (p->val == val)
            {
                pre->next = p->next;
                p = pre->next;
                break;
            }
            else
            {
                pre = p;
                p = p->next;
            }
        }
        return head;
    }
};
// 206. 反转链表
class LT206Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        ListNode *new_head = new ListNode(-1);
        ListNode *cur = new_head;
        ListNode *a = head;
        while (a)
        {
            ListNode *next = a->next;
            a->next = cur->next;
            cur->next = a;
            a = next;
        }
        return new_head->next;
    }
};
// 287. 寻找重复数
class LT287Solution
{
public:
    //有环
    int findDuplicate(vector<int> &nums)
    {
        int slow = 0, fast = 0;
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
    unordered_map<int, int> m_map;
    int findDuplicate2(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (m_map.count(nums[i]))
            {
                return nums[i];
            }
            else
            {
                m_map[nums[i]]++;
            }
        }
        return 0;
    }
};