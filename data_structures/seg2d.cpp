// LIS2    http://codeforces.com/gym/101055/problem/D SOLUTION
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

#define L(x) 2*x
#define R(x) 2*x + 1

struct no {
	int *seg;
	vector <int> v;
	int n;
	int a, b;

	no () {}

	no (int sz) {
		n = sz;
		seg = new int [4*n + 1];
		for (int i = 0; i < 4*n + 1; i++)
			seg[i] = 0;
	}

	void merge (vector <int> &v1, vector <int> &v2) {
		int i = 0, j = 0;
		while (i < (int)v1.size() and j < (int)v2.size()) {
			if (v1[i] <= v2[j]) 
				v.pb(v1[i++]);
			else 
				v.pb(v2[j++]);
		}
		while (i < (int)v1.size())
			v.pb(v1[i++]);
		while (j < (int)v2.size())
			v.pb(v2[j++]);
	}

	int query (int y) {
		y = upper_bound(v.begin(), v.end(), y) - v.begin() - 1;
		a = 0;	b = min(y, (int)v.size() - 1);
		return query (1, 0, n-1);
	}

	int query (int r, int i, int j) {
		if (j < a or i > b) return 0;

		if (i >= a and j <= b) {
			return seg[r];
		} else {
			int mid = (i + j)/2;
			int L = query (L(r), i, mid);
			int R = query (R(r), mid + 1, j);
			return max(L, R);
		}
	}

	void update (int y, int val) {
		y = upper_bound(v.begin(), v.end(), y) - v.begin() - 1;
		a = b = y;
		update (1, 0, n-1, val);
	}

	void update (int r, int i, int j, int val) {
		if (j < a or i > b) return;
		
		if (i >= a and j <= b) {
			seg[r] = max(seg[r], val);
		} else {
			int mid = (i + j)/2;
			update (L(r), i, mid, val);
			update (R(r), mid + 1, j, val);
			seg[r] = max(seg[L(r)], seg[R(r)]);
		}
	}
};

const int N = 1e5 + 5;
int n;
ii p[N], v[N];
map <int, int> id;
map <ii, int> noid;
no seg[4*N + 1];

void build (int r, int i, int j) {
	seg[r] = no (j - i + 1);

	if (i == j) {
		seg[r].v.pb(v[i].se);
	} else {
		int mid = (i + j)/2;
		build (L(r), i, mid);
		build (R(r), mid + 1, j);
		seg[r].merge (seg[L(r)].v, seg[R(r)].v);
	}
}

int a, b, y;

int query (int r, int i, int j) {
	if (j < a or i > b) return 0;

	if (i >= a and j <= b) {
		return seg[r].query(y);
	} else {
		int mid = (i + j)/2;
		int L = query (L(r), i, mid);
		int R = query (R(r), mid + 1, j);
		return max(L, R);
	}
}

void update (int r, int i, int j, int val) {
	if (j < a or i > b) return;

	seg[r].update(y, val);

	if (i == j) return;
	int mid = (i + j)/2;
	update (L(r), i, mid, val);
	update (R(r), mid + 1, j, val);
}

int main (void) {
	scanf ("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf ("%d%d", &p[i].fi, &p[i].se);
		v[i] = p[i];
	}

	sort (v, v + n);

	for (int i = 0; i < n; i++) {
		id[v[i].fi] = i;
		noid[v[i]] = i;
	}
	
	build (1, 0, n - 1);

	int res = 0;
	for (int i = 0; i < n; i++) {
		a = 0;	b = id[p[i].fi];
		y = p[i].se;
		int x = query (1, 0, n - 1);	

		res = max (res, x + 1);

		a = b = noid[p[i]];
		y = p[i].se;
		update (1, 0, n - 1, x + 1);
	}

	printf ("%d\n", res);

	return 0;
}
