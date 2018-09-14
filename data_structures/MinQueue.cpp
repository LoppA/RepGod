/* MinQueue that stores a maximum of k elements */
#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);

struct minq {
	deque<ii> v;
	int t, k;

	minq(int k) : k(k) {}

	void clear() {
		v.clear();
		t = 0;
	}

	void insert(int at) {
		while(v.size() and (v.rbegin())->fi >= at)
			v.pop_back();

		v.pb(ii(at, t++));

		while(v.size() and (v.rbegin())->se - (v.begin())->se >= k)
			v.pop_front();
	}

	int min() {
		if(!v.size())	return INF;
		return v.begin()->fi;
	}
};

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
