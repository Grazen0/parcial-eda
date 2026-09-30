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
#define all(x) begin(x), end(x)

#define int long long

using vi = vector<int>;

constexpr int N = 30000;
constexpr int MAXN = N*26;

constexpr int op(int a, int b) { return a + b; }
constexpr int ID = 0;

int val[MAXN];
int le[MAXN];
int ri[MAXN];
int nodes = 0;

int a[N];

int build(int tl, int tr) {
    int t = nodes++;
    if (tl == tr) {
        val[t] = a[tl];
        return t;
    }
    int tm = tl+(tr-tl)/2;
    le[t] = build(tl, tm);
    ri[t] = build(tm+1, tr);
    val[t] = op(val[le[t]], val[ri[t]]);
    return t;
}

int update(int t, int tl, int tr, int pos, int v) {
    int tn = nodes++;
    if (tl == tr) {
        assert(tl == pos);
        val[tn] = val[t] + v;
        return tn;
    }
    le[tn] = le[t];
    ri[tn] = ri[t];
    int tm = tl+(tr-tl)/2;
    if (pos <= tm)
        le[tn] = update(le[t], tl, tm, pos, v);
    else
        ri[tn] = update(ri[t], tm+1, tr, pos, v);
    val[tn] = op(val[le[tn]], val[ri[tn]]);
    return tn;
}

int query(int t, int tl, int tr, int l, int r) {
    if (r < tl or l > tr) return ID;
    if (l <= tl and tr <= r) return val[t];
    int tm = tl+(tr-tl)/2;
    return op(query(le[t], tl, tm, l, r), query(ri[t], tm+1, tr, l, r));
}

int kth(int l, int r, int tl, int tr, int k) {
    if (tl == tr) return tl;

    int fd = val[le[r]] - val[le[l]];
    int tm = tl+(tr-tl)/2;

    if (k <= fd)
        return kth(le[l], le[r], tl, tm, k);
    
    return kth(ri[l], ri[r], tm+1, tr, k - fd);
}

constexpr int MOD = 1e9;

int rev[N+1];

void solve() {
    int n;cin>>n;
    for (int i = 0; i < n; ++i) cin>>a[i];

    vi comp(a, a+n);
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    int c = comp.size();
    for (int i=0;i<n;++i) a[i] = lower_bound(all(comp), a[i]) - comp.begin();

    rev[0] = build(0, c-1);
    for (int i=0;i<n;++i)
        rev[i+1] = update(rev[i], 0, c-1, a[i], 1);

    int q;cin>>q;
    while (q--) {
        int i,j,k;cin>>i>>j>>k;--i;--j;
        k = upper_bound(all(comp), k) - comp.begin();
        cout << query(rev[j+1], 0, c-1, k, c-1) - query(rev[i], 0, c-1, k, c-1) << "\n";
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t=1;
    //cin>>t;
    while (t--) solve();
    return 0;
}
