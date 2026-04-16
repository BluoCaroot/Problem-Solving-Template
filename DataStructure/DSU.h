struct DSU {
    vector<int> par, sz;

    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }

    int find(int u) {
        if (u == par[u])
            return u;
        return par[u] = find(par[u]);
    }

    bool same(int u, int v) { return find(u) == find(v); }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v])
            swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }

    int size(int u) { return sz[find(u)]; }
};