int minRotation(string s){
    // rotate (v. begin () , v. begin ()+ minRotation (v),v. end ());
    int a = 0, N = sz(s);
    s += s;
    forn(b, 0, N) forn(k, 0, N){
        if (a + k == b || s[a + k] < s[b + k]){
            b += max(0, k - 1);
            break;
        }
        if (s[a + k] > s[b + k]){
            a = b;
            break;
        }
    }
    return a;
}
