/* UVA 11228
   MST - Kruskal  O (M*log(N))	*/

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

const int N = 1e3 + 4;

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

int n;
double r;
ii p[N];

double dist (ii p1, ii p2) {
	return sqrt((p1.fi - p2.fi)*(p1.fi - p2.fi) + (p1.se - p2.se)*(p1.se - p2.se));
}

uni U1;
int go1 () {
	U1 = uni(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (dist(p[i], p[j]) <= r) {
				U1.une(i, j);
			}
		}
	}

	return U1.comps();
}

vector <pair<double, pair<int, int> > > edg;

void kruskal () {
	edg.clear();
	uni U2 = uni(n);
	double r1 = 0, r2 = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			edg.pb(mk(dist(p[i], p[j]),mk(i,j)));
		}
	}
	sort(edg.begin(), edg.end());

	for (int i = 0; i < edg.size(); i++) {
		int u = edg[i].se.fi, v = edg[i].se.se;
		double dist = edg[i].fi;
		if (U2.une(u,v)) {
			if (U1.find(u) != U1.find(v)) r2 += dist;
			else r1 += dist;
		}
	}
	cout << setprecision(0) << fixed  << r1 << " " << r2 << endl;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	int t;	cin >> t;

	for (int T = 1; T <= t; T++) {
		cin >> n >> r;
		for (int i = 0; i < n; i++) {
			cin >> p[i].fi >> p[i].se;
		}
		cout << "Case #" << T << ": ";
		cout << go1() << " ";
		kruskal();
	}

	return 0;
}
