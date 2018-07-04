/*	
	border = proper prefix that is suffix
	p[i] = length of longest border of prefix of length i, s[0...i-1]
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);

const int N = 1e6 + 6;
int pi[N];
string p, t;

void pre () {
	p += '#';

	pi[0] = pi[1] = 0;
	for (int i = 2; i <= (int)p.size(); i++) {
		pi[i] = pi[i-1];

		while (pi[i] > 0 and p[pi[i]] != p[i-1])
			pi[i] = pi[pi[i]];

		if (p[pi[i]] == p[i-1])
			pi[i]++;
	}
}

void report (int at) {

}

void KMP () {
	pre ();

	int k = 0;
	int m = p.size() - 1;

	for (int i = 0; i < (int)t.size(); i++) {
		while (k > 0 and p[k] != t[i])
			k = pi[k];
		
		if (p[k] == t[i])
			k++;
		if (k == m)
			report (i - m + 1);
	}

}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
