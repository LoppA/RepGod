/*  Implementacao mais facil pra recuperar o flow
*   
*   MinCut tutorial:
*   
*	Grafo do flow G
*	MinCut: corte de G em S - T, s pertence a S e t pertence a T
*
*	MinCut = MaxFlow
*
*	Todos os vertices alcancaveis por s no grafo residual final
*	pertence a S o resto pertence a T
*
*	As arestas de MinCut sao todas que linhas S a T
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

struct edge {
	int to, cap, flow, rid;

	edge () {}

	edge (int a, int b, int c, int d) : 
		to(a), cap(b), flow(c), rid(d) {}
};

const int N = 111;
vector <edge> g[N];

void add (int a, int b, int c) {
	g[a].pb(edge(b, c, 0, g[b].size()));
	g[b].pb(edge(a, 0, 0, g[a].size() - 1));
}

ii pai[N];
int bfs (int s, int t) {
	for (int i = 0; i < N; i++)
		pai[i] = ii(-1, -1);
	queue <ii> q;
	q.push(ii(s, INF));

	while (!q.empty()) {
		int at = q.front().fi;
		int free = q.front().se;
		q.pop();

		for (int i = 0 ; i < (int)g[at].size(); i++) {
			edge edg = g[at][i];
			if (pai[edg.to].fi == -1 and edg.cap - edg.flow > 0) {
				int f = min(edg.cap - edg.flow, free);
				q.push(ii(edg.to, f));
				pai[edg.to] = ii(at, i);
				if (edg.to == t)
					return f;
			}
		}
	}
	return 0;
}

int max_flow (int s, int t) {
	int ret = 0;
	while (1) {
		int f = bfs (s, t);

		if (!f) break;

		for (int at = t; at != s; at = pai[at].fi) {
			edge &edg = g[pai[at].fi][pai[at].se];
			edg.flow += f;

			edge &redg = g[edg.to][edg.rid];
			redg.flow -= f;
		}

		ret += f;
	}
	return ret;
}

bool vis[N];
void find_MinCut (int at) {
	vis[at] = 1;

	for (int i = 0; i < (int)g[at].size(); i++) {
		edge edg = g[at][i];
		int next = edg.to;
		if (pai[next].fi == -1) 
			cout << at << " " << next << endl;
		else if (!vis[next])
			find_MinCut (next);
	}
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
