#include <bits/stdc++.h>

typedef long long ll;

const int N = 401;
const ll INF = 0x3f3f3f3f;

int adj[N][N];
int v;

void floyd () {
	for (int k = 0; k < v; k++)
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	
}

int main (void) {
	memset(adj, INF, sizeof adj);
	// Ler adjs

	return 0;
}
