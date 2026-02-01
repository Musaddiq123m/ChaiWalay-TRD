class SuffixArray {
private:
    string s;
    int n;

public:
    vector<int> sa;   // suffix array
    vector<int> lcp;  // LCP array

    SuffixArray(const string& str) {
        s = str + "$"; 
        n = (int)s.size();
        buildSuffixArray();
        buildLCP();
    }

private:
    void buildSuffixArray() {
        vector<int> p(n), c(n);
        vector<pair<char,int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
            c[p[i]] = c[p[i-1]] + (a[i].first != a[i-1].first);

        int k = 0;
        while ((1 << k) < n) {
            vector<pair<pair<int,int>,int>> v(n);
            for (int i = 0; i < n; i++)
                v[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
            sort(v.begin(), v.end());
            for (int i = 0; i < n; i++) p[i] = v[i].second;

            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++)
                c_new[p[i]] = c_new[p[i-1]] + (v[i].first != v[i-1].first);
            c = c_new;
            k++;
        }
        sa = p;
        sa.erase(sa.begin()); // remove sentinel
    }

    void buildLCP() {
        int sz = (int)sa.size();
        lcp.assign(sz, 0);
        vector<int> rank(n - 1, 0);
        for (int i = 0; i < sz; i++) rank[sa[i]] = i;

        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            if (rank[i] == sz - 1) { k = 0; continue; }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
    }

public:
    // 1) Check if a pattern exists
    bool contains(const string& pat) {
        int m = pat.size(), l = 0, r = (int)sa.size()-1;
        while (l <= r) {
            int mid = (l+r)/2;
            string suf = s.substr(sa[mid], m);
            if (suf == pat) return true;
            if (suf < pat) l = mid + 1;
            else r = mid - 1;
        }
        return false;
    }

    // 2) Count distinct substrings
    long long countDistinctSubstrings() {
        long long total = 0;
        for (int i = 0; i < (int)sa.size(); i++) {
            int len = n - 1 - sa[i]; // exclude sentinel
            int lcp_val = (i == 0 ? 0 : lcp[i-1]);
            total += len - lcp_val;
        }
        return total;
    }

    // 3) Longest repeated substring
    string longestRepeatedSubstring() {
        int maxLen = 0, idx = -1;
        for (int i = 0; i < (int)lcp.size(); i++) {
            if (lcp[i] > maxLen) {
                maxLen = lcp[i];
                idx = i;
            }
        }
        if (maxLen == 0) return ""; // no repeated substring
        return s.substr(sa[idx], maxLen);
    }

    // 4) Count occurrences of a pattern
    int countPatternOccurrences(const string& pat) {
        int m = pat.size();
        auto lower = [&](int l, int r) {
            while (l < r) {
                int mid = (l+r)/2;
                string suf = s.substr(sa[mid], min(m, n - sa[mid]));
                if (suf < pat) l = mid+1;
                else r = mid;
            }
            return l;
        };
        auto upper = [&](int l, int r) {
            while (l < r) {
                int mid = (l+r)/2;
                string suf = s.substr(sa[mid], min(m, n - sa[mid]));
                if (suf <= pat) l = mid+1;
                else r = mid;
            }
            return l;
        };
        int l = lower(0, sa.size());
        int r = upper(0, sa.size());
        return r - l;
    }
};
