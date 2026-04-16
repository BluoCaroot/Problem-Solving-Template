
struct dsu_save{
    int v = 0, szv = 0, u = 0, szu = 0;
    dsu_save(int v, int szv, int u, int szu):v(v), szv(szv),u(u),szu(szu){}
};
struct dsu_rollback{
  vector<int>p, sz;
  int comps;
  stack<dsu_save>op;
  explicit dsu_rollback(int n) : p(n), sz(n, 1), comps(n){
      iota(p.begin(), p.end(), 0);
  }
  int par(int u)
  {
      return (p[u] == u ? u : par(p[u]));
  }
  bool united(int u, int v)
  {
      u = par(u), v = par(v);
      return u == v;
  }
  bool unite(int u, int v)
  {
      u = par(u), v = par(v);
      if (u == v)
          return false;
      comps--;
      if (sz[u] > sz[v])
          swap(u, v);
      op.emplace(v, sz[v], u, sz[u]);
      p[u] = v;
      sz[v] += sz[u];
      return true;
  }
  void rollback()
  {
      if (op.empty())
          return;
      auto x = op.top();
      op.pop();
      comps++;
      p[x.v] = x.v;
      p[x.u] = x.u;
      sz[x.u] = x.szu;
      sz[x.v] = x.szv;
  }
};
