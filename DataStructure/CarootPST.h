

struct PST {
    struct Node {
        ll sum = 0;
        Node *left, *right;
    };
    int sz = 1;
    vector<Node *> roots;

    PST(int n) {
        while (sz < n)
            sz <<= 1;
        roots.emplace_back(new Node);
        build(roots.back(), 0, sz - 1);
    }

    void merge(Node *v) {
        v->sum = v->left->sum + v->right->sum;
    }

    void build(Node *v, int l, int r) {
        if (l == r)
            return;
        int m = (l + r) / 2;
        v->left = new Node;
        v->right = new Node;
        build(v->left, l, m);
        build(v->right, m + 1, r);
    }

    ll query(Node *v, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return v->sum;
        int m = (l + r) / 2;
        return query(v->left, l, m, ql, qr) + query(v->right, m + 1, r, ql, qr);
    }

    void update(Node *v, int l, int r, int ind, int val) {
        if (l == r) {
            v->sum += val;
            return;
        }
        int m = (l + r) / 2;
        if (ind <= m) {
            Node *next = new Node(*v->left);
            update(next, l, m, ind, val);
            v->left = next;
        } else {
            Node *next = new Node(*v->right);
            update(next, m + 1, r, ind, val);
            v->right = next;
        }
        merge(v);
    }

    void update(int ind, int val) {
        roots.emplace_back(new Node(*roots.back()));
        update(roots.back(), 0, sz - 1, ind, val);
    }

    ll query(int l, int r, int k) {
        return query(roots[r], 0, sz - 1, k, sz - 1) -
               query(roots[l - 1], 0, sz - 1, k, sz - 1);
    }
};
