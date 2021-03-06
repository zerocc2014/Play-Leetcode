/// Source : https://leetcode.com/problems/count-ways-to-make-array-with-product/
/// Author : liuyubobobo
/// Time   : 2021-01-28

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


/// Shieve Prime Numbers and using factorials to calculate combinations
/// Time Complexity: O(q + maxk + maxn + maxk * log(maxk) + q * logk)
/// Space Complexity: O(maxk + maxn)
class Solution {

private:
    const long long MOD = 1e9 + 7;

public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {

        int maxk = 0, maxn = 0;
        for(int i = 0; i < queries.size(); i ++){
            maxk = max(maxk, queries[i][1]);
            maxn = max(maxn, queries[i][0]);
        }

        vector<int> first = shieve(maxk);

        vector<long long> fac(maxk + maxn, 1ll);
        for(int i = 2; i < fac.size(); i ++)
            fac[i] = fac[i - 1] * i % MOD;

        vector<int> ret(queries.size());
        for(int i = 0; i < queries.size(); i ++){
            int n = queries[i][0], k = queries[i][1];

            unordered_map<int, int> d;
            while(k != 1) d[first[k]] ++, k /= first[k];

            long long res = 1ll;
            for(const pair<int, int>& p: d)
                res = res * put(p.second, n, fac) % MOD;
            ret[i] = res;
        }
        return ret;
    }

private:
    // n balls in m boxes, boxes can be empty
    int put(int n, int m, vector<long long>& fac){
        return C(n + m - 1, m - 1, fac);
    }

    int C(int n, int k, vector<long long>& fac){
        return fac[n] * mypow(fac[n - k], MOD - 2) % MOD * mypow(fac[k], MOD - 2) % MOD;
    }

    long long mypow(long long a, int k){

        if(k == 0) return 1ll;
        if(k == 1) return a;

        long long t = mypow(a, k / 2);
        long long res = t * t % MOD;
        if(k % 2) res = res * a % MOD;
        return res;
    }

    vector<int> shieve(int n){

        vector<int> first(n + 1, 0);
        for(int i = 2; i <= n; i ++)
            if(first[i] == 0){
                for(int k = i; k <= n; k += i)
                    first[k] = i;
            }
        return first;
    }
};


void print_vec(const vector<int>& v){
    for(int e: v) cout << e << " "; cout << endl;
}

int main() {

    vector<vector<int>> queries1 = {{2, 6}, {5, 1}, {73, 660}};
    print_vec(Solution().waysToFillArray(queries1));
    // 4 1 50734910

    vector<vector<int>> queries2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    print_vec(Solution().waysToFillArray(queries2));
    // 1 2 3 10 5

    return 0;
}
