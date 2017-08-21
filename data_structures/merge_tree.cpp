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

const int N = 250123;
int n;
ii v[N];

vector <int> seg[4*N + 1];

void build (int r, int i, int j) {

	if (i == j) {
		seg[r].pb(v[i].se);
	} else {
		int mid = (i + j)/2;
		build (2*r, i, mid);
		build (2*r + 1, mid + 1, j);

		seg[r].resize(j - i + 1);

		merge (seg[2*r].begin(), seg[2*r].end(),
			seg[2*r + 1].begin(), seg[2*r + 1].end(), seg[r].begin());
	}
}

int a, b, c, d;
int query (int r, int i, int j) {
	if (v[i].fi > b or v[j].fi < a)	return 0;

	if (v[i].fi >= a and v[j].fi <= b) {

		vector <int> &v = seg[r];

		int i = lower_bound(v.begin(), v.end(), c) - v.begin();
		int j = upper_bound(v.begin(), v.end(), d) - v.begin() - 1;

		return max (0, j - i + 1);
	} else {
		int mid = (i + j)/2;
		int L = query (2*r, i, mid);
		int R = query (2*r + 1, mid + 1, j);
		return L + R;
	}

	return 0;
}

int w[N];

int main (void) {
	ios_base::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n; i++) 
		cin >> v[i].fi >> v[i].se;
	sort (v, v + n);

	build (1, 0, n - 1);

	int q;	cin >> q;
	for (int i = 4; i < q + 4; i++) {
		int e, f, g, h;
		cin >> e >> f >> g >> h;

		a = e ^ w[i-4];
		b = f ^ w[i-3];
		c = g ^ w[i-2];
		d = h ^ w[i-1];

		if (a > b)	swap (a, b);
		if (c > d)	swap (c, d);

		w[i] = query (1, 0, n - 1);

		cout << w[i] << endl;
	}

	return 0;
}
