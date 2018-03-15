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

const int N = 1e5 + 5;
vector <int> g[N];
int n, sub[N];
bool cent[N];

// Calcula sub
int dfs (int at, int pai) {
	sub[at] = 1;

	for (int next : g[at]) {
		if (next == pai or cent[next])	continue;
		sub[at] += dfs (next, at);
	}

	return sub[at];
}

// acha centroid
int find_centroid (int at, int pai, int total) {
	int mx = 0;

	for (int next : g[at]) {
		if (next == pai or cent[next])	continue;
		mx = max (sub[next], mx);
	}

	if (2*mx <= total)
		return at;

	for (int next : g[at]) {
		if (next == pai or cent[next])	continue;
		if (sub[next] == mx) 
			return find_centroid (next, at, total);
	}

	return -1;
}

void go (int at) {
	int total = dfs (at, -1);
	at = find_centroid (at, -1, total);
	if (at == -1)	return;
	cent[at] = 1;

	// centroid eh o at agora

	// vai para as proximas subtrees
	for (int next : g[at]) 
		if (!cent[next])
			go (next);
			
	cent[at] = 0;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
