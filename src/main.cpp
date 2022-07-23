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
    Solution test;
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &b;
    test.detectCycle(&a);
    return 0;
}
