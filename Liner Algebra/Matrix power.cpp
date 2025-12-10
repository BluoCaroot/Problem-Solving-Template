
template<class T>
struct Matrix {
    vector<vector<T>> mat;
    vector<Matrix>pre;
    int N;

    Matrix(vector<vector<T>> v) : mat(v), N(v.size()) {}

    Matrix() {}

    Matrix operator*(Matrix &other) {
        Matrix ret(vector<vector<T>>(N, vector<T>(N, 0)));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    ret.mat[i][j] = (ret.mat[i][j] + mat[i][k] * other.mat[k][j] % M) % M;
        return ret;
    }

    vector<T> operator*(vector<T> &other) {
        vector<T> ret(N);
        for (int i = 0; i < N; ++i)
            for (int k = 0; k < N; ++k)
                ret[i] = (ret[i] + mat[i][k] * other[k] % M) % M;
        return ret;
    }
    void init()
    {
        pre.emplace_back(*this);
        for (int i = 1; i < 60; ++i)
            pre.emplace_back(pre.back() * pre.back());
    }
    vector<T> solve(T exp, vector<T> &other) {
        vector<T> ret = other;
        for (int i = 0; exp >> i; ++i)
            if (exp >> i & 1)
                ret = pre[i] * ret;
        return ret;
    }
};