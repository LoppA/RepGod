#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

struct state {
	int len, link;
	int fpos;
	map <char, int> next;
};

const int N = 1e5 + 5;
state st[2*N];
int cnt[2*N];
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

set <pair <int, int> > base;

void sa_extend (char c) {
	int cur = sz++;

	st[cur].len = st[last].len + 1;
	// fpos
	st[cur].fpos = st[cur].len - 1;

	// cnt
	cnt[cur] = 1;
	base.insert(make_pair(st[cur].len, cur));

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
			// fpos
			st[clone].fpos = st[q].fpos;
			for (; p != -1 and st[p].next[c] == q; p = st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;

			//cnt
			cnt[clone] = 0;
			base.insert(make_pair(st[clone].len, clone));
		}
	}
	last = cur;
}

void sa_build() {
	sa_init();
	string s;	cin >> s;
	for (int i = 0; i < (int)s.size(); i++) {
		sa_extend(s[i]);
	}
}

void cnt_build () {
	set<pair <int, int> >::reverse_iterator it;

	for (it = base.rbegin(); it != base.rend(); it++) {
		cnt[st[it->se].link] += cnt[it->se];
	}
}

// Number of ocurrences
int cnt_str (string &p) {
	int s_t = 0, vtx = 0;

	while (s_t < (int)p.size()) {
		vtx = st[vtx].next[p[s_t]];
		s_t++;
	}

	return cnt[vtx];
}

// Position of first occurence
int find_fpos (string &p) {
	int s_t = 0, vtx = 0;

	while (s_t < (int)p.length()) {
		if (!st[vtx].next.count (p[s_t])) {
			// N TEM
			return -1;
		}
		vtx = st[vtx].next[p[s_t]];
		s_t++;
	}

	return st[vtx].fpos - p.size() + 1;
}


int main (void) {
	ios_base::sync_with_stdio(false);

	sa_build();
	cnt_build();

	string p;
	cin >> p;
	cout << cnt_str(p) << endl;
	cout << find_fpos(p) << endl;

	return 0;
}
