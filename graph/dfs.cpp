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

const int N = 1e3 + 3;

class Digrafo {
public: 
	bool vis[N];
	int entra[N], sai[N], low[N], comp[N];
	vector <int> g[N];
	stack <int> st;
	int ncp, t;

	Digrafo() {
		memset(vis, 0, sizeof vis);
		ncp = 0;	t = 0;
	}

	void dfs (int at) {
		vis[at] = true;
		entra[at] = low[at] = t++;
		st.push(at);

		for (int next : g[at]) 
			if (!vis[next]) {
				dfs(next);
				low[at] = min(low[at], low[next]);
			} else 
				low[at] = min(low[at], entra[next]);

		if (low[at] == entra[at]) {
			int a;
			do {
				a = st.top();	st.pop();
				comp[a] = ncp;
				entra[a] = INF;
			} while (a != at);
			ncp++;
		}

		sai[at] = t++;
	}
};

class Grafo {
public:
	bool vis[N];
	vector <int> g[N];
	int entra[N], sai[N], low[N];
	int t;

	Grafo () {
		memset(vis, 0, sizeof vis);
		t = 0;
	}

	void ponte (int u, int v) {

	}

	void vertice_corte (int u) {

	}

	void dfs (int at, int pai) {
		vis[at] = true;
		low[at] = entra[at] = t++;
		int filhos = 0;
		bool f = false;

		for (int next : g[at]) 
			if (!vis[next]) {
				dfs(next, at);
				filhos++;
				if (low[next] >= entra[at])
					f = true;
				low[at] = min(low[next], low[at]);
				if (low[next] > entra[at])
					ponte(at, next);
			} else if (next != pai) {
				low[at] = min(low[at], entra[next]);
			}
		
		if (pai == -1) {
			if (filhos >= 2) vertice_corte(at);
		} else 
			if (f)	vertice_corte(at);

		sai[at] = t++;
	}

	/*retorna true se v eh ancestral de u*/
	bool ancestral (int v, int u) {
		return (entra[v] < entra[u] and sai[u] < sai[v]);
	}
};

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
