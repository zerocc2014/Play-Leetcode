/// Source : https://leetcode.com/problems/nested-list-weight-sum-ii/
/// Author : liuyubobobo
/// Time   : 2021-01-15

#include <iostream>
#include <vector>

using namespace std;


/// DFS
/// Time Complexity: O(n)
/// Space Complexity: O(h)

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
    public:
        // Constructor initializes an empty nested list.
        NestedInteger();

        // Constructor initializes a single integer.
        NestedInteger(int value);

        // Return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() const;

        // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
        int getInteger() const;

        // Set this NestedInteger to hold a single integer.
        void setInteger(int value);

        // Set this NestedInteger to hold a nested list and adds a nested integer to it.
        void add(const NestedInteger &ni);

        // Return the nested list that this NestedInteger holds, if it holds a nested list
        // The result is undefined if this NestedInteger holds a single integer
        const vector<NestedInteger> &getList() const;
};

class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {

        int depth = get_depth(nestedList);
        return depthSumInverse(nestedList, depth);
    }

private:
    int depthSumInverse(const vector<NestedInteger>& nestedList, int d){

        int res = 0;
        for(const NestedInteger& e: nestedList)
            if(e.isInteger()) res += d * e.getInteger();
            else res += depthSumInverse(e.getList(), d - 1);
        return res;
    }

    int get_depth(const vector<NestedInteger>& nestedList){

        int d = 1;
        for(const NestedInteger& e: nestedList)
            if(!e.isInteger())
                d = max(d, 1 + get_depth(e.getList()));
        return d;
    }
};


int main() {

    return 0;
}
