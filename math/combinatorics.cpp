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

const ll mod = 1e9 + 7;
const int N = 3e5 + 5;
ll fat[N];

ll pot(ll x, ll y) {
	if(!y)	return 1LL;

	ll ret = pot(x, y>>1);
	ret = (ret * ret)%mod;
	if(y&1)
		ret = (ret*x)%mod;
	return ret;
}

// Iterative version
ll i_pot (ll x, ll y) {
	ll ret = 1;

	while (y) {
		if (y & 1)
			ret = (ret * x)%mod;

		x = (x * x)%mod;
		y >>= 1;
	}

	return ret;
}

// Formula: n! / (n-k)! * (k)! 
// With dinamic programming we can use (n + 1, k) = (n, k-1) + (n, k) and (n, 0) = 1, (n, n) = 1 for n >= 0
// (n, k) = (n, n - k) for 0 <= k <= n
// (n, k) = (n/k) * (n-1, k-1)
ll choose(ll n, ll k) {
	if(k > n)	return 0LL;

	ll ret = (fat[n] * pot(fat[n-k], mod-2))%mod;

	return (ret * pot(fat[k], mod-2))%mod;
}

// Stirling Number of The Second Kind: Calculates the number of ways to partition a set of n objects into k non-empty subsets
// Formula explanation: https://math.stackexchange.com/questions/550256/stirling-numbers-of-second-type
// O(k*log2(mod))
// With dinamic programming we can use S(n + 1, k) = S(n, k - 1) + k*S(n, k) and S(n,n) = 1, S(n, 1) = 1 for n >= 1
ll stirling2(ll n, ll k) {
	if(k > n)	return 0LL;

	ll ret = 0;

	for(ll j = 0; j <= k; j++) {
		ret += pot(-1, j%2) * (choose(k,j) * pot(k-j, n))%mod;
		ret %= mod;
	}

	ret = (ret * pot(fat[k], mod - 2))%mod;

	if(ret < 0)
		return ret + mod;
	return ret;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	fat[0] = 1;
	for(ll i = 1; i < N; i++)
		fat[i] = (fat[i-1] * i)%mod;

	return 0;
}
