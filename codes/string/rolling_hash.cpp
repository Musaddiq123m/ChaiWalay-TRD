
const int MODH1 = 1e9 + 7;
const int BASE1 = 911;
const int MODH2 = 1e9 + 9;
const int BASE2 = 3571;

struct RollingHash {
    int n;
    vector<int> H1, P1;
    vector<int> H2, P2;

    RollingHash(const string &s) {
        n = s.size();
        H1.assign(n + 1, 0);
        P1.assign(n + 1, 1);
        H2.assign(n + 1, 0);
        P2.assign(n + 1, 1);

        forn(i, 0, n) {
            int val = s[i] - 'a' + 1;
            H1[i + 1] = (H1[i] * BASE1 + val) % MODH1;
            P1[i + 1] = (P1[i] * BASE1) % MODH1;

            H2[i + 1] = (H2[i] * BASE2 + val) % MODH2;
            P2[i + 1] = (P2[i] * BASE2) % MODH2;
        }
    }

    pair<int, int> get(int l, int r) {
        int x1 = MOD(H1[r] - H1[l] * P1[r - l], MODH1);
        int x2 = MOD(H2[r] - H2[l] * P2[r - l], MODH2);
        return {x1, x2};
    }
    
    uint64_t get_int(int l, int r){
        auto [x1, x2] = get(l,r);           
        uint64_t hi = static_cast<uint32_t>(x1);
        uint64_t lo = static_cast<uint32_t>(x2);
        return (hi << 32) | lo;
    }
};