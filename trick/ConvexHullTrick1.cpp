/* dp[i] = min j<i {dp[j] + a[j] * x[i]}
 * conditions:
 *     x[i] < x[i+1]: erase lines with minimun value smaller than x[i]
 *     a[j] > a[j+1]: put new line in the end
 *
 * code example for problem: http://www.spoj.com/problems/ACQUIRE/
 * */
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<ll, ll> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);

const int N = 5e4 + 4;
ll n, w[N], h[N];
ll dp[N];

double inter(ii p1, ii p2) {
	ll a = p1.fi;
	ll b = p1.se;

	ll c = p2.fi;
	ll d = p2.se;

	return (double)(d-b)/(double)(a-c);
}

int main (void) {
	ios_base::sync_with_stdio(false);

	cin >> n;
	vector<ii> ve;
	for(int i = 0; i < n; i++) {
		int a, b;	cin >> a >> b;
		ve.eb(a, b);
	}
	sort(ve.begin(), ve.end());

	w[0] = ve[0].fi;
	h[0] = ve[0].se;
	n = 0;

	for(int i = 1; i < (int)ve.size(); i++) {
		ll W = ve[i].fi;
		ll H = ve[i].se;

		while(n >= 0 and h[n] <= H) 
			n--;

		n++;
		w[n] = W;
		h[n] = H;
	}
	n++;

	for(int i = 0; i < n - 1; i++)
		assert(w[i] <= w[i+1]);
	for(int i = 0; i < n - 1; i++)
		assert(h[i] > h[i+1]);

	deque<pair<ii, double> > s;
	deque<pair<ii, double> >::iterator it1, it2;
	const double inf = 1e18;
	s.eb(ii(h[0], 0), inf);
	for(int i = 0; i < n; i++) {
		while(w[i] > s.begin()->se)
			s.pop_front();

		ll a = s.begin()->fi.fi;
		ll b = s.begin()->fi.se;
		dp[i] = a*w[i] + b;

		while(s.size() > 1) {
			it2 = --s.end();
			it1 = it2;	it1--;

			if(inter(it1->fi, it2->fi) < inter(it1->fi, ii(h[i+1], dp[i]))) {
				break;
			} else {
				s.pop_back();
			}
		}
		s.rbegin()->se = inter(s.rbegin()->fi, ii(h[i+1], dp[i]));
		s.eb(ii(h[i+1], dp[i]), inf);
	}

	cout << dp[n-1] << endl;

	return 0;
}
