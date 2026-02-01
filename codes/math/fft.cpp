void fft(vector<complex<double>>& a) {
    int n = (int)a.size();
    int L = 31 - __builtin_clz(n);

    static vector<complex<long double>> R(2, 1);
    static vector<complex<double>> rt(2, 1);

    for (static int k = 2; k < n; k <<= 1) {
        R.resize(n);
        rt.resize(n);
        auto x = polar((long double)1.0, acosl(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) {
            R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
            rt[i] = (complex<double>)R[i];
        }
    }

    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | ((i & 1) << L)) >> 1;
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                double* x = (double*)&rt[j + k];
                double* y = (double*)&a[i + j + k];

                complex<double> z(
                    x[0] * y[0] - x[1] * y[1],
                    x[0] * y[1] + x[1] * y[0]
                );

                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

// when using conv make sure to + 0.5 then convert to long long to prevent precision
vector<double> convolution(const vector<double>& a,
                           const vector<double>& b) {
    if (a.empty() || b.empty()) return {};

    int resultSize = (int)a.size() + (int)b.size() - 1;
    int L = 32 - __builtin_clz(resultSize);
    int n = 1 << L;

    vector<complex<double>> in(n), out(n);

    for (int i = 0; i < (int)a.size(); i++) in[i].real(a[i]);
    for (int i = 0; i < (int)b.size(); i++) in[i].imag(b[i]);

    fft(in);

    for (auto& x : in) x *= x;

    for (int i = 0; i < n; i++) {
        out[i] = in[(-i) & (n - 1)] - conj(in[i]);
    }

    fft(out);

    vector<double> res(resultSize);
    for (int i = 0; i < resultSize; i++) {
        res[i] = imag(out[i]) / (4 * n);
    }
    return res;
}


template<int MOD>
vector<long long> convolutionMod(const vector<long long>& a,
                                 const vector<long long>& b) {
    if (a.empty() || b.empty()) return {};

    int resultSize = (int)a.size() + (int)b.size() - 1;
    int B = 32 - __builtin_clz(resultSize);
    int n = 1 << B;

    int cut = (int)sqrt(MOD);

    vector<complex<double>> L(n), R(n), outl(n), outs(n);

    for (int i = 0; i < (int)a.size(); i++)
        L[i] = complex<double>(a[i] / cut, a[i] % cut);

    for (int i = 0; i < (int)b.size(); i++)
        R[i] = complex<double>(b[i] / cut, b[i] % cut);

    fft(L);
    fft(R);

    for (int i = 0; i < n; i++) {
        int j = (-i) & (n - 1);

        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n)
                  / complex<double>(0, 1);
    }

    fft(outl);
    fft(outs);

    vector<long long> res(resultSize);
    for (int i = 0; i < resultSize; i++) {
        long long av = (long long)(real(outl[i]) + 0.5);
        long long cv = (long long)(imag(outs[i]) + 0.5);
        long long bv = (long long)(imag(outl[i]) + 0.5)
                     + (long long)(real(outs[i]) + 0.5);

        res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
    }
    return res;
}

