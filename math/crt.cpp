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

// ax + by = g
// g = 1 for a and b coprimes
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
 
const ll mul(ll x, ll y, ll mod) {
  ll ret = 0;
 
  if(x<0) x+= mod;
  if(y<0) y+= mod;
 
  while(y) {
    if(y&1)
      ret = (ret+x)%mod;
    x = (x<<1)%mod;
    y >>= 1;
  }
 
  return ret;
}
 
inline ll mul(ll a, ll b, ll c, ll mod) {
  a %= mod;
  b %= mod;
  c %= mod;
  ll x = mul(a, b, mod);
  return mul(x, c, mod);
}
 
ll go(ll a0, ll p0, ll a1, ll p1) {
  ll m0, m1;
  gcd(p0, p1, m0, m1);
 
  assert(p0*m0 + p1*m1 == 1);
 
  return mul(a0, p1, m1, (p0*p1)) + mul(a1, p0, m0,(p0*p1));
}
 
ll crt(const vector<ll> &a, const vector<ll> &p) {
  assert(a.size() == p.size());
  int n = a.size();
 
  ll _a = a[0];
  ll _p = p[0];
 
  for(int i = 1; i < n; i++) {
    _a = go(_a, _p, a[i], p[i]);
    _p *= p[i];
    _a %= _p;
    if(_a < 0)  _a += _p;
  }
 
  return _a;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
