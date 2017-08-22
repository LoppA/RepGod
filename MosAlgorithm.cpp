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
const double E = exp(1);

const int N = 1e5 + 5;
int n;
int a[N];
int m;
vector <pair<ii, int> > v;
const int S = sqrt(N);
int res[N];
int ans = 0;

void tira (int i) {
	/*
		Tirar a[i]
	*/
}

void add (int i) {
	/*
		Colocar a[i]
	*/
}

void go () {
	int l = 0, r = 0;

	add(0);
	
	for (int i = 0; i < v.size(); i++) {
		ii p = v[i].fi;
		int id = v[i].se;

		while (r < p.se) {
			r++;
			add(r);
		}

		while (r > p.se) {
			tira(r);
			r--;
		}


		while (l < p.fi) {
			tira(l);
			l++;
		}

		while (l > p.fi) {
			l--;
			add(l);
		}

		res[id] = ans;
	}

}

bool comp (pair<ii, int> p1, pair<ii, int> p2) {
	ii x1, x2;
	x1 = p1.fi;
	x2 = p2.fi;
	if (x1.fi / S != x2.fi / S) return x1.fi / S < x2.fi / S;
	return x1.se > x2.se;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n; i++) 
		cin >> a[i];

	cin >> m;
	for (int i = 0; i < m; i++) {
		int l, r;	cin >> l >> r;
		l--;	r--;
		v.pb(mk(mk(l, r), i));
	}

	sort(v.begin(), v.end(), comp);

	go();

	for (int i = 0; i < m; i++) {
		cout << res[i] << endl;
	}

	return 0;
}
