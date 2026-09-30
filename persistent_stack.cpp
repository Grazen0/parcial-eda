//     .--.
//    |o_o |
//    |:_/ |
//   //   \ \
//  (|     | )
// /'\_   _/`\
// \___)=(___/

#include <bits/stdc++.h>
using namespace std;

#define dbg(x) do {cerr<<#x<<" = "<<(x)<<"\n";} while (0)
#define vdbg(v) do {cerr<<#v<<" = "; for(auto&x:v)cerr<<x<<" ";cerr<<"\n";} while (0)

#define int long long

using vi = vector<int>;

constexpr int MAXQ = 2e5;
constexpr int MAXN = MAXQ+5;

int top[MAXN];
int nxt[MAXN];
int nodes = 1;

int add_node(int x, int p) {
    top[nodes] = x;
    nxt[nodes] = p;
    return nodes++;
}

int push(int v, int x) {
    return add_node(x, v);
}

int pop(int v) {
    return nxt[v];
}

int rev[MAXQ+1];

void solve() {
    int n;cin>>n;

    for (int i = 0; i < n; ++i) {
        int t,m;cin>>t>>m;
        if (m == 0)
            rev[i+1] = pop(rev[t]);
        else
            rev[i+1] = push(rev[t], top[rev[t]] + m);
    }

    int ans = 0;
    for (int i = 0; i <= n; ++i)
        ans += top[rev[i]];
    cout << ans << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t=1;
    //cin>>t;
    while (t--) solve();
    return 0;
}
