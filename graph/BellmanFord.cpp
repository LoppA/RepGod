/* Bellman Ford Algorithm O(VE)	*/

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

const int N = 301;
ll dist[N];
vector <ll> g[N], p[N];
int n;

void NegativeCicle () { }

void BellmanFord (int s) {
	memset (dist, INF, sizeof dist);
	dist[s] = 0;

	for (int i = 0; i < n - 1; i++) 
		for (int at = 0; at < n; at++)
			for (int j = 0; j < (int)g[at].size(); j++) {
				ll next = g[at][j],	w = p[at][j];
				dist[next] = min (dist[next], dist[at] + w);
			}


	for (int at = 0; at < n; at++) 
		for (int j = 0; j < (int)g[at].size(); j++) {
			ll next = g[at][j],	w = p[at][j];
			if (dist[next] > dist[at] + w) 
				NegativeCicle();
		}
}
