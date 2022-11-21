#pragma once
#include "Util.h"

// 127. 单词接龙(困难)
//map<字串，ID>+ 广度优先搜索 + 优化建图
class LT127Solution
{
public:
    /*输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    输出：5
    解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
    */
    unordered_map<string, int> wordId;
    vector<vector<int>> edge;
    // 结点数 ID
    int nodeNum = 0;
    void addWord(string &word)
    {
        if (!wordId.count(word))
        {
            wordId[word] = nodeNum++;
            edge.emplace_back();
        }
    }

    void addEdge(string &word)
    {
        // 赋予word 一个ID 以及创建一个空的vector 用于记录该word可以转换成的string的ID
        addWord(word);
        int id1 = wordId[word];
        // dot 可以转换成*ot d*t do*
        for (char &it : word)
        {
            char tmp = it;
            it = '*';
            addWord(word);
            int id2 = wordId[word];
            edge[id1].push_back(id2);
            edge[id2].push_back(id1);
            it = tmp;
        }
    }

    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        if (beginWord == endWord)
            return 0;
        // 根据字典构建 wordId 记录每个string ID 以及edge 每个ID有一个vector 记录可以转换的id
        for (string &word : wordList)
        {
            addEdge(word);
        }
        addEdge(beginWord);
        if (!wordId.count(endWord))
        {
            return 0;
        }
        // 用于记录到每个结点时，已经转换的次数
        vector<int> dis(nodeNum, INT_MAX);

        int beginId = wordId[beginWord];
        int endId = wordId[endWord];
        dis[beginId] = 0;

        //
        queue<int> que;
        que.push(beginId);
        while (!que.empty())
        {
            int x = que.front();
            que.pop();
            if (x == endId)
            {
                // hit->*it->
                //    ->hi*->   ->ho*    ->d*t            ->log
                //    ->h*t->hot->*ot->dot->do*->dog->*og->cog
                //                   ->lot           ->d*g
                //
                return dis[endId] / 2 + 1;
            }
            // 查找每个ID自己的vector支持转换的id
            for (int &it : edge[x])
            {
                // 判断是否转换过 没有则记录转化次数,以及记录转换后的ID
                if (dis[it] == INT_MAX)
                {
                    dis[it] = dis[x] + 1;
                    que.push(it);
                }
            }
        }
        return 0;
    }
};