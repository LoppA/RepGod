// https://github.com/miskcoo/oicode/blob/master/spoj/MOD.cpp
// http://www.spoj.com/problems/MOD/
// https://e-maxx-eng.appspot.com/algebra/discrete-log.html
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

ll gcd (ll a, ll b) {
	if (!b)
		return a;
	else
		return gcd(b, a%b);
}

// O(sqrt(m))
// Find x in: a**x = b (mod m)	
// a and m are coprimes
// x = np - q => a**(np - q) = b => a**np = b*(a**q) // make n=sqrt(m)
// Find smallest x
ll go(ll a, ll b, ll m) {
	a%=m;
	b%=m;
	if (b == 1)	return 0;

	// PARTE DISNEY
	if (gcd(a,m) != 1) {
		set <int> s;
		ll at = a;
		for (int i = 1; ; i++) {
			if (at == b)	return i;
			if (s.count(at))	return -1;
			s.insert(at);
			at = (at * a)%m;
		}
	}

	// CERTO DAQUI P BAIXO

	ll n = sqrt(m) + 1;

	ll an = 1;
	for (int i = 0; i < n; i++)
		an = (an * a)%m;

	unordered_map<ll, ll> mp;
	// b*(a**q)
	for (ll i = 0, val = b; i < n; i++, val = (val*a)%m) 
		mp[val] = i;

	// a**np
	for (ll i = 1, val=an; i <= n; i++, val = (val*an)%m) 
		if (mp.count(val)) {
//			cout << a << "**" << n*i - mp[val] << " = " << b << " mod " << m << endl;
//			cout << i << " " << val << " " << mp[val] << " " << n << endl;
			return n*i - mp[val];
		}

	return -1;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	ll x, z, k;
	while (cin >> x >> z >> k and (x+z+k)) {
		ll ans = go(x,k,z);
		if (ans == -1)
			cout << "No Solution" << endl;
		else
			cout << ans << endl;
	}

	return 0;
}
