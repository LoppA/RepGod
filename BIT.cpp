#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;
ll v[N];	// valores iniciais

class BIT { 
private:
	ll t1[N], t2[N];

	/* upd t[at..N]*/
	void update (ll t[], int at, ll val) {
		for ( ; at <= N; at += at&(-at))
			t[at] += val;
	}

	/* point query*/
	ll query (ll t[], int b) {
		ll sum = v[b];
		for (; b  > 0; b -= b&(-b))
			sum += t[b];
		return sum;
	}

	/* query [1..b]*/
	ll query (int b) {
		return query (t1, b) * b - query (t2, b);
	}

public:
	/* upd t[a..b]*/
	void update (ll a, ll b, ll val) {
		update (t1, a, val);
		update (t1, b + 1, -val);
		update (t2, a, val * (a-1));
		update (t2, b + 1, -val * b);
	}

	/* query [a..b]*/
	ll query (int a, int b) {
		return query(b) - query(a-1);
	}

	BIT () {
		memset (t1, 0, sizeof t1);
		memset (t2, 0, sizeof t2);
	}
};

int main (void) {

	return 0;
}
