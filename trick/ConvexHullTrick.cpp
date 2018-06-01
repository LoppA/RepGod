/* 	dp[i] = min j>i { a[j]*b[i] + dp[j] } 
			varj atual <= varj antigo
(optional)	vari atual >= vari antigo

		vari -> query (x da linha)
		varj -> slope da linha
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> ii;
const double PI = acos(-1.0);

const int N = 1e5 + 5;
int n;
ll a[N], b[N];
ll dp[N];

set <pair <double, int> > s;

void add (double a, double b, int id) {
	set <pair <double, int> >::iterator it = s.end();

	while (it != s.begin()) {
		it--;
		
		int j = it->se;
		double c = ::a[j], d = dp[j];

		double x = (d - b)/(a - c);

		if (x > it->fi) {
			s.insert(mk(x, id));

			it = s.end();	it--;
			while (it->se != id) {
				s.erase(it);
				it = s.end();	it--;
			}

			break;
		}
	}
}

int main (void) {
	ios_base::sync_with_stdio(false);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];

	const double INF = DBL_MAX;
	s.insert(mk(-INF, n-1));
	for (int i = n - 2; i >= 0; i--) {
		double x = b[i];

		set <pair <double, int> >::iterator it = s.upper_bound (mk(x, 0));
		it--;

		int j = it->se;

		dp[i] = a[j] * b[i] + dp[j];

		add (a[i], dp[i], i);
	}

	cout << dp[0] << endl;

	return 0;
}
