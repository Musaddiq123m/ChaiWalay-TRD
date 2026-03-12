#include <bits/stdc++.h>
using namespace std;
#define int long long
#define nl "\n"
#define WA cout << "WA" << nl;
#define OK cout << "OK" << nl;

vector<int> read_line_array() {
    string line;
    vector<int> res;
    if(!getline(cin, line)) return res;
    stringstream ss(line);
    long long x;
    while(ss >> x) res.push_back(x);
    return res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
}