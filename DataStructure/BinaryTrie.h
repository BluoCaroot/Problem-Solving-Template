class Trie
{
    vector<vector<int>>tree;
    vector<int>cnt;
    int sz = 1;
    int lg;

public:
    explicit Trie(int mxN, int lg) : tree(2, vector<int>(mxN * lg, -1)), cnt(mxN * lg), lg(lg) {}


    void insert(int x)
    {
        int v = 0;
        cnt[v]++;

        for (int i = 30; i >= 0; --i)
        {
            int bit = (x >> i) & 1;
            if (tree[bit][v] == -1)
                tree[bit][v] = sz++;
            v = tree[bit][v];
            cnt[v]++;
        }
    }
    void erase(int x)
    {
        int v = 0;
        cnt[v]--;

        for (int i = 30; i >= 0; --i)
        {
            int bit = (x >> i) & 1;
            if (tree[bit][v] == -1)
                tree[bit][v] = sz++;
            v = tree[bit][v];
            cnt[v]--;
        }
    }

    int query(int x, int k) // number of elements y where x xor y greater than k
    {
        int v = 0;
        int ans = 0;

        for (int i = 30; i >= -1; --i)
        {
            if (i == -1)
            {
                ans += cnt[v];
                break;
            }
            if (((k >> i) & 1) && (tree[(((x >> i) & 1) ^ 1)][v] != -1) && cnt[tree[(((x >> i) & 1) ^ 1)][v]])
                v = tree[(((x >> i) & 1) ^ 1)][v];
            else if (!((k >> i) & 1))
            {
                if (tree[(((x >> i) & 1) ^ 1)][v] != -1)
                    ans += cnt[tree[(((x >> i) & 1) ^ 1)][v]];
                if (tree[(((x >> i) & 1))][v] != -1 && cnt[tree[(((x >> i) & 1))][v]])
                    v = tree[(((x >> i) & 1))][v];
                else
                    break;
            }
            else
                break;
        }
        return ans;
    }

};