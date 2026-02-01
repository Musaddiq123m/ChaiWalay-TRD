template <typename T = long long, int BITS = 62>
struct XORBasis {
    T basis[BITS + 1];
    int sz = 0;

    XORBasis(){
        for (int i = 0; i <= BITS; i++) basis[i] = 0;
    }

    bool insert(T x) {
        for (int i = BITS; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (!basis[i]) {
                basis[i] = x;
                sz++;
                return true;
            }
            x ^= basis[i];
        }
        return false;
    }

    bool canForm(T x) {
        //formula 2^(number of elements - basis size)
        for (int i = BITS; i >= 0; i--) {
            x = std::min(x, x ^ basis[i]);
        }
        return x == 0;
    }

    T getMax(){
        T res = 0;
        for (int i = BITS; i >= 0; i--) {
            res = std::max(res, res ^ basis[i]);
        }
        return res;
    }

    long long countDistinct() {return 1LL << sz;}
};