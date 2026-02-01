
const int mod = 1000000007;
struct mint {
    ll x;
    mint() : x(0) {}
    mint(ll x) : x((x%mod+mod)%mod) {}
    mint& fix() { x = (x%mod+mod)%mod; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint& operator+=(const mint& a) { if ((x+=a.x)>=mod) x-=mod; return *this; }
    mint& operator-=(const mint& a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this; }
    mint& operator*=(const mint& a) { (x*=a.x)%=mod; return *this; }

    mint operator+(const mint& a) const { return mint(*this) += a; }
    mint operator-(const mint& a) const { return mint(*this) -= a; }
    mint operator*(const mint& a) const { return mint(*this) *= a; }
    bool operator<(const mint& a) const { return x < a.x; }
    bool operator==(const mint& a) const { return x == a.x; }
    mint pow(ll e) const {
        mint r = 1, b = *this;
        while(e){
            if(e & 1) r *= b;
            b *= b;
            e >>= 1;
        }
        return r;
    }
    mint inv() const {
        return pow(mod - 2);
    }
    mint operator/(const mint& a) const {
        return *this * a.inv();
    }
    mint& operator/=(const mint& a) {
        return *this = *this / a;
    }
};
istream& operator>>(istream& i, mint& a) { i >> a.x; return i; }
ostream& operator<<(ostream& o, const mint& a) { o << a.x; return o; }
typedef vector<mint> vm;