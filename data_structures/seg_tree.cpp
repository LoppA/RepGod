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

struct SegT {
	vector <ll> seg, lazy;
	int n;

	SegT () {}

	SegT (int n) {
		this->n = n;
		seg.resize(4*n + 1);
		lazy.resize(4*n + 1);
	}

	void prop (int r, int i, int j) {

		seg[r] += lazy[r] * (j-i+1);

		if (i != j) {
			lazy[2*r] += lazy[r];
			lazy[2*r + 1] += lazy[r];
		}

		lazy[r] = 0;
	}

	int a, b;
	ll update (int r, int i, int j, ll val) {
		prop (r, i, j);
		if (j < a or i > b)	return 0LL;

		if (i >= a and j <= b) {
			lazy[r] += val;
			prop (r, i, j);
			return seg[r];
		} else {
			int mid = (i + j)/2;
			ll L = update (2*r, i, mid, val);
			ll R = update (2*r + 1, mid + 1, j, val);
			return L + R;
		}
	}

	ll update (int l, int r, ll val) {
		a = l;	b = r;
		return update (1, 0, n - 1, val);
	}

	ll query (int l, int r) {
		return update (l, r, 0);
	}

};

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
