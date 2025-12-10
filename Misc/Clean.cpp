// Cmake files
//add_definitions(-D Clion)
//set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,1000000000")

#pragma GCC optimize("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("Ofast");
#pragma GCC target("avx2")
#include <bits/stdc++.h>

using ll = long long;
using namespace std;
const double pi = acos(-1);
int dx[] = {+0, +0, -1, +1, +1, +1, -1, -1};
int dy[] = {-1, +1, +0, +0, +1, -1, +1, -1};
#define TESTS

void solve() {

}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef Clion
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
#endif
    int tt = 1;
//    cout << fixed << setprecision(10);
#ifdef TESTS
    cin >> tt;
#endif
    for (int tc = 1; tc <= tt; ++tc) {
        solve();
        cout << '\n';
    }
}