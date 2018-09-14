/*  O(log2(min(a, b)))
    Solve ax + by = gcd(a,b)

    Bezouts lemma: there is alwayas a solution
        |x| <= |b/g| and |y| <= |a/g|

    x * y <= 0 (x > 0 => y <= 0, y > 0 => x <= 0)

    others solutions: x' = x+k*(b/g), y' = y-k*(a/g) k is integer

    Quick explanation:
        r[0] = a, r[1] = b

        1: r[i-2] = r[i-1]*q[i] + r[i]  // gcd algorithm
        2: r[i] = s[i]*a + t[i]*b       // we want it

        with 1 and 2:
            s[i] = s[i-2] * s[i-1]*q[i]
            t[i] = t[i-2] * s[i-1]*q[i]

            r[0] = a = s[0]*a + t[0]*b => s[0] = 1, t[0] = 0
            r[1] = b = s[1]*a + t[1]*b => s[1] = 0, t[1] = 1

        algorithm stops at a = g, b = 0 => r[n-2], r[n-1]=0
        find gcd(a, b) = r[n-2] = s[n-2]*a + t[n-2]*b
 * */

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

// ax + by = g
ll gcd(ll a, ll b, ll &x, ll &y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll ret = gcd(b, a%b, x, y);
    ll t = x;
    x = y;
    y = t - (a/b)*y;
    return ret;
}

int main (void) {
    ios_base::sync_with_stdio(false);

	return 0;
}
