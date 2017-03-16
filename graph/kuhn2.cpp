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

const int N = 1e4 + 4;
int n;
int mt[N], nt[N];
bool vis[N];
vector <int> g[N];

bool kuhn (int at) {
	if (vis[at])	return false;
	vis[at] = 1;

	for (auto next : g[at]) 
		if (mt[next] == -1) {
			mt[next] = at;
			nt[at] = next;
			return true;
		}

	for (auto next : g[at]) 
		if (kuhn(mt[next])) {
			mt[next] = at;
			nt[at] = next;
			return true;
		}

	return false;
}

int max_matching () {
	memset (mt, -1, sizeof mt);
	memset (nt, -1, sizeof nt);

	int mm = 0;

	bool updated = true;
	while (updated) {
		updated = false;
		memset (vis, 0, sizeof vis);

		for (int i = 0; i < n; i++) 
			if (nt[i] == -1 and kuhn(i)) {
				mm ++;
				updated = true;
			}
	}

	return mm;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
