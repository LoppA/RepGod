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

struct node {
	node *child[2], *p;
	bool reverse;
	ll val, size, sum;

	node () {
		child[0] = child[1] = p = NULL;
		reverse = false;
		val = size = sum = 0LL;
	}
};

node *v[N];

struct splay_tree {
 	node *root, *null;

	splay_tree () {
		root = null = new node();
	}

	void update (node *at) {
		at->size = at->child[0]->size + at->child[1]->size + 1;
		at->sum = at->child[0]->sum + at->child[1]->sum + at->val;
	}

	void set_link (node *p, node *c, int d) {
		c->p = p;
		p->child[d] = c;
	}

	void rotate (node *at, int d) {
		node *c = at->child[d], *p = at->p;
		set_link (at, c->child[1 - d], d);
		set_link (c, at, 1 - d);
		set_link (p, c, get_dir(p, at));
		update(at);	update(c);
	}

	int get_dir (node *p, node *c) {
		return p->child[0] == c ? 0 : 1;
	}

	void splay (node *at) {
		while (at->p != null) {
			node *p = at->p, *g = p->p;
			int dirp = get_dir(p, at), dirg = get_dir(g, p);
			if (g == null) rotate(p, dirp);
			else if (dirp == dirg)	rotate(g, dirg), rotate(p, dirp);
			else	rotate(p, dirp), rotate(g, dirg);
		}
	}

	node* build (int *a, int l, int r) {
		if (l > r)	return null;
		int mid = (l + r)>>1;

		node *at = new node();
		at->val = a[mid];
		at->p = null;
		at->child[0] = build(a, l, mid - 1);
		at->child[1] = build(a, mid + 1, r);
		at->child[0]->p = at->child[1]->p = at;

		v[a[mid]] = at;

		update(at);

		return at;
	}
} st;

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
