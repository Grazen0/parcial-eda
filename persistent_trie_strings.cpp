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
constexpr int MAXN = 7*1e5+5;
constexpr int MAXB = 29;
constexpr int E = 26;

int f[MAXN];
int child[E][MAXN];
int nodes = 1;

int add_node(int from) {
    f[nodes] = f[from];
    for (int i = 0; i < E; ++i)
        child[i][nodes] = child[i][from];
    return nodes++;
}


int count_prefix(int root, string& p) {
    for (auto c : p)
        root = child[c-'a'][root];
    return f[root];
}

int add_word(int root, string& s) {
    int new_root = add_node(root);
    int cur = new_root;
    f[cur]++;
    for (auto c : s) {
        cur = child[c-'a'][cur] = add_node(child[c-'a'][cur]);
        f[cur]++;
    }
    return new_root;
}

int rm_word(int root, string& s) {
    int new_root = add_node(root);
    int cur = new_root;
    f[cur]--;
    for (auto c : s) {
        cur = child[c-'a'][cur] = add_node(child[c-'a'][cur]);
        f[cur]--;
    }
    return new_root;
}

int rev[MAXQ+1];

void solve() {
    int n,q;cin>>n>>q;

    for (int i = 0; i < n; ++i) {
        string s;cin>>s;
        rev[i+1] = add_word(rev[i], s);
    }

    while (q--) {
        int l,r;string p;cin>>l>>r>>p;--l;--r;
        cout << count_prefix(rev[r+1], p) - count_prefix(rev[l], p) << "\n";
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t=1;
    //cin>>t;
    while (t--) solve();
    return 0;
}
