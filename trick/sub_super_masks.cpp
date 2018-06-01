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

int bits = 20;

vector <int> submasks (int mask) {
	vector <int> subs;

	for (int x = mask; x; x = (x-1)&mask) 
		subs.pb(x);
	subs.pb(0);

	return subs;
}

vector <int> supermasks (int mask) {
	vector <int> supers;

	int msk = ((1LL<<bits)-1)^mask;
	for (int x = msk; x; x = (x - 1)&msk)
		supers.pb(x | mask);
	supers.pb(mask);

	return supers;
}

vector <int> supermasks2 (int mask) {
	vector <int> supers;

	int msk = ((1LL<<bits)-1)^mask;
	supers = submasks(msk);

	for (int i = 0; i < (int)supers.size(); i++)
		supers[i] |= mask;

	return supers;
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
