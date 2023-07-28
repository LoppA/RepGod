// https://cp-algorithms.com/algebra/primality_tests.html#deterministic-version
// https://cp-algorithms.com/algebra/factorization.html#implementation_1
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef __int128 LL;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);

ll exp(LL x, ll y, ll mod) {
  ll r = 1;
  x %= mod;

  while(y) {
    if (y&1)
      r = (x*r)%mod;
    x = (x*x)%mod;
    y >>= 1;
  }

  return r;
}

// Fermat's little theorem: a^(n-1) = 1 % n
// n-1 = 2^s * d
// a^(n-1) = 1 mod n
// a^(2^s * d) - 1 = 0 mod n
// (a^(2^(s-1)d + 1)(a^(2^(s-2)d + 1)...(a^(2^d) + 1)(a^(2^d) - 1) = 0 mod n
// If none of these terms are equal 0 mod n, we are sure that n is not a prime.
// Otherwise n is **likely** a prime, need to try with other bases a.
bool checkComposite(ll n, ll a, ll d, int s) {
  ll x = exp(a, d, n);

  if (x == 1 or x == n-1)
    return false;

  for (int r = 1; r < s; r++) {
    x = ((LL)x*x)%n;
    if (x == n-1)
      return false;
  }

  return true;
}

// Returns true if n is prime, else returns false.
bool millerRabin(ll n) {
  if (n < 2)
    return false;

  // n-1 = (2^s)*d;
  int s = 0;
  ll d = n-1;
  while((d&1) == 0) {
    d >>= 1;
    s++;
  }

  // Checking all base a <= 2ln(n)^2 is enough
  // But for a 64 bit integer, the first 12 primes work.
  // For 32 bit integer the first 4 primes work {2, 3, 5, 7}.
  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a)
      return true;
    if (checkComposite(n, a, d, s))
      return false;
  }
  return true;
}

ll rho(const ll n, const ll x0=2, const ll c=1) {
  if (n == 1) return 1;

  auto f = [&c, &n](LL x) {
    return (x*x + c)%n;
  };

  auto mult = [&n](LL a, ll b) {
    return (a*b)%n;
  };

  ll x = x0;
  ll g = 1;
  ll q = 1;
  ll xs, y;

  int m = 128;
  int l = 1;
  while(g == 1) {
    y = x;
    for (int i = 1; i < l; i++)
      x = f(x);

    int k = 0;
    while (k < l && g == 1) {
      xs = x;
      for (int i = 0; i < m && i < l-k; i++) {
        x = f(x);
        q = mult(q, abs(y-x));
      }
      g = gcd(q, n);
      k += m;
    }

    l *= 2;
  }

  if (g == n) {
    do {
      xs = f(xs);
      g = gcd(abs(xs - y), n);
    } while(g == 1);
  }

  return g;
}

int main (void) {
  ios_base::sync_with_stdio(false);

  return 0;
}
