// https://codeforces.com/blog/entry/106851
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

// Phi for a single value n
// phi(n) in O(sqrt(n)), bottleneck is factorization, Pollard rho can optimize.
namespace SingleValuePhi {
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
  
  int getPhi(int n) {
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
}

// Batch phi calculation, calculate from 1 to N-1 in O(n*log(n))
// phi(n) = (p1^e1 - p1^(e1-1)) * (p2^e2 - p2^(e2-1)) ... (pk^ek - pk^(ek-1))
// Above formula can be written as:
// phi(n) = n * (1 - 1/p1) * (1 - 1/p2) ... * (1 - 1/pk)
// O(n*log(n)), can be optimize with linear sieve.
namespace BatchPhi {
  const int N = 5e6 + 5;
  int phi[N];
  void build() {
    for (int i = 1; i < N; i++) {
      phi[i] = i;
    }
   
    for (int i = 2; i < N; i++) {
      if (phi[i] == i) {
        for (int j = i; j < N; j+=i) {
          phi[j] -= phi[j]/i;
        }
      }
    }
  }
}

// phi(n) = (p1^e1 - p1^(e1-1)) * (p2^e2 - p2^(e2-1)) ... (pk^ek - pk^(ek-1))
// phi(n) = (p^e - p^(e-1)) * phi(n/(p^e))
//
// If n = i*p, p being the smallest prime that divides n
//   If i and p are coprimes => phi(n) = phi(p) * phi(i)
//   If p divides i => phi(n) = p * phi(i)
//     Because phi(n) = (p^e - p^(e-1)) * phi(n/(p^e))
//             phi(n) = p * (p^(e-1) - p^(e-2)) * phi(n/p^e)
//             phi(n) = p * phi(n/p^e)
// O(n), using linear sieve.
namespace LinearBatchPhi {
  const int N = 5e6 + 5;
  vector<int> prime;
  int phi[N];

  void build() {
    for (int i = 1; i < N; i++) {
      phi[i] = i;
    }
   
    for (int i = 2; i < N; i++) {
      if (phi[i] == i) {
        prime.pb(i);
        phi[i] = i-1;
      }
      for (int j = 0; j < (int)prime.size() and i*prime[j] < N; j++) {
        if (i%prime[j]) {
          phi[i*prime[j]] = phi[i] * phi[prime[j]];
        } else {
          phi[i*prime[j]] = prime[j] * phi[i];
          break; // we know that i * prime[j + 1] will also have prime[j]
        }
      }
    }
  }
}

int main (void) {
  ios_base::sync_with_stdio(false);
  return 0;
}
