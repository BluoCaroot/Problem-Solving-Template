struct HLD {
    vector<ll> tin, tout, depth, par, head, sz;

    int dfs(int u, vector<vector<int>> &adj, int p = 0) {
        sz[u] = 1;
        for (auto &v: adj[u]) {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            par[v] = u;
            sz[u] += dfs(v, adj, u);
            if (sz[v] > sz[adj[u][0]] || adj[u][0] == p)
                swap(v, adj[u][0]);
        }
        return sz[u];
    }

    void decompose(int u, vector<vector<int>> &adj, int &t, int p = 0) {
        tin[u] = t++;
        for (auto &v: adj[u]) {
            if (v == p)
                continue;
            if (tin[u] == t - 1)
                head[v] = head[u];
            else
                head[v] = v;
            decompose(v, adj, t, u);
        }
        tout[u] = t - 1;
    }

    HLD(vector<vector<int>> &adj) : tin(adj.size()), head(adj.size()), tout(adj.size()), depth(adj.size()), par(adj.size()), sz(adj.size()) {
        dfs(0, adj);
        int t = 0;
        decompose(0, adj, t);
    }

    vector<pair<int, int>> query(int u, int v) {
        vector<pair<int, int>> ret;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            ret.emplace_back(tin[head[u]], tin[u]);
            u = par[head[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        ret.emplace_back(tin[v], tin[u]);
        return ret;
    }
    vector<array<int, 3>> query_ordered(int u, int v) {
        vector<array<int, 3>> up, down;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                up.push_back({tin[head[u]], tin[u], 1});
                u = par[head[u]];
            } else {
                down.push_back({tin[head[v]], tin[v], 0});
                v = par[head[v]];
            }
        }
        if (depth[u] <= depth[v])
            up.push_back({tin[u], tin[v], 0});
        else
            up.push_back({tin[v], tin[u], 1});
        while (!down.empty())
            up.push_back(down.back()), down.pop_back();
        return up;
    }
};