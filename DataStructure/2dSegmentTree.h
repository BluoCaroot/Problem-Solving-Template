
int st[N << 2][N << 2], n, m;

void build_y(vector<vector<int>> &v, int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx)
            st[vx][vy] = v[lx][ly];
        else
            st[vx][vy] = min(st[vx << 1][vy], st[vx << 1 | 1][vy]);
        return;
    }
    int my = (ly + ry) / 2;
    build_y(v, vx, lx, rx, vy << 1, ly, my);
    build_y(v, vx, lx, rx, vy << 1 | 1, my + 1, ry);
    st[vx][vy] = min(st[vx][vy << 1], st[vx][vy << 1 | 1]);

}

void build(vector<vector<int>> &v, int vx, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        build(v, vx << 1, lx, mx);
        build(v, vx << 1 | 1, mx + 1, rx);
    }
    build_y(v, vx, lx, rx, 1, 0, m - 1);
}

int query_y(int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry)
        return 1e9;
    if (ly == tly && ry == try_)
        return st[vx][vy];
    int my = (tly + try_) / 2;
    return min(
            query_y(vx, vy << 1, tly, my, ly, min(ry, my)),
            query_y(vx, vy << 1 | 1, my + 1, try_, max(ly, my + 1), ry)
    );
}

int query(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx)
        return 1e9;
    if (lx == tlx && rx == trx) {
        return query_y(vx, 1, 0, m - 1, ly, ry);
    }
    int mx = (tlx + trx) / 2;
    return min(
            query(vx << 1, tlx, mx, lx, min(mx, rx), ly, ry),
            query(vx << 1 | 1, mx + 1, trx, max(mx + 1, lx), rx, ly, ry));
}
void update_y (int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry) {
        if (lx == rx)
            st[vx][vy] = new_val;
        else
            st[vx][vy] = min(st[vx*2][vy], st[vx*2+1][vy]);
    }
    else {
        int my = (ly + ry) / 2;
        if (y <= my)
            update_y (vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            update_y (vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
        st[vx][vy] = min(st[vx][vy*2], st[vx][vy*2+1]);
    }
}

void update_x (int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x (vx*2, lx, mx, x, y, new_val);
        else
            update_x (vx*2+1, mx+1, rx, x, y, new_val);
    }
    update_y (vx, lx, rx, 1, 0, m-1, x, y, new_val);
}