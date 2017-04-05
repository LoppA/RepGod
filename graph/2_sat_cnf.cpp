/* 2 SAT 2 CNF O(N + M)	

	2 SAT:
		(a V b):
			not a => b
			not b => a

	2 CNF:
		(a implies b):
			a => b
			not b => not a
		(a implies b): (not a V b)

OBS: define N as 2*n, n is the number of variables
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
const double E = exp(1);

const int N = 2e5 + 3;

bool vis[N];
int entra[N], sai[N], low[N], comp[N];
vector <int> g[N];
stack <int> st;
int ncp, t;

void init () {
	for (int i = 0; i < N; i++)
		g[i].clear();
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

// id x = 2*x
// id not x = 2*x + 1
int id (int x, bool n) {
	return 2*x + n;
}

// na == 0, var: a
// na == 1, var: not a
void add_or (int a, bool na, int b, bool nb) {
	g[id(a, !na)].pb(id(b, nb));
	g[id(b, !nb)].pb(id(a, na));
}

// na == 0, var: a
// na == 1, var: not a
void add_implies (int a, bool na, int b, bool nb) {
	add_or (a, !na, b, nb);
}

void no () {
	cout << "Impossible" << endl;
	exit(0);
}

int n;
int ans[N];

int main (void) {
	ios_base::sync_with_stdio(false);

	init ();

	for (int i = 0; i < 2*n; i++) 
		if (!vis[i])
			dfs (i);
	
	//  if comp[x] == comp[not x] there is no answer
	//	if there is a path from v to w, comp[v] > comp[w]
	for (int i = 0; i < n; i++) 
		if (comp[2*i] == comp[2*i + 1])
			no ();
		else if (comp[2*i] < comp[2*i + 1]) 
			ans[i] = true;
		else 
			ans[i] = false;

	return 0;
}
