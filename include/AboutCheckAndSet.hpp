﻿#include "Util.h"
/*
    vector<vector<string>> equations;
    equations.push_back(vector<string>({"x1", "x2"}));
    equations.push_back(vector<string>({"x2", "x3"}));
    equations.push_back(vector<string>({"x3", "x4"}));
    equations.push_back(vector<string>({"x4", "x5"}));
    vector<double> values;
    values.push_back(3.0);
    values.push_back(4.0);
    values.push_back(5.0);
    values.push_back(6.0);
    vector<vector<string>> queries;
    queries.push_back(vector<string>({"x1", "x5"}));
    test.calcEquation(equations, values, queries);
*/
class UnionFind
{
private:
    vector<int> parent;    // 存放父节点
    vector<double> weight; // 指向父节点的权值

public:
    UnionFind(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            parent.push_back(i);
            weight.push_back(1.0); // 权重初始化为1
        }
    }
    // 路径压缩。返回根节点id
    int find(int x)
    {
        // 递归寻找根节点，更新该点到根的权重为该点父节点到根的权重
        if (x != parent[x])
        {
            //保存原来的父节点
            int origin = parent[x];
            //利用递归栈的特性 一直找到根节点 后进先出
             parent[x] = find(parent[x]);
            //更新权值
            weight[x] *= weight[origin];
        }
        return parent[x];
    }
    // 返回除法结果。如果两个值不存在则-1
    double isConected(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        // 如果两个值有共同的根也就是可以计算，则算结果。否则不在同一个并查集，-1
        if (rootX == rootY)
        {
            return weight[x] / weight[y];
        }
        else
        {
            return -1.00000;
        }
    }
    void myunion(int x, int y, double value)
    {
        // 分别找到二者的根节点
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY)
        {
            return; // 二者已经指向同一个根节点
        }
        // 令分子指向分母的根节点，权重为分母到根的权重*分母除分子的值/分子到根的权重。一开始都是1
        parent[rootX] = rootY;
        weight[rootX] = weight[y] * value / weight[x];
    }
};
//399. 除法求值
class LT399Solution
{
public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        // 初始化并查集
        int equationsSize = equations.size();
        UnionFind unionFind(2 * equationsSize);
        // 第 1 步：预处理，将变量的值与 id 进行映射
        map<string, int> hashMap;
        int id = 0;
        for (int i = 0; i < equationsSize; ++i)
        {
            //每一个分子，分母，映射独立的值为id
            vector<string> equation = equations[i];
            string var1 = equation[0];
            string var2 = equation[1];
            if (!hashMap.count(var1))
            {
                hashMap[var1] = id;
                ++id;
            }
            if (!hashMap.count(var2))
            {
                hashMap[var2] = id;
                ++id;
            }
            // 把分子分母用有向边连起来
            unionFind.myunion(hashMap[var1], hashMap[var2], values[i]);
        }
        // 第 2 步：做查询[a,c] [b,a]
        int queriesSize = queries.size();
        vector<double> res(queriesSize, -1.00000);
        for (int i = 0; i < queriesSize; ++i)
        {
            string var1 = queries[i][0];
            string var2 = queries[i][1];
            int id1, id2;
            // 如果两个值有至少一个不在equations中，结果为-1，否则做除法
            if (hashMap.count(var1) && hashMap.count(var2))
            {
                id1 = hashMap[var1];
                id2 = hashMap[var2];
                res[i] = unionFind.isConected(id1, id2);
            }
        }
        return res;
    }
};