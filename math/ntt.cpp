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

// root is a r**c, r is nth root of unity r**n = 1 % mod and r**k != 1 % mod for 1 <= k < n
// r**c is (2**k)th root of unity and can be used to calculate ntt for polynomial of size 2**k
// mod must be of form: mod = 2**k * c + 1

const int N = 2e5 + 5;
const int mod = 998244353;
const int root = 363395222;
const int root_1 = 704923114;
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

// a, b => coefs to multiply,  res => resulting coefs
// // a[0], b[0], res[0] = coef x^0
// // Doesnt work with negative coefs
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

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
