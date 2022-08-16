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


int main()
{
    cout << "---Solution Call---" << endl;
    multiset<int> a;
    LT200Solution test;
    vector<vector<char>> grid;
    grid.push_back(vector<char>({'1', '1', '1'}));
    grid.push_back(vector<char>({'0', '1', '0'}));
    grid.push_back(vector<char>({'1', '1', '1'}));
    // grid.push_back(vector<char>({'1', '0', '1', '1', '0', '1', '1'}));
    //  grid.push_back(vector<char>({'1', '1', '0', '0', '0'}));
    //  grid.push_back(vector<char>({'1', '1', '0', '0', '0'}));
    //  grid.push_back(vector<char>({'0', '0', '1', '0', '0'}));
    //  grid.push_back(vector<char>({'0', '0', '0', '1', '1'}));
    test.numIslands(grid);
    return 0;
}