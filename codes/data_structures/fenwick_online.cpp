// Usage : BIT <int > bit (n); bit . add (idx , val); bit . sum (l, r);
template <class T>
struct BIT
{
    int n;
    vector<T> b, a;
    BIT(int n) : n(n), b(n + 1), a(n) {}
    BIT(vector<T> &v) : BIT(v.size())
    {
        for (int i = 0; i < n; ++i)
            add(i, v[i]);
    }
    void add(int i, T v)
    {
        a[i] += v;
        for (++i; i <= n; i += i & -i)
            b[i] += v;
    }
    void set(int i, T v) { add(i, v - a[i]); }
    T sum(int i)
    {
        T r = 0;
        for (++i; i; i -= i & -i)
            r += b[i];
        return r;
    }
    T sum(int l, int r) { return sum(r) - (l ? sum(l - 1) : 0); }
    int lower_bound(T x)
    {
        int i = 0;
        for (int k = 1 << __lg(n); k; k >>= 1)
            if (i + k <= n && b[i + k] < x)
                x -= b[i += k];
        return i;
    }
};