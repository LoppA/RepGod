/* SPOJ SOLUTION: MKTHNUM
	Persisten Segmentation Tree
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
const double E = exp(1);

const int N = 1e5 + 5;
const int M = 7000000;
int n, m;
int a[N], d[N];

int v[M], L[M], R[M], root[N];
int nodes;

int build (int l, int r) {
	int j = nodes++;
	if (l == r) {
		v[j] = 0;
	} else {
		int m = (l + r)/2;
		L[j] = build(l, m);
		R[j] = build(m+1, r);
		v[j] = v[L[j]] + v[R[j]];
	}
	return j;
}

int update (int i, int l, int r, int p, int c) {
	int j = nodes++;
	if (l == r) {
		v[j] = c;
	} else {
		int m = (l + r)/2;
		if (p <= m) {
			L[j] = update(L[i], l, m, p, c);
			R[j] = R[i];
		} else {
			L[j] = L[i];
			R[j] = update(R[i], m+1, r, p, c);
		}
		v[j] = v[L[j]] + v[R[j]];
	}
	return j;
}

int mkquery (int a, int b, int l, int r, int c) {
	if (l == r) {
		return l;
	}

	int nl = v[L[b]] - v[L[a]];
	int m = (l+r)/2;
	if (c <= nl) 
		return mkquery(L[a], L[b], l, m, c);

	return mkquery(R[a], R[b], m + 1, r, c - nl);
}

int main (void) {
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	vector <ii> v;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		d[i] = a[i];
		v.pb(mk(a[i],i));
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		a[v[i].se] = i + 1;
	}

	root[0] = build(1, n);

	for (int i = 1; i <= n; i++) 
		root[i] = update (root[i-1], 1, n, a[i], 1);

	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;
		int res = mkquery (root[a-1], root[b], 1, n, c);
		cout << v[res-1].fi << endl;
	}

	return 0;
}
