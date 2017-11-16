#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
const int INF = 0x3f3f3f3f;

struct state {
	int len;	// Length of Longest Suffix
	int link;	// Suffix Link of the state
	int fpos;	// First element in endpos of this state, endpos.begin()
	map <char, int> next;
};

const int N = 3e5 + 5;
state st[2*N];
int sz, last;

void sa_init() {
	for (int i = 0; i < 2*N; i++)
		st[i].next.clear();
	last = 0;
	sz = 1;
	st[0].len = 0;
	st[0].link = -1;
	st[0].fpos = -1;
}

void sa_extend (char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	st[cur].fpos = st[cur].len - 1;	//fpos
	int p;
	for (p = last; p != -1 and !st[p].next.count(c); p = st[p].link)
		st[p].next[c] = cur;
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].next = st[q].next;
			st[clone].link = st[q].link;
			st[clone].fpos = st[q].fpos;	//fpos
			for (; p != -1 and st[p].next[c] == q; p = st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

void sa_build() {
	sa_init();
	string s;	cin >> s;
	for (int i = 0; i < (int)s.size(); i++)
		sa_extend(s[i]);
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
