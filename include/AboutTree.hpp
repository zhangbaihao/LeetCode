#include "Util.h"

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 94. 二叉树的中序遍历
class LT094Solution
{
public:
    void inorder(TreeNode *root, vector<int> &res)
    {
        if (!root)
        {
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        inorder(root, res);
        return res;
    }
};
// 114. 二叉树展开为链表
class LT114Solution
{
public:
    vector<TreeNode *> q;
    void pre(TreeNode *root)
    {
        if (!root)
            return;
        q.push_back(root);
        pre(root->left);
        pre(root->right);
    }
    void flatten(TreeNode *root)
    {
        pre(root);
        if (q.empty())
            return;
        TreeNode *temp = q[0];
        for (int i = 1; i < q.size(); i++)
        {
            temp->left = nullptr;
            temp->right = q[i];
            temp = q[i];
        }
    }
};
// LT55 二叉树的深度
class LT55Solution
{
public:
    int TreeDepth(TreeNode *pRoot)
    {
        if (!pRoot)
            return 0;
        int lval = TreeDepth(pRoot->left);
        int rval = TreeDepth(pRoot->right);
        return max(lval, rval) + 1;
    }
};
// 96. 不同的二叉搜索树
class LT096Solution
{
    /*
    dp[i] = i个不同的数组成的二叉搜索数的个数
    假设 i = 5
    当根节点等于 1 时 ，其余数字都比1大，只能在右边 dp[i] += dp[4]
    当根节点等于 2 时，左边有一个1比2小，右边有三个比2大的数字 dp[i] += dp[1] * dp[3]
    当根节点等于 3 时，左边有两个数比3小，右边有两个数比3大的数字 dp[i] += dp[2] * dp[2]
    ...
    知道根节点等于5，左边有4个数字比5小，只能放在5的左边,dp[i] += dp[4]
     */
public:
    int numTrees(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        { //以j值为根结点，总dp[i] 左子树只有dp[j-1]种 *右子树dp[i-j]
            for (int j = 1; j <= i; j++)
            {
                int leftNum = dp[j - 1];
                int rightNum = dp[i - j];
                dp[i] += leftNum * rightNum;
            }
        }
        return dp[n];
    }
};
// 98. 验证二叉搜索树
class LT098Solution
{
public:
    bool helper(TreeNode *root, long long lower, long long upper)
    {
        if (!root)
            return true;
        if (root->val <= lower || root->val >= upper)
        {
            return false;
        }
        return helper(root->left, lower, root->val) && helper(root->right, root->val, upper);
    }
    bool isValidBST(TreeNode *root)
    {
        return helper(root, LONG_MIN, LONG_MAX);
    }
};

// 101. 对称二叉树
class LT101Solution
{
public:
    bool isSame(TreeNode *root1, TreeNode *root2)
    {
        if (!root1 && !root2)
            return true;
        if (!root1 || !root2)
            return false;
        return root1->val == root2->val && isSame(root1->left, root2->right) && isSame(root1->right, root2->left);
    }
    bool isSymmetric(TreeNode *pRoot)
    {
        return isSame(pRoot, pRoot);
    }
};

// 102. 二叉树的层序遍历
class LT102Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (!root)
            return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            vector<int> res;
            while (size--)
            {
                TreeNode *temp = q.front();
                q.pop();
                res.emplace_back(temp->val);
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
            ans.emplace_back(res);
        }
        return ans;
    }
};
// 104. 二叉树的最大深度

class LT104Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        int lDepth = maxDepth(root->left);
        int rDepth = maxDepth(root->right);
        return max(lDepth, rDepth) + 1;
    }
};
// 105. 从前序与中序遍历序列构造二叉树
class LT105Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.size() == 0 || inorder.size() == 0)
            return nullptr;
        TreeNode *root = new TreeNode(preorder[0]);
        int mid = distance(inorder.begin(), find(inorder.begin(), inorder.end(), preorder[0]));
        vector<int> preorder_left(preorder.begin() + 1, preorder.begin() + 1 + mid);
        vector<int> preorder_right(preorder.begin() + 1 + mid, preorder.end());
        vector<int> inorder_left(inorder.begin(), inorder.begin() + mid);
        vector<int> inorder_right(inorder.begin() + mid + 1, inorder.end());
        root->left = buildTree(preorder_left, inorder_left);
        root->right = buildTree(preorder_right, inorder_right);
        return root;
    }
};

// 124. 二叉树中的最大路径和
class LT124Solution
{
public:
    int maxSum = INT_MIN;
    int maxGain(TreeNode *node)
    {
        if (!node)
        {
            return 0;
        }
        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);
        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;
        // 更新答案
        maxSum = max(maxSum, priceNewpath);
        // 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }
    int maxPathSum(TreeNode *root)
    {
        maxGain(root);
        return maxSum;
    }
};

// LT77 按之字形顺序打印二叉树
class LT77Solution
{
public:
    vector<vector<int>> Print(TreeNode *pRoot)
    {
        vector<vector<int>> res;
        if (!pRoot)
            return res;
        queue<TreeNode *> q;
        q.push(pRoot);
        int level = 0;
        while (!q.empty())
        {
            vector<int> arr;
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *tmp = q.front();
                q.pop();
                if (!tmp)
                    continue;
                q.push(tmp->left);
                q.push(tmp->right);
                if (level % 2 == 0)
                {
                    arr.push_back(tmp->val);
                }
                else
                {
                    arr.insert(arr.begin(), tmp->val);
                }
            }
            level++;
            if (!arr.empty())
                res.push_back(arr);
        }
        return res;
    }
};

// LT54 二叉搜索树的第k个节点
class LT54Solution
{
public:
    stack<int> q;
    int KthNode(TreeNode *proot, int k)
    {
        // write code here
        if (!proot || k <= 0)
            return -1;
        KthNode(proot->left, k);
        if (q.size() < k)
            q.push(proot->val);
        //这里不加也行，但是没必要
        if (q.size() < k)
            KthNode(proot->right, k);
        if (q.size() == k)
        {
            return q.top();
        }
        else
        {
            return -1;
        }
    }
};

// LT27 二叉树的镜像
class LT27Solution
{
public:
    TreeNode *Mirror(TreeNode *pRoot)
    {
        // write code here
        if (!pRoot)
            return pRoot;
        TreeNode *temp = pRoot->left;
        pRoot->left = Mirror(pRoot->right);
        pRoot->right = Mirror(temp);
        return pRoot;
    }
};

// LT33 二叉搜索树的后序遍历序列
class LT33Solution
{
public:
    //输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
    //如果是则返回 true ,否则返回 false 。假设输入的数组的任意两个数字都互不相同
    // sequence[end] 后续遍历根节点是最后一个结点
    bool Verify(vector<int> sequence, int start, int end)
    {
        if (start >= end)
            return true;
        int k = start;
        //找到第一个比根节点大的结点 从此节点到根节点皆为右子树
        while (k < end && sequence[k] < sequence[end])
        {
            k++;
        }
        for (int i = k; i < end; i++)
        {
            if (sequence[i] < sequence[end])
                return false;
        }
        return Verify(sequence, start, k - 1) && Verify(sequence, k, end - 1);
    }
    bool VerifySquenceOfBST(vector<int> sequence)
    {
        if (sequence.empty())
            return false;
        if (sequence.size() == 1)
            return true;
        return Verify(sequence, 0, sequence.size() - 1);
    }
};
// LT82 二叉树中和为某一值的路径(一)
class LT82Solution
{
public:
    bool hasPathSum(TreeNode *root, int sum)
    {
        // write code here
        if (!root)
            return false;
        sum -= root->val;
        if (!root->left && !root->right && sum == 0)
            return true;
        return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
    }
};
// LT34 二叉树中和为某一值的路径(二)
class LT34Solution
{
public:
    vector<vector<int>> res;
    void FindOnePath(vector<int> temp, TreeNode *root, int expectNumber)
    {
        if (!root)
            return;
        temp.push_back(root->val);
        //这里需要到叶子结点
        if (!root->left && !root->right && expectNumber == root->val)
            res.push_back(temp);
        else
        {
            FindOnePath(temp, root->left, expectNumber - root->val);
            FindOnePath(temp, root->right, expectNumber - root->val);
        }
        temp.pop_back();
    }
    vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
    {
        vector<int> temp;
        FindOnePath(temp, root, expectNumber);
        return res;
    }
};

// LT36 二叉搜索树与双向链表
class LT36Solution
{
public:
    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if (!pRootOfTree)
            return nullptr;
        stack<TreeNode *> st;
        TreeNode *head = nullptr;
        TreeNode *pre = nullptr;
        while (!st.empty() || pRootOfTree)
        {
            //优先访问左子树，其他先存栈
            while (pRootOfTree && pRootOfTree->left)
            {
                st.push(pRootOfTree);
                pRootOfTree = pRootOfTree->left;
            }
            //当前结点左子树 自己 右子树均访问结束，往上走
            if (!pRootOfTree && !st.empty())
            {
                pRootOfTree = st.top();
                st.pop();
            }
            //第一次出栈pre还未赋值
            if (!pre)
            {
                head = pRootOfTree;
            }
            else
            {
                //调整当前结点与上结点的left和right指针关系
                pre->right = pRootOfTree;
                pRootOfTree->left = pre;
            }
            pre = pRootOfTree;
            //访问默认的下个结点
            pRootOfTree = pRootOfTree->right;
        }
        return head;
    }
};
// LT79 判断是不是平衡二叉树
class LT79Solution
{
public:
    map<TreeNode *, int> hs;
    int getDeepth(TreeNode *pRoot)
    {
        if (!pRoot)
            return 0;
        int l = getDeepth(pRoot->left);
        int r = getDeepth(pRoot->right);
        hs[pRoot] = (max(l, r) + 1);
        return hs[pRoot];
    }
    bool isBalanced(TreeNode *pRoot)
    {
        if (!pRoot)
            return true;
        return abs(hs[pRoot->left] - hs[pRoot->right]) <= 1 && isBalanced(pRoot->left) && isBalanced(pRoot->right);
    }
    bool IsBalanced_Solution(TreeNode *pRoot)
    {
        getDeepth(pRoot);
        return isBalanced(pRoot);
    }
};
// LT8 二叉树的下一个结点
struct TreeLinkNode
{
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next; //指向父结点的next指针
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
class LT8Solution
{
public:
    TreeLinkNode *GetNext(TreeLinkNode *pNode)
    {
        if (!pNode)
            return pNode;
        //如果有右子树则，下一个结点一点在右子树上的左下角
        if (pNode->right)
        {
            pNode = pNode->right;
            while (pNode->left)
            {
                pNode = pNode->left;
            }
            return pNode;
        }
        //没有右子树的情况下，如果有父节点
        while (pNode->next)
        {
            TreeLinkNode *root = pNode->next;
            //判断一下当前结点是不是父结点的左子树，是下一个就是父节点
            if (root->left == pNode)
            {
                return root;
            }
            else
            {
                //右子树，则往上移动
                pNode = pNode->next;
            }
        }
        return nullptr;
    }
};

// LT78 把二叉树打印成多行
class LT78Solution
{
public:
    vector<vector<int>> Print(TreeNode *pRoot)
    {
        vector<vector<int>> res;
        if (!pRoot)
            return res;
        queue<TreeNode *> q;
        q.push(pRoot);
        while (!q.empty())
        {
            int size = q.size();
            vector<int> temp;
            while (size--)
            {
                TreeNode *t = q.front();
                q.pop();
                if (!t)
                    continue;
                q.push(t->left);
                q.push(t->right);
                temp.push_back(t->val);
            }
            if (!temp.empty())
                res.push_back(temp);
        }
        return res;
    }
};
// LT37 序列化二叉树
class LT37Solution
{
public:
    string SerializeCore(TreeNode *root)
    {
        if (!root)
            return "#!";
        string str = "";
        str = std::to_string(root->val) + "!";
        str += SerializeCore(root->left);
        str += SerializeCore(root->right);
        return str;
    }
    char *Serialize(TreeNode *root)
    {
        string str = SerializeCore(root);
        char *res = new char[str.length()];
        for (int i = 0; i < str.length(); i++)
            res[i] = str[i];
        return res;
    }
    //{1,2,3,#,#,6,7} 转成二叉树
    TreeNode *DeserializeCore(char *&str)
    {
        if (*str == '#')
        {
            str++;
            return nullptr;
        }

        int num = 0;
        while (*str != '!')
        {
            num = num * 10 + *str - '0';
            str++;
        }
        TreeNode *node = new TreeNode(num);
        node->left = DeserializeCore(++str);
        node->right = DeserializeCore(++str);
        return node;
    }
    TreeNode *Deserialize(char *str)
    {
        return DeserializeCore(str);
    }
};
// 297. 二叉树的序列化与反序列化
class LT297Solution
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (!root)
            return "#!";
        string res = std::to_string(root->val) + "!";
        res += serialize(root->left);
        res += serialize(root->right);
        return res;
    }
    TreeNode *DeserializeCore(string data, int &index)
    {
        if (data[index] == '#')
        {
            index++; //跳过#号
            return nullptr;
        }

        int num = 0;
        bool aNegativeNumber = false;
        while (data[index] != '!')
        {
            if (data[index] == '-')
            {
                aNegativeNumber = true;
            }
            else
            {
                num = num * 10 + data[index] - '0';
            }
            index++;
        }
        if (aNegativeNumber)
            num = -num;
        TreeNode *node = new TreeNode(num);
        //++index 跳过!
        node->left = DeserializeCore(data, ++index);
        node->right = DeserializeCore(data, ++index);
        return node;
    }
    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        int index = 0;
        TreeNode *res = DeserializeCore(data, index);
        return res;
    }
};
// LT84 二叉树中和为某一值的路径(三)
class LT84Solution
{
public:
    int key = 0;
    void dfs(TreeNode *root, int sum)
    {
        if (!root)
            return;
        sum -= root->val;
        if (sum == 0)
            key++;
        dfs(root->left, sum);
        dfs(root->right, sum);
    }
    int FindPath(TreeNode *root, int sum)
    {
        // write code here
        if (!root)
            return key;
        /*找当前结点*/
        dfs(root, sum);
        FindPath(root->left, sum);
        FindPath(root->right, sum);
        return key;
    }
};

// LT86 在二叉树中找到两个节点的最近公共祖先
class LT86Solution
{
public:
    int lowestCommonAncestor(TreeNode *root, int o1, int o2)
    {
        // write code here
        if (root->val == o1)
            return o1;
        else if (root->val == o2)
            return o2;
        queue<TreeNode *> q;
        q.push(root);

        unordered_map<int, int> father;
        map<int, int> depth;
        father[root->val] = root->val;
        int n = 0;
        while (!q.empty())
        {
            int size = q.size();
            n++;
            while (size--)
            {
                TreeNode *temp = q.front();
                q.pop();
                if (temp->left)
                {
                    q.push(temp->left);
                    father[temp->left->val] = temp->val;
                }
                if (temp->right)
                {
                    q.push(temp->right);
                    father[temp->right->val] = temp->val;
                }
                depth[temp->val] = n;
            }
        }
        while (o1 != o2)
        {
            if (depth[o1] > depth[o2])
            {
                o1 = father[o1];
            }
            else if (depth[o1] < depth[o2])
            {
                o2 = father[o2];
            }
            else
            {
                o1 = father[o1];
                o2 = father[o2];
            }
        }
        return o1;
    }
    int lowestCommonAncestor2(TreeNode *root, int o1, int o2)
    {
        // 记录每个节点的父亲
        unordered_map<int, int> f;
        // 记录bfs队列
        queue<TreeNode *> q;
        q.push(root);

        // 找到o1和o2的父节点就可以停止了
        while (!f[o1] || !f[o2])
        {
            TreeNode *cur = q.front();
            q.pop();
            TreeNode *l = cur->left;
            TreeNode *r = cur->right;

            // 如果当前点有左孩子，那么记录下左孩子的父子关系，并且加入队列
            if (l)
                f[l->val] = cur->val, q.push(l);

            // 右侧对称
            if (r)
                f[r->val] = cur->val, q.push(r);
        }

        // path记录root到o1的路径，无序即可
        unordered_set<int> path;
        while (f[o1])
        {
            path.insert(o1);
            o1 = f[o1];
        }

        // 找到o2到root的路径中，第一个跟path有交集的点，即为答案
        while (path.find(o2) == path.end() && o2 != root->val)
        {
            o2 = f[o2];
        }

        return o2;
    }
};
// 236. 二叉树的最近公共祖先
class LT236Solution
{
public:
    unordered_map<int, TreeNode *> fa;
    unordered_map<int, bool> vis;
    void dfs(TreeNode *root)
    {
        if (root->left != nullptr)
        {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr)
        {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        fa[root->val] = nullptr;
        dfs(root);
        while (p != nullptr)
        {
            vis[p->val] = true;
            p = fa[p->val];
        }
        while (q != nullptr)
        {
            if (vis[q->val])
                return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};
// LT68 二叉搜索树的最近公共祖先
class LT68Solution
{
public:
    int lowestCommonAncestor(TreeNode *root, int p, int q)
    {
        while (1)
        {
            if (root->val > p && root->val > q)
            {
                root = root->left;
            }
            else if (root->val < p && root->val < q)
            {
                root = root->right;
            }
            else
            {
                break;
            }
        }
        return root->val;
    }
};
//337. 打家劫舍 III
class LT337Solution
{
public:
    // f[i]偷i结点价值最大 g[i]代表不偷i结点的价值最大
    unordered_map<TreeNode *, int> f, g;
    void dfs(TreeNode *node)
    {
        if (!node)
        {
            return;
        }
        dfs(node->left);
        dfs(node->right);
        //偷f[node] 则左右子树不能偷
        f[node] = node->val + g[node->left] + g[node->right];
        //不偷g[node] 左+右子树可以偷也可以不偷 取最大值和
        g[node] = max(f[node->left], g[node->left]) + max(f[node->right], g[node->right]);
    }

    int rob(TreeNode *root)
    {
        dfs(root);
        return max(f[root], g[root]);
    }
};