/*
	O(n * log^2)
	Heavy-Light-Decomposition: on vertices

	************* ONE BASED VERTICES ***************
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);

const int N = 1e5 + 5;
int n;
vector <int> g[N];
int dist[N], size[N], pai[N];
int ind, id[N], heavy[N], ch, chain[N], top[N];

ll seg[4*N + 1];

int a, b;
ll query (int r, int i, int j, int val) {
	if (j < a or i > b)	return 0;

	if (i >= a and j <= b) {
		return seg[r] += val;
	} else {
		int mid = (i + j)/2;
		ll L = query (2*r, i, mid, val);
		ll R = query (2*r + 1, mid + 1, j, val);

		seg[r] = max (seg[2*r], seg[2*r + 1]);
		return max (L, R);
	}
}

ll update (int l, int r, int val) {
	a = l;	b = r;
	return query (1, 0, n - 1, val);
}

ll query (int l, int r) {
	return update (l, r, 0);
}

int pre (int at) {
	size[at] = 1;

	for (auto next : g[at]) {
		if (next == pai[at])	continue;
		dist[next] = dist[at] + 1;
		pai[next] = at;

		size[at] += pre (next);
		
		if (size[next] > size[heavy[at]])
			heavy[at] = next;
	}
	
	return size[at];
}

void dfs (int at, int pai) {
	id[at] = ind++;

	if (heavy[at])	{
		chain[heavy[at]] = chain[at];
		dfs (heavy[at], at);
	}

	for (auto next : g[at]) {
		if (next == pai or next == heavy[at])	continue;
		top[ch] = next;
		chain[next] = ch++;
		dfs (next, at);
	}
}

void build_hld () {
	pre (1);
	ind = ch = 0;
	chain[1] = ch++;
	top[0] = 1;
	dfs (1, 0);
}

ll go (int u, int v) {
	ll res = 0;
	while (chain[u] != chain[v]) {
		if (dist[top[chain[u]]] < dist[top[chain[v]]])	swap (u, v);

		int sobe = top[chain[u]];
		/********* ORDEM: id[sobe] < id[u] ***********/
		res = max (res, query (id[sobe], id[u]));
		u = pai[sobe];
	}
	if (id[u] > id[v])	swap (u, v);

	res = max (res, query (id[u], id[v]));
	return res;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n - 1; i++) {
		int a, b;	cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}

	build_hld ();

	int q;	cin >> q;
	while (q--) {
		char c;	int u, v;	cin >> c >> u >> v;
		if (c == 'I') {
			update (id[u], id[u], v);
		} else {
			cout << go (u, v) << endl;
		}
	}

	return 0;
}
