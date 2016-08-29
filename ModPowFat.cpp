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

const int N = 3e5 + 5;
ll mod = 1e9 + 7;
ll ft[N];

ll fat (ll n) {
	if (n <= 1)	return 1;
	if (ft[n]) return ft[n];
	return ft[n] = (n * fat(n-1))%mod;
}

ll pot (ll x, ll y) {
	if (y == 1) return x;
	if (y == 0) return 1;
	
	ll ret1 = pot(x, y/2);
	ll ret = ret1;
	if ((y%2) == 1) {
		ret = (ret * x)%mod;
	}
	ret = (ret * ret1)%mod;

	return ret;
}

ll choose (ll a, ll b) {
	ll r = (fat(a) * pot(fat(b), mod - 2))%mod;
	r = (r * pot(fat(a - b), mod - 2))%mod;
	return r;
}

int main (void) {
	ios_base::sync_with_stdio(false);
	
	return 0;
}
