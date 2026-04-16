struct node {
    ll sum, lazy = 0;

    node(ll sum = 0) : sum(sum) {}

};


struct SegmentTree {
    vector<node> st;
    int sz;

    SegmentTree(vector<int> &v) {
        sz = 1;
        while (sz < v.size())
            sz <<= 1;
        st.resize(sz << 1);
        for (int i = 0; i < v.size(); ++i)
            st[i + sz] = node(v[i]);
        for (int i = sz - 1; i > 0; --i)
            st[i] = merge(st[i << 1], st[i << 1 | 1]);
    }

    node merge(node left, node right) {
        int sum = left.sum + right.sum;
        return {sum};
    }
    void push(int v, int sl, int sr)
    {
        if (st[v].lazy)
        {
            st[v].sum = st[v].sum + st[v].lazy * (sr - sl + 1);
            if (sl != sr)
                st[v << 1].lazy = st[v << 1].lazy + st[v].lazy,
                        st[v << 1 | 1].lazy = st[v << 1 | 1].lazy + st[v].lazy;
            st[v].lazy = 0;
        }
    }

    void update(int v, int sl, int sr, int ql, int qr, int val)
    {
        push(v, sl, sr);
        if (sl > qr || sr < ql)
            return;
        if (ql <= sl && sr <= qr)
        {
            st[v].lazy = st[v].lazy + val;
            push(v, sl, sr);
            return;
        }
        int mid = (sl + sr) / 2;
        update(v << 1, sl, mid, ql, qr, val);
        update(v << 1 | 1, mid + 1, sr, ql, qr, val);
        st[v] = merge(st[v << 1], st[v << 1 | 1]);
    }

    node query(int v, int sl, int sr, int ql, int qr) {
        push(v, sl, sr);
        if (sl > qr || sr < ql)
            return {};
        if (ql <= sl && sr <= qr)
            return st[v];
        int mid = (sl + sr) / 2;
        return merge(query(v << 1, sl, mid, ql, qr), query(v << 1 | 1, mid + 1, sr, ql, qr));
    }

    node query(int l, int r) {
        return query(1, 0, sz - 1, l, r);
    }

    void update(int l, int r, int val) {
        update(1, 0, sz - 1, l, r, val);
    }
};