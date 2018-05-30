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

const int N = 2e5 + 5;
const int mod = 998244353;
const int root = 363395222;
const int root_1 = 786627976;
const int root_pw = 1 << 19;

int inverse(int x, int mod) {
	int y = mod - 2;
	int ret = 1, a = x;

	while(y > 0) {
		if(y&1)
			ret = (1LL * ret * a)%mod;
		
		a = (1LL * a * a)%mod;
		y>>=1;
	}

	return ret;
}

void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = inverse(n, mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	vector<int> fa(a.begin(), a.end()),  fb(b.begin(), b.end());
	int n = 1;
	while (n < (int) max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);

	fft(fa, false), fft (fb, false);
	for (int i = 0; i < n; ++i)
		fa[i] = 1LL * fa[i] * fb[i] % mod;
	fft (fa, true);
	res = fa;
}

// Stirling Number of The First Kind: Count permutations according to their number of cycles
// s(n, k): Count the number of permutations of n elements with k disjoint cycles
// s(n, k): Number of permutations such that for N elements exactly A records are present from front
// record -> number that is greater than previous
// (x)**(n) = x * (x + 1) * (x + 2) ... (x + n - 1) = sum(k=0, n){ s(n, k) * x**k }
// Then the coeficient ak of x**k on (x)**(n) = s(n, k). Use fft to calculate (x)**(n)
// s(n + 1, k) = s(n, k - 1) + n * s(n, k); s(0, 0) = 1 and s(n, 0) = s(0, n) = 0
// O(nn * log(nn))
vector <int> s[N];
int stirling1(int n, int k) {
	int nn = 1;
	while(nn < n) nn <<= 1;

	// (i + x)
	for(int i = 0; i < n; ++i) {
		s[i].push_back(i);	
		s[i].push_back(1);
	}

	// fill the rest with (1)
	for(int i = n; i < nn; ++i) {
		s[i].push_back(1);
	}

	// multiply all s[i]
	// each time first half of s is multiplied by corresponding value on second half
	// then we can consider only first half of s on next iterations
	for(int j = nn; j > 1; j >>= 1){	// j: size of s on this iteration
		int hn = j >> 1;	// half size of s
		for(int i = 0; i < hn; ++i) {	
			multiply(s[i], s[i + hn], s[i]);	// multiply value on first half with second half
		}
	}

	return s[0][k];
}

ll pot(ll x, ll y) {
	ll ret = 1LL;
	ll a = x;

	while(y > 0) {
		if(y&1)
			ret = (ret * a)%mod;

		a = (a * a)%mod;
		y >>= 1;
	}

	return ret;
}

ll fat[N];
ll choose(ll n, ll k) {
	if(k > n)	return 0;

	ll ret = fat[n];

	ret = (ret * pot(fat[n-k], mod - 2))%mod;
	ret = (ret * pot(fat[k], mod - 2))%mod;

	return ret;
}

// Count the number of permutations such that the number of records from the 
// front is A and the number of records from the back is B
// record: a value that is greater than previous ones in some direction
ll solve(ll n, ll a, ll b) {
	ll res = choose(a + b - 2, a - 1);
	res *= stirling1(n - 1, a + b - 2);
	res %= mod;

	return res;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	fat[0] = 1;
	for(int i = 1; i < N; i++)
		fat[i] = (1LL * fat[i-1] * i)%mod;

	return 0;
}
