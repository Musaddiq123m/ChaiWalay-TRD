struct FWHT {
    int n;
    int mode; // 0 = XOR, 1 = AND, 2 = OR
    vector<long long> a;

    FWHT(const vector<long long>& input, int mode)
        : mode(mode), a(input) {
        n = a.size();
        convolve();
    }

private:
    void transform(bool inverse = false) {
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += len << 1) {
                for (int j = 0; j < len; j++) {
                    long long u = a[i + j];
                    long long v = a[i + j + len];

                    if (mode == 0) {
                        // XOR
                        a[i + j] = u + v;
                        a[i + j + len] = u - v;
                    }
                    else if (mode == 1) {
                        // AND
                        if (!inverse)
                            a[i + j] = u + v;
                        else
                            a[i + j] = u - v;
                    }
                    else {
                        // OR
                        if (!inverse)
                            a[i + j + len] = u + v;
                        else
                            a[i + j + len] = v - u;
                    }
                }
            }
        }

        if (mode == 0 && inverse) {
            for (auto &x : a) x /= n;
        }
    }

    void convolve() {
        transform(false);
        for (int i = 0; i < n; i++)
            a[i] *= a[i];
        transform(true);
    }
};
