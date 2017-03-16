#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;

const int N = 1e5 + 5;
vector <int> g[N], p[N];
int d[N];

ll go (int s, int t) {
	for (int i = 0; i < N; i++)	d[i] = INF;
	priority_queue <ii, vector <ii>, greater<ii> > pq;

	d[s] = 0;
	pq.push(mk(0,s));

	while (pq.size()) {
		int at = pq.top().se;	int dist = pq.top().fi;
		pq.pop();

		if (at == t)
			return dist;

		for (int i = 0; i < (int)g[at].size(); i++) {
			int next = g[at][i], cost = p[at][i];
			if (dist + cost < d[next]) {
				d[next] = dist + cost;
				pq.push(mk(d[next], next));
			}
		}
	}
	
	return -1;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
