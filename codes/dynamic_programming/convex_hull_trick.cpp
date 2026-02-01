// Usage : CHT cht ; cht . add (m, b); cht . get (x); ( Max query )
using ll = long long;
static constexpr ll is_query = -(1LL < < 62);
struct Line{
    ll m, b;
    mutable function<const Line *()> succ;
    bool operator<(Line const &o) const{
        if (o.b != is_query)
            return m < o.m;
        const Line *s = succ();
        if (!s)
            return false;
        ll x = o.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct CHT : multiset<Line>{
    bool bad(iterator y){
        auto z = next(y), x = (y == begin() ? end() : prev(y));
        if (z == end())
            return x != end() && y->m == x->m && y->b <= x->b;
        if (x == end())
            return y->m == z->m && y->b <= z->b;
        long double v1 = (long double)(x->b - y->b) / (y->m - x->m);
        long double v2 = (long double)(y->b - z->b) / (z->m - y->m);
        return v1 >= v2;
    }
    void add(ll m, ll b){
        auto it = insert({m, b, {}});
        it->succ = [=]
        { return next(it) == end() ? nullptr : &*next(it); };
        if (bad(it)){
            erase(it);
            return;
        }
        while (next(it) != end() && bad(next(it)))
            erase(next(it));
        while (it != begin() && bad(prev(it)))
            erase(prev(it));
    }
    ll get(ll x) const{
        auto l = *lower_bound({x, is_query, {}});
        return l.m * x + l.b;
    }
};