const int N = 1e6 + 5, sz = 2;
const int mod[]{(int) 1e9 + 7, (int) 1e9 + 9}, base[]{31, 37};
typedef array<int, sz> hsh;
array<int, sz> pw[N], inv[N];

int binpow(int b, int e, int m) {
    int ret = 1;
    while (e) {
        if (e & 1)
            ret = 1ll * ret * b % m;
        b = 1ll * b * b % m;
        e >>= 1;
    }
    return ret;
}

int modinv(int n, int m) {
    return binpow(n, m - 2, m);
}

void pre() {
    for (int i = 0; i < sz; ++i)
        pw[0][i] = 1;
    for (int i = 1; i < N; ++i)
        for (int j = 0; j < sz; ++j)
            pw[i][j] = 1ll * pw[i - 1][j] * base[j] % mod[j];
    for (int i = 0; i < 2; ++i)
        inv[N - 1][i] = inv(pw[N - 1][0], mod[i]);
    for (int i = N - 2; i >= 0; --i)
        for (int j = 0; j < sz; ++j)
            inv[i][j] = 1ll * inv[i + 1][j] * base[j] % mod[j];
}

hsh Hash(string &s) {
    int n = s.length();
    hsh ret{0, 0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz; ++j) {
            ret[j] = (1ll * s[i] * pw[i][j] % mod[j] + ret[j]) % mod[j];
        }
    }
    return ret;
}

vector<hsh> HashPrf(string &s) {
    int n = s.length();
    hsh cur{0, 0};
    vector<hsh> ret;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz; ++j) {
            cur[j] = (1ll * s[i] * pw[i][j] % mod[j] + cur[j]) % mod[j];
        }
        ret.push_back(cur);
    }
    return ret;
}

hsh query(vector<hsh> &hashes, int l, int r) {
    hsh ret = hashes[r];
    for (int j = 0; j < sz && l; ++j)
        ret[j] = (ret[j] - hashes[l - 1][j]) % mod[j];
    for (int j = 0; j < sz; ++j)
        ret[j] = ret[j] * inv[l][j] % mod[j];
    return ret;
}

hsh concat(hsh left, hsh right, int n) { // n = left.size()
    hsh ret = left;
    for (int j = 0; j < sz; ++j) {
        right[j] = 1ll * right[j] * pw[n][j] % mod[j];
        ret[j] = (ret[j] + right[j]) % mod[j];
    }
    return ret;
}