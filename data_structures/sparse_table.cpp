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

const int N = 1e5 + 5, LOG = 20;
int n, a[N];

int lg[N];
struct SparseTable {
	int n, table[N][LOG];

	SparseTable () {}

	SparseTable (int n) : n(n) {
		for (int i = 0; i < n; i++)
			table[i][0] = a[i];

		for (int j = 1; (1<<j) < n; j++) 
			for (int i = 0; i + (1<<j) - 1 < n; i++)
				table[i][j] = min (table[i][j-1], table[i + (1<<(j-1))][j-1]);
	}

	int query (int l, int r) {
		if (l > r)	swap (l, r);
		int tam = r - l + 1;

		return min (table[l][lg[tam]], table[r - (1<<lg[tam]) + 1][lg[tam]]);
	}
	
} st;

int main (void) {
	ios_base::sync_with_stdio(false);

	lg[1] = 0;
	for (int i = 2; i < N; i++) {
		lg[i] = lg[i-1];
		if ((1<<(lg[i] + 1)) == i)
			lg[i]++;
	}

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	st = SparseTable(n);

	int q;	cin >> q;
	while (q--) {
		int l, r;	cin >> l >> r;
		cout << st.query (l, r) << endl;
	}

	return 0;
}
