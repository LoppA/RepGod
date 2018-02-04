/*

n >= k

T(n) = a1*T(n-1) + a2*T(n-2) + ... + ak*T(n-k)

 _  _     _   (n-(k-1)) _  _   
| Tn |   |a1 ... ak|   |Tk-1|
|Tn-1|   |1 0 0 0 0|   |Tk-2|
|Tn-2| = |0 1 0 0 0| * |Tk-3|
| ...|	 |   ...   |   | ...|
|_T1_|   |0 0 0 1 0|   |_T0_|

*/

#include <bits/stdc++.h>

using namespace std;

#define mk make_pair
#define fi first
#define se second

typedef long long ll;
const ll mod = 1e9 + 7; 

class mat {
public:
	ll m[2][2];

	/*
	 * 1 0
	 * 0 1
	 * */
	mat () {
		m[0][0] = 1;
		m[0][1] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
	}

	/*
	 * a b
	 * c d
	 * */
	mat (ll a, ll b, ll c, ll d) {
		m[0][0] = a;
		m[0][1] = b;
		m[1][0] = c;
		m[1][1] = d;
	}

	mat operator * (const mat &B) const {
		mat ret = mat(0,0,0,0);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					ret.m[i][j] += (m[i][k] * B.m[k][j])%mod;
					ret.m[i][j] %= mod;
				}
			}
		}
		return ret;
	}

};

/*
 A = 1 1
     1 0

 Fn   = A^(n-1) * 1
 Fn-1             1
*/
mat exp (ll y) {
	mat R, A = mat(1,1,1,0);
	mat T = A;

	while (y) {
		if ((y & 1)) {
			R = R * T;
		}
		T = T * T;
		y >>= 1;
	}

	return R;
}

/*
	F(0) = 1	F(1) = 1
	F(n) = 1*F(n-1) + 1*F(n-2)
*/

int main (void) {

	ll n;
	while (cin >> n) {
		mat f = exp(max(n-1,0LL));

		ll res = f.m[0][0] + f.m[0][1];

		cout << "F(" << n << "): "<< res << endl;
	}

	return 0;
}
