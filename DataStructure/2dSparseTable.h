
int st[N][N][10][10];

void build(vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j)
            st[i][j][0][0] = v[i][j];
        for (int l = 1; l < 10; ++l)
            for (int j = 0; (j + (1 << l)) <= v[i].size(); ++j)
                st[i][j][0][l] = min(st[i][j][0][l - 1], st[i][j + (1 << (l - 1))][0][l - 1]);
    }
    for (int l1 = 1; l1 < 10; ++l1)
        for (int i = 0; i + (1 << l1) <= v.size(); ++i)
            for (int l2 = 0; l2 < 10; ++l2)
                for (int j = 0; j < v[i].size(); ++j)
                    st[i][j][l1][l2] = min(st[i][j][l1 - 1][l2], st[i + (1 << (l1 - 1))][j][l1 - 1][l2]);
}

int query(int x1, int y1, int x2, int y2) {
    int lx = __lg(x2 - x1 + 1);
    int ly = __lg(y2 - y1 + 1);
    auto a = min(st[x1][y1][lx][ly], st[x1][y2 + 1 - (1 << ly)][lx][ly]);
    auto b = min(st[x2 + 1 - (1 << lx)][y1][lx][ly], st[x2 + 1 - (1 << lx)][y2 + 1 - (1 << ly)][lx][ly]);
    return min(a, b);
}