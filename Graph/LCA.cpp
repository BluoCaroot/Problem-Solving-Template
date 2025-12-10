template<typename T>
struct SparseTable{
    vector<vector<T>>table;
    vector<int>lg;
    int sz;
    SparseTable() {}
    SparseTable(vector<T>&v) : sz(v.size()){
        lg.resize(sz + 1);
        lg[1] = 0;
        for (int i = 2; i <= sz; ++i)
            lg[i] = lg[i / 2] + 1;
        table = vector<vector<T>>(lg[sz] + 1, vector<T>(sz));
        table[0] = v;
        for (int i = 1; i <= lg[sz]; ++i)
            for (int j = 0; j + (1 << i) <= sz; ++j)
                table[i][j] = f(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
    }
    T f(T &a, T &b)
    {
        return min(a, b);
    }
    T query(int l, int r)
    {
        assert(l <= r);
        int range = r - l + 1;
        int log = lg[range];
        return f(table[log][l], table[log][r - (1 << log) + 1]);
    }
};
struct LCA{
    SparseTable<pair<int, int>>st;
    vector<pair<int, int>>tour;
    vector<vector<int>>adj;
    vector<int>in, depth;
    int sz;
    LCA(vector<vector<int>>&adj) : adj(adj){
        sz = adj.size();
        in.resize(sz);
        depth.resize(sz);
        dfs(0, 0);
        st = SparseTable<pair<int, int>>(tour);
    }
    void dfs(int u, int p)
    {
        in[u] = tour.size();
        tour.emplace_back(depth[u], u);
        for (auto v : adj[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            tour.emplace_back(depth[u], u);
        }
    }
    int query(int u, int v)
    {
        u = in[u], v = in[v];
        if (u > v)
            swap(u, v);
        return st.query(u, v).second;
    }
    int dist(int u, int v)
    {
        int lca = query(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }
};