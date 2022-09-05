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
//今天周六计划
//完成
// 538. 把二叉搜索树转换为累加树
class LT538Solution
{
public:
    int sum = 0;
    TreeNode *convertBST(TreeNode *root)
    {
        if(!root){
            return nullptr;
        }
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};




int main()
{
    cout << "---Solution Call---" << endl;

    return 0;
}