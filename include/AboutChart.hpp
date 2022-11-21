#pragma once
#include "Util.h"
// 207. 课程表
class LT207Solution
{
public:
    vector<vector<int>> edges;
    vector<int> indeg;
    //广度优先搜索
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        //先修课程的后续课程如 [0] = {1,2,3} 代表 修课123都需要先修课0
        edges.resize(numCourses);
        //入度 代表该课程有多少个先修课程，后面每学习完一门课程对应更新indeg
        indeg.resize(numCourses);
        for (const auto &info : prerequisites)
        {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
        { //入度0 无先修课程 可以先放在队列学习
            if (indeg[i] == 0)
            {
                q.push(i);
            }
        }
        //修完的课程
        int visited = 0;
        while (!q.empty())
        {
            ++visited;
            int u = q.front();
            q.pop();
            //先修课程的后续课程 依赖关系 v是后续课程
            for (int v : edges[u])
            {
                --indeg[v];
                //没有先修课程了，接下来也可以学习
                if (indeg[v] == 0)
                {
                    q.push(v);
                }
            }
        }
        //修过的课程与所有课程比较 课程表是否合理
        return visited == numCourses;
    }
};
// 210. 课程表 II
class LT210Solution
{
public:
    vector<vector<int>> edges;
    vector<int> indeg;

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<int> ans;
        if (prerequisites.empty())
        {
            for (int i = 0; i < numCourses; i++)
                ans.push_back(i);
            return ans;
        }
        // x[1]是x1[0]...x2的必修课
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (auto &x : prerequisites)
        {
            edges[x[1]].push_back(x[0]);
            ++indeg[x[0]]; // x[0]这门课的必修课数量
        }
        // 广度遍历常用的queue
        queue<int> m_queue;

        for (int i = 0; i < numCourses; ++i)
        { // 入度0 无先修课程 可以先放在队列学习
            if (indeg[i] == 0)
            {
                m_queue.push(i);
            }
        }
        // 修完的课程
        int visited = 0;
        while (!m_queue.empty())
        {
            ++visited;
            int u = m_queue.front();
            m_queue.pop();
            // 记录这个顺序
            ans.push_back(u);
            // 先修课程的后续课程 依赖关系 v是后续课程
            for (int v : edges[u])
            {
                --indeg[v];
                // 没有先修课程了，接下来也可以学习
                if (indeg[v] == 0)
                {
                    m_queue.push(v);
                }
            }
        }
        //学课程不满足所有课程
        if(ans.size() != numCourses)
            return vector<int>();
        else 
            return ans;
    }
};