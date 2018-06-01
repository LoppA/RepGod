/* Divide & Conquer Trick
 * dp[i] = min k<i {dp[k] + c[k][i]}
 * opt[i-1] <= opt[i] <= opt[i+1]
 *
 * opt property is true if quadrangulaer iniquality holds:
 *    a <= b <= c <= d
 *    c[a][c] + c[b][d] <= c[a][d] + c[b][c]
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

const int N = 4123, M = 812;
int n, m, u[N][N], c[N][N];
int dp[M][N];

int cost(int a, int b) {
	int ret = c[b][b];

	if(a) {
		ret -= c[a-1][b] + c[b][a-1];
		ret += c[a-1][a-1];
	}

	return ret;
}

void go(int m, int l, int r, int optl, int optr) {
	if(l > r)	return;
	int i = (l + r)>>1;

	int opt = optl;
	dp[m][i] = INF;
	for(int k = optl; k <= optr and k < i; k++) {
		int at = dp[m-1][k] + (cost(k+1, i)>>1);
		if(at < dp[m][i]) {
			dp[m][i] = at;
			opt = k;
		}
	}

	go(m, l, i - 1, optl, opt);
	go(m, i + 1, r, opt, optr);
}

int main (void) {

	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			char ch;
			getchar();
			ch = getchar();
			u[i][j] = ch - '0';
		}

	for(int j = 1; j <= n; j++) 
		c[0][j] = c[0][j-1] + u[0][j];

	for(int i = 1; i <= n; i++) {
		int at = 0;
		for(int j = 1; j <= n; j++) {
			at += u[i][j];
			c[i][j] = c[i-1][j] + at;
		}
	}

	for(int i = 1; i <= n; i++)
		dp[0][i] = INF;
	dp[0][0] = 0;

	for(int i = 1; i <= m; i++) 
		go(i, 1, n, 0, n-1);

	printf("%d\n", dp[m][n]);

	return 0;
}
