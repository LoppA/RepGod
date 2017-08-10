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


const int N = 3e5 + 5, M = 205;
const ll mod = 1e9 + 7;
ll fat[N];
ll ch[M][M];

ll pot (ll x, ll y) {
	ll ret = 1;

	while (y) {
		if (y & 1)
			ret = (ret * x)%mod;

		x = (x * x)%mod;
		y >>= 1;
	}

	return ret;
}

void pre_fat () {
	fat[0] = 1;
	for (ll i = 1; i < N; i++) 
		fat[i] = (fat[i - 1] * i)%mod;
}

ll choose (ll a, ll b) {
	if (b > a)	return 0;

	ll r = (fat[a] * pot(fat[b], mod - 2))%mod;
	r = (r * pot(fat[a - b], mod - 2))%mod;

	return r;
}

void pre_choose () {

	for (int i = 0; i < M; i++) {
		ch[i][0] = ch[i][i] = 1;
		for (int j = 1; j < i; j++) 
			ch[i][j] = (ch[i-1][j-1] + ch[i-1][j])%mod;
	}

}

ll choose2 (int a, int b) {
	return ch[a][b];
}

int main (void) {
	ios_base::sync_with_stdio(false);

	pre_fat();
	pre_choose();

	return 0;
}
