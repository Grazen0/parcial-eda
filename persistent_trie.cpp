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

using vi = vector<int>;

constexpr int MAXQ = 2*1e5;
constexpr int MAXN = 32*MAXQ+5;
constexpr int MAXB = 29;
constexpr int E = 2;

int f[MAXN];
int child[E][MAXN];
int nodes = 1;

int add_node(int from) {
    f[nodes] = f[from];
    for (int i = 0; i < E; ++i)
        child[i][nodes] = child[i][from];
    return nodes++;
}


int search(int root, int x) {
    for (int i = MAXB; i >= 0; --i)
        root = child[(x>>i)&1][root];
    return f[root];
}

int add_num(int root, int x) {
    int new_root = add_node(root);
    int cur = new_root;
    f[cur]++;
    for (int i = MAXB; i >= 0; --i) {
        int b = (x>>i) & 1;
        cur = child[b][cur] = add_node(child[b][cur]);
        f[cur]++;
    }
    return new_root;
}

int rm_num(int root, int x) {
    int new_root = add_node(root);
    int cur = new_root;
    f[cur]--;
    for (int i = MAXB; i >= 0; --i) {
        int b = (x>>i) & 1;
        cur = child[b][cur] = add_node(child[b][cur]);
        f[cur]--;
    }
    return new_root;
}

int kth(int root, int k) {
    int ans = 0;

    for (int i = MAXB; i >= 0; --i) {
        if (k <= f[child[0][root]]) {
            root = child[0][root];
        } else {
            k -= f[child[0][root]];
            root = child[1][root];
            ans |= 1<<i;
        }
    }

    return ans;
}

int maximize(int l, int r, int x) {
    int ans = 0;

    for (int i = MAXB; i >= 0; --i) {
        int b = (x >> i) & 1;
        if (f[child[b^1][r]] - f[child[b^1][l]] > 0) {
            r = child[b^1][r];
            l = child[b^1][l];
            ans |= 1<<i;
        } else {
            r = child[b][r];
            l = child[b][l];
        }
    }

    return ans;
}

int kth_range_xor(int l, int r, int k, int x) {
    int ans = 0;

    for (int i = MAXB; i >= 0; --i) {
        int b = (x >> i) & 1;
        int fd = f[child[b][r]] - f[child[b][l]];
        if (k <= fd) {
            r = child[b][r];
            l = child[b][l];
        } else {
            k -= fd;
            r = child[b^1][r];
            l = child[b^1][l];
            ans |= 1<<i;
        }
    }

    return ans;
}

int rev[MAXQ+1];
int par[MAXQ+1];

void solve() {
    int n;cin>>n;
    for (int i = 0; i < n; ++i) {
        int a;cin>>a;
        rev[i+1] = add_num(rev[i], a);
    }

    int q;cin>>q;
    while (q--) {
        int l,r,x,k;cin>>l>>r>>x>>k;--l;--r;
        cout << kth_range_xor(rev[l], rev[r+1], k, x) << "\n";
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t=1;
    //cin>>t;
    while (t--) solve();
    return 0;
}
