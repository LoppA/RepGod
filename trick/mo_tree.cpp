// Tutorial: https://codeforces.com/blog/entry/43230
// Sample problem: https://www.spoj.com/problems/COT2/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);

const int N = 80008, S = 290, Q = 100011, LOG = 21;
int n, m;

class Tree {
private:
  int pai[N][LOG], dist[N];
  int t;

  void build(int u) {
    for (int i = 1; i < LOG; i++) {
      int _pai = pai[u][i-1];
      pai[u][i] = pai[_pai][i-1];
    }
  }

  void init(int u, int p) {
    st[u] = t++;

    pai[u][0] = p;
    build(u);

    for (int v : g[u]) {
      if (v != p) {
        dist[v] = dist[u] + 1;
        init(v, u);
      }
    }

    en[u] = t++;
  }

public:
  vector<int>g[N];
  int st[N], en[N];
  int w[N];

  void build() {
    dist[1] = 0;
    t = 0;
    init(1, 0);

    map<int, int> id;
    for (int i = 1; i <= n; i++) {
      if (!id.count(w[i])) {
        id[w[i]] = id.size();
      }
      w[i] = id[w[i]];
    }
  }

  void add(int u, int v) {
    g[u].pb(v);
    g[v].pb(u);
  }

  int lca(int u, int v){
    if (dist[v] < dist[u])
      swap(v,u);

    int x = dist[v] - dist[u];

    for (int i = 0; i < LOG; i++)
      if (x & (1<<i))
        v = pai[v][i];

    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; i--)
      if (pai[u][i] != pai[v][i]) {
        u = pai[u][i];
        v = pai[v][i];
      }

    return pai[u][0];
  }

} t;

class Query {
public:
  int u, v, lca;
  int l, r;
  int id;

  Query() {}

  void build() {
    if (t.st[u] > t.st[v]) {
      swap(u, v);
    }
    lca = t.lca(u, v);
    if (lca == u) {
      l = t.st[u];
      r = t.st[v];
    } else {
      l = t.en[u];
      r = t.st[v];
    }
  }

  bool operator < (const Query& other) const {
    int i = l/S, j = other.l/S;
    if (i != j) {
      return i < j;
    }
    return r < other.r;
  }
};

class Mo {
public:
  vector<Query> v;
  int res, ans[Q];
  int freq[N], cnt[N];
  int no[N];

  Mo(int m) {
    v = vector<Query>(m);
    int i = 0;
    for (Query &q : v) {
      cin >> q.u >> q.v;
      q.id = i++;
      q.build();
    }

    for (int i = 1; i <= n; i++) {
      no[t.st[i]] = i;
      no[t.en[i]] = i;
    }
  }

  void _add(int i) {
    int j = t.w[i];

    if (!cnt[j]) {
      res++;
    }
    cnt[j]++;
  }

  void _remove(int i) {
    int j = t.w[i];

    cnt[j]--;
    if (!cnt[j]) {
      res--;
    }
  }

  void add(int id) {
    if (id < 0) return;

    int i = no[id];

    freq[i]++;
    if (freq[i] == 1) {
      _add(i);
    } else {
      _remove(i);
    }
  }

  void remove(int id) {
    if (id < 0) return;

    int i = no[id];

    freq[i]--;
    if (freq[i] == 1) {
      _add(i);
    } else {
      _remove(i);
    }
  }

  void solve() {
    sort(v.begin(), v.end());
    res = 0;

    int l = -1, r = -1;
    for (const Query& q : v) {
      while(r < q.r) {
        r++;
        add(r);
      }
      while(l < q.l) {
        remove(l);
        l++;
      }

      while(l > q.l) {
        l--;
        add(l);
      }
      while(r > q.r) {
        remove(r);
        r--;
      }

      if (q.lca != q.u) {
        int l = t.st[q.lca];
        add(l);
        ans[q.id] = res;
        remove(l);
      } else {
        ans[q.id] = res;
      }
    }
  }

  void print() {
    for (int i = 0; i < m; i++) {
      cout << ans[i] << endl;
    }
  }

};

int main (void) {
  ios_base::sync_with_stdio(false);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> t.w[i];
  }
  for (int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    t.add(u, v);
  }
  t.build();

  Mo mo(m);
  mo.solve();
  mo.print();

  return 0;
}

