/* Manacher’s algorithm O(N), time and memory, algorithm to find 
 * longest palindromic substring
 *
 * Transform initial string t into s, 
 * puting separators between characters
 *
 * Build vector p[], where p[i] is the length of the 
 * palindrome centered at s[i]
 *
 * Works for both, odd and even length
 * s: # a # b # a #		# a # a #
 * p: 0 1 0 3 0 1 0		0 1 2 1 0
 *
 * p built in O(N) using the fact that elements can be simetric
 * given some center and p[center]:
 * If we are in i and center c, i_mirror = c - (i - c), if p[i_mirror]
 * fits in center + p[center], p[i] is p[i_mirror], else we need to
 * check real value of p[i]
 * If we call the border center + p[center], r. Its easy to see
 * r is only increased, achieving the O(N) time complexity
 *
 * Longest palindromic substring is the maximum element in p
 *
 * */

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

const int N = 1e6 + 5;
int p[2*N + 2];

int main (void) {
	ios_base::sync_with_stdio(false);

	string s, t;	cin >> t;
	s += "#";
	for (auto c : t) {
		s += c;
		s += '#';
	}

	int n = s.size();
	int c = 0, r = 0;
	for (int i = 0; i < n; i++) {
		int i_mirror = c - (i - c);
		
		if (i <= r)
			p[i] = min (p[i_mirror], r - i);
		else
			p[i] = 0;

		while (i - 1 - p[i] >= 0 and i + 1 + p[i] < n and s[i + 1 + p[i]] == s[i - 1 - p[i]]) {
			p[i]++;
		}

		if (i + p[i] > r) {
			c = i;
			r = i + p[i];
		}
	}

	int len = 0, center = 0;
	for (int i = 0; i < n; i++) 
		if (p[i] > len) {
			len = p[i];
			center = i;
		}

	/* not tested */
	string res;
	for (int i = 0; i < n; i++)
		if (i >= center - len and i <= center + len and s[i] != '#')
			res += s[i];
	/* */

	cout << len << endl;
	cout << res << endl;

	return 0;
}
