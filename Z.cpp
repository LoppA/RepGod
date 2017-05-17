/*          {0, if i = 0
    z[i] =  {length longest commom prefix of s and s[i...n-1]
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

const int N = 2e5 + 5;
string s;
int z[N];

void go () {
	int l = 0, r = 0;
	int n = s.size();
	memset (z, 0, sizeof z);

	for (int i = 1; i < n; i++) {
		if (i <= r)
			z[i] = min (z[i-l], r - i + 1);
		while (z[i] + i < n and s[z[i] + i] == s[z[i]])
			z[i]++;
		if (r < i + z[i] - 1) {
			l = i;
			r = i + z[i] - 1;
		}
	}
}

int main (void) {

	return 0;
}
