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
const int LOG = 20;
vector <int> g[N];

class LCA {
public:
	int pai[N][LOG], dist[N];

	void build (int curr){
		for (int i = 1; i < LOG; i++){
				pai[curr][i] = pai[pai[curr][i-1]][i-1];
		}
	}

	void ini (int curr, int last, int d){
		dist[curr] = d;
		pai[curr][0] = last;
		build (curr);

		for (unsigned int i = 0; i < g[curr].size(); i++){
				int next = g[curr][i];
				if (next != last) ini (next, curr, d+1);
		}
	}


	int query (int u, int v){
		if (dist[v] < dist[u])
		swap(v,u);

		while (dist[u] < dist[v]){
				int i = 0;
				while (dist[pai[v][++i]] > dist[u]);
				v = pai[v][i-1];
		}
		if (u == v) return u;

		while (pai[u][0] != pai[v][0]){
				int i = 0;
				while (pai[v][i] != pai[u][i]){
						i++;
				}
				v = pai[v][i-1];
				u = pai[u][i-1];
		}
		return pai[v][0];
	}
};

