// Chinese Remainder Theorem
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

ll pot(ll x, ll y, ll mod) {
	ll a = x, ret = 1;

	while(y > 0) {
		if(y&1)
			ret = (ret * a)%mod;

		a = (a * a)%mod;
		y >>= 1;
	}

	return ret;
}

// O(N**2 * log2(p)), works with bultin types until final multplication
// Define: a = x0 + x1*p0 + x2*p0*p1 + ... + x[n-1]*p0*...*p[n-2]
// So:  a = x0 (mod p0)
//      a = x0 + x1*po (mod p1)
// So:  x0 = a0 (mod p0)
//      x1 = (a1 - x0)*p0**-1 (mod p1)
//      x2 = ((a2 - x0)*p0**-1 - x1)*p1**-1 (mod p2)
ll crt(const vector<ll> &a, const vector<ll> &p) {
	if(a.size() == p.size());
	int n = a.size();
	vector<ll> x(n);

	for(int i = 0; i < n; i++) {
		x[i] = a[i];
		for(int j = 0; j < i; j++) {
			x[i] = (x[i] - x[j]) * pot(p[j], p[i]-2, p[i]);
			x[i] %= p[i];
			if(x[i] < 0)
				x[i] += p[i];
		}
	}

	// This part could need bit integer
	ll ret = 0;
	ll pp = 1;
	ll _p = 1;
	for(auto it : p)
		_p *= it;

	for(int i = 0; i < n; i++) {
		ret = (ret + x[i] * pp)%_p;
		pp *= p[i];
	}

	return ret;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
