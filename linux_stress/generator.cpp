#include <bits/stdc++.h>

// #ifndef ONLINE_JUDGE
//     #include "debug/debug_template.cpp"
// #else
//     #define debug(...)
//     #define debugArr(...)
// #endif

#define ll long long
#define nl "\n"
#define vi vector<int>
#define vvi vector<vector<int>>
#define int long long
#define pii pair<int,int>
#define double long double
#define pb push_back
#define here cout<<"HERE"<<nl;
#define forn(i,a,n) for(int i = a; i < n; i++)
#define print(a) for(auto& e : a) cout << e << " "; cout << nl;
#define all(a) a.begin(),a.end()
#define MOD(a,b) ((a%b)+b)%b
#define yesno(b) cout << ((b)? "YES\n" : "NO\n")
template<typename T> using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
using namespace std;
static mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());


ll rnd(ll L, ll R) {
    uniform_int_distribution<long long> dist(L, R);
    return dist(rng);
}

vector<int> rand_array(int n, int L = 0, int R = 1000) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rnd(L, R);
    return a;
}


void solve(){
    

}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
