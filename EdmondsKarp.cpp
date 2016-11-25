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

const int N = 202;

struct Flow {
public:
	int n, m;
	int pai[N];
	int flow[N][N], cap[N][N];
	vector <int> g[N];

	Flow () {
		memset (flow, 0, sizeof flow);
		memset (cap, 0, sizeof cap);
		for (int i = 0; i < N; i++) 
			g[i].clear();
	}

	void edge (int a, int b, int c) {
		g[a].pb(b);
		g[b].pb(a);
		cap[a][b] += c;
	}

	Flow (int n, int m) {
		*(this) = Flow ();
		this->n = n;	this->m = m;
		for (int i = 0; i < m; i++) {
			int a, b, c;	cin >> a >> b >> c;
			if (a == b) continue;
			edge (a, b, c);
		}
	}

	void bfs (int s, int t) {
		queue <int> q;
		q.push(s);

		while (!q.empty()) {
			int at = q.front();	q.pop();
			for (int i = 0; i < (int)g[at].size(); i++) {
				int next = g[at][i];
				if (cap[at][next] > 0 and pai[next] == -1) {
					pai[next] = at;
					q.push(next);
					if (next == t) return;
				}
			}
		}

	}

	int go (int s, int t) {	
		while (1) {
			memset (pai, -1, sizeof pai);
			bfs(s, t);

			if(pai[t] == -1) {
				int ret = 0;
				for (int i = 0; i <= n; i++) 
					ret += flow[i][t];
				return ret;
			}

			int f = INF;
			int a = t;

			while (a != s) {
				int b = a;
				a = pai[b];
				f = min(f, cap[a][b]);
			}

			a = t;
			while (a != s) {
				int b = a;
				a = pai[b];
				flow[a][b] += f;
				cap[a][b] -= f;
				cap[b][a] += f;
			}
		}
	}

} F;

int main (void) {
	ios_base::sync_with_stdio(false);

	int n, m, s, t;
	while (cin >> n >> m >> s >> t) {
		F = Flow (n, m);
		cout << F.go(s, t) << endl;
	}

	return 0;
}
