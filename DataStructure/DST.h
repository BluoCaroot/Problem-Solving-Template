
struct Node {
    ll sum = 0, lazy = 0;
    Node *left = nullptr, *right = nullptr;
};

struct DST {
    int sz = 1;
    Node *root;

    DST(int n) {
        while (sz < n)
            sz <<= 1;
        root = new Node;
    }
    int get(Node *v)
    {
        if (v == nullptr)
            return 0;
        return v->sum;
    }
    void merge(Node *v) {
        v->sum = get(v->left) + get(v->right);
    }
    void prop(Node *v, int l, int r)
    {
        if (v->lazy)
        {
            v->sum = v->lazy * (r - l + 1);
            if (l != r)
            {
                if (v->left == nullptr)
                    v->left = new Node();
                v->left->lazy = v->lazy;
                if (v->right == nullptr)
                    v->right = new Node();
                v->right->lazy = v->lazy;
            }
            v->lazy = 0;
        }
    }
    ll query(Node *v, int l, int r, int ql, int qr) {
        if (v == nullptr)
            return 0;
        prop(v, l, r);
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return v->sum;
        int m = (l + r) / 2;
        return query(v->left, l, m, ql, qr) + query(v->right, m + 1, r, ql, qr);
    }

    void update(Node *v, int l, int r, int ql, int qr) {
        prop(v, l, r);
        if (ql > r || qr < l)
            return;
        if (v->sum == (r - l + 1)) return;
        if (ql <= l && r <= qr)
        {
            v->lazy = 1;
            prop(v, l, r);
            return;
        }
        int m = (l + r) / 2;

        if (ql <= m) {
            if (v->left == nullptr)
                v->left = new Node();
            update(v->left, l, m, ql, qr);
        }

        if (qr > m) {
            if (v->right == nullptr)
                v->right = new Node();
            update(v->right, m + 1, r, ql, qr);
        }
        merge(v);
    }


};
