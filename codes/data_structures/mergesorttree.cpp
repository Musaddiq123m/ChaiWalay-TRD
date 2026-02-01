#include<bits/stdc++.h>
using namespace std;

const int N = 1 << 18;  
static vector<int> tree[2 * N];  
class MergeSortTree {
    private:
    int n;

    void build(const vector<int>& arr) {
        for (int i = 0; i < n; i++) {
            tree[N + i] = {arr[i]};
        }
        for (int i = N - 1; i >= 1; i--) {
            int sz = (int)tree[i << 1].size() + (int)tree[i << 1 | 1].size();
            tree[i].resize(sz);
            merge(tree[i << 1].begin(), tree[i << 1].end(),
                  tree[i << 1 | 1].begin(), tree[i << 1 | 1].end(),
                  tree[i].begin());
        }
    }

public:
    MergeSortTree(const vector<int>& arr) {
        n = arr.size();
        build(arr);
    }

    // Query: count of numbers >= x in arr[l..r], inclusive (0-based)
    // for <= change the lower_bound to upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin()
    int query_ge(int l, int r, int x) {
        l += N, r += N;
        int count = 0;
        while (l <= r) {
            if (l & 1) {
                count += tree[l].end() - lower_bound(tree[l].begin(), tree[l].end(), x);
                l++;
            }
            if (!(r & 1)) {
                count += tree[r].end() - lower_bound(tree[r].begin(), tree[r].end(), x);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return count;
    }
    // Query: count of numbers <= x in arr[l..r], inclusive (0-based)
    int query_le(int l, int r, int x) {
        l += N, r += N;
        int count = 0;
        while (l <= r) {
            if (l & 1) {
                count += upper_bound(tree[l].begin(), tree[l].end(), x) - tree[l].begin();
                l++;
            }
            if (!(r & 1)) {
                count += upper_bound(tree[r].begin(), tree[r].end(), x) - tree[r].begin();
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return count;
    }
};