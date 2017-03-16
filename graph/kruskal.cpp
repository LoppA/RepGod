#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double E = exp(1);

const int N = 1e5 + 4;

class uni {
public:
	int pai[N], size[N];
	int cps;

	uni() {
		memset(pai, -1, sizeof pai);
		memset(size, 0, sizeof size);
	}

	uni(int n) {
		memset(pai, -1, sizeof pai);
		memset(size, 0, sizeof size);
		cps = n;
	}

	int find (int u) {
		if (pai[u] == -1)
			return u;
		else 
			return pai[u] = find(pai[u]);
	}

	bool une (int u, int v) {
		u = find(u);	v = find(v);
		if (u == v) return false;

		if (size[u] < size[v])
			swap(u, v);

		pai[v] = u;
		size[u] += size[v];
		size[v] = 0;
		cps--;
		return true;
	}

	int comps () { return cps; }
};

vector <pair<int, ii> > edg;
vector <ii> mst;

int kruskal () {
	sort(edg.begin(), edg.end());
	int ret = 0;
	uni U;

	for (int i = 0; i < (int)edg.size(); i++) {
		int u = edg[i].se.fi, v = edg[i].se.se;
		int dist = edg[i].fi;
		if (U.une(u,v)) {
			mst.pb(mk(u,v));
			ret += dist;
		}
	}

	return ret;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
