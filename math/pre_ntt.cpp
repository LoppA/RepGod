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

const int N = 1e5 + 5;
ll mod, n, c;
int vis[N];
vector<int> v;

void crivo() {
	for(int i = 2; i < N; i++) 
		if(!vis[i]) 
			for(int j = i + i; j < N; j += i)
				vis[j] = 1;
}

int pot(ll x, ll y, int mod) {
	int ret = 1;
	ll a = x;

	while(y > 0) {
		if(y&1)
			ret = (a * ret)%mod;

		a = (a * a)%mod;
		y>>=1;
	}

	return ret;
}

void find_nth_root(int mod) {
	crivo();

	int n = mod - 1;
	int m = sqrt(n) + 2;

	for(int i = 2; i < m; i++) 
		if(!vis[i] and n%i == 0) 
			v.pb(n/i);

	// find if i**k != 1 for 1 <= k < mod - 1 = 2**k * c
	// just need to try (mod - 1)/prime_is_(mod-1) because of cicles
	for(int i = 2; i < mod; i++) {
		bool f = true;
		for(auto d : v) 
			if(pot(i, d, mod) == 1) 
				f = false;

		if(f) {
			// if i is (mod - 1)th root, i**c  is (2**k)th root
			// now we can use i**c as root of ntt for polynomial of size 2**k (order 2**k - 1)
			cout << "r: " << i << endl;
			cout << "root = r**c: " << pot(i, c, mod) << endl;
			cout << "root_1 = r**-c: " << pot(i, (c*(mod - 2))%(mod-1), mod) << endl;
			return;
		}
	}
}

void find_pw(int n) {
	int pw = 1;
	int k = 0;

	while(pw < n) {
		pw <<= 1;
		k++;
	}

	c = (mod - 1)/pw;

	cout << "pw: " << pw << " root_pw: 1<<" << k << endl;
	cout << "(mod-1)%pw: " << (mod-1)%pw << " (mod-1)/pw = c: " << c << endl;

	// mod must be of form mod = 2**k * c + 1
	assert((mod-1)%pw == 0);
}

int main (void) {
	ios_base::sync_with_stdio(false);

	cout << "mod: ";
	cin >> mod;
	cout << "\nn: ";
	cin >> n;

	cout << "mod: " << mod << endl;

	find_pw(2*n);

	find_nth_root(mod);

	return 0;
}
