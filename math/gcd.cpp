#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd (ll a, ll b) {
	if (!b)
		return a;
	return gcd(b, a%b);
}
