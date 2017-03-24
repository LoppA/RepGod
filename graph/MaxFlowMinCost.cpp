/* O(V^2 * E * log(V))*/

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
	int to, cost, cap, flow, rid;

	edge () {}

	edge (int a, int b, int c, int d, int e) : 
		to(a), cost(b), cap(c), flow(d), rid(e) {}
};

const int N = 111;
vector <edge> g[N];
int n;

void add (int a, int b, int cost, int cap) {
	g[a].pb(edge(b, cost, cap, 0, g[b].size()));
	g[b].pb(edge(a, -cost, 0, 0, g[a].size() - 1));
}

int h[N];
/*negative edges*/
void bellman_ford (int s) {
	memset (h, INF, sizeof h);
	h[s] = 0;
	for (int i = 0; i < n - 1; i++) 
		for (int at = 0; at < n; at++) 
			for (int j = 0; j < (int)g[at].size(); j++) {
				if (!g[at][j].cap)	continue;
				int next = g[at][j].to, w = g[at][j].cost;
				h[next] = min (h[next], h[at] + w);
			}
}

ii pai[N];
int dist[N];
int dijkstra (int s, int t) {
	memset (dist, INF, sizeof dist);
	for (int i = 0; i < N; i++)
		pai[i] = ii(-1, -1);
	priority_queue <ii, vector <ii>, greater<ii> > pq;

	dist[s] = 0;
	pq.push(ii(0, s));

	bool ret = false;
	while (pq.size()) {
		int at = pq.top().se;
		pq.pop();

		if (at == t) {
			ret = true;
			break;
		}

		for (int i = 0; i < (int)g[at].size(); i++) {
			edge edg = g[at][i];
			int next = edg.to;
			if (edg.cap - edg.flow <= 0)	continue;
			ll w = dist[at] + edg.cost + h[at] - h[next];
			if (dist[next] > w) {
				dist[next] = w;
				pai[next] = ii(at, i);
				pq.push(ii(dist[next], next));
			}
		}
	}

	for (int i = 0; i < N; i++)
		h[i] += dist[i];

	return ret;
}

ii max_flow (int s, int t) {
	int cost = 0, flow = 0;
	bellman_ford(s);

	while (dijkstra(s, t)) {
		int f = INF;
		for (int at = t; at != s; at = pai[at].fi) {
			edge edg = g[pai[at].fi][pai[at].se];
			f = min (f, edg.cap - edg.flow);
		}
		flow += f;
		for (int at = t; at != s; at = pai[at].fi) {
			edge &edg = g[pai[at].fi][pai[at].se];
			edg.flow += f;
			g[edg.to][edg.rid].flow -= f;
			cost += edg.cost;
		}
	}

	return mk(cost, flow);
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
