// https://codeforces.com/blog/entry/54090
// A composite number q, can be written as
// q = i*p, where p is the smallest prime that divides it.
// From that we know
//   1. i >= p
//   2. Any prime < p can't divide i
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

const int N = 1e6 + 6;
vector<int> p;
bool vis[N];

void sieve() {
  for (int i = 2; i < N; i++) {
    if (!vis[i])  p.pb(i);
    for (int j = 0; j < p.size() and i*p[j] < N; j++) {
      vis[i*p[j]] = true;
      if (i%p[j]==0)  break; // we know that i * prime[j + 1] will also have prime[j] as the smallest prime divisor.
    }
  }
}

int main (void) {
  ios_base::sync_with_stdio(false);
  sieve();
  return 0;
}
