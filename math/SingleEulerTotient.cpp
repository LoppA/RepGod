// https://codeforces.com/blog/entry/106851
// phi(n) in O(sqrt(n)), bottleneck is factorization, Pollard rho can optimize.
//
// phi(p^k) = p^k - p^(k-1)
// If gcd(a,b) = 1 then phi(a*b) = phi(a) * phi(b)
//
// Factorizing n, n = p1^e1 * p2^e2 ... pk^ek
// p(n) = phi(p1^e1) * phi(p2^e2) ... phi(pk^ek)
// p(n) = (p1^e1 - p1^(e1-1)) * (p2^e2 - p2^(e2-1)) ... (pk^ek - pk^(ek-1))

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

vector<ii> factorize(int n) {
  vector<ii> v;
  int m = sqrt(n);

  for (int i = 2; i <= m; i++) {
    if (n%i == 0) {
      v.eb(i, 0);
      while(n%i == 0) {
        n /= i;
        v.back().se++;
      }
    }
  }

  if (n > 1) {
    v.eb(n,1);
  }

  return v;
}

int phi(int n) {
  vector<ii> divisors = factorize(n);

  int ans = 1;
  for (auto [prime, exp] : divisors) {
    int power = 1;
    for (int i = 1; i < exp; i++) {
      power *= prime;
    }
    ans *= (power * prime - power); // p^exp - p^(exp-1)
  }

  return ans;
}

int main (void) {
  ios_base::sync_with_stdio(false);

  int T;  cin >> T;
  while(T--) {
    int n;  cin >> n;
    cout << phi(n) << endl;
  }

  return 0;
}
