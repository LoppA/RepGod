/* Build Suffix Automata of string S
 * aciclic graph where nodes are called states and edges
 * between states have char labels, a path in the automata
 * listing all edge labels defines a substring, all substrings
 * are defined exactly once in the automata
 *
 * build time and space: O(N = length(S))
 *
 * Endpos(T): set of all positions where T ends in S
 * 	if u is suffix of w -> Endpos(w) C Endpos(u)
 * 	else				-> Endpos(w) /\ Endpos(u) = {}
 *
 * Same class: Endpos(u) == Endpos(v)
 * sort all strings of same class, the of lengths difference between
 * consective strings is 1, and one string is suffix of all others
 * with greatest length
 *
 * Number of states is equal to the number of endpos classes
 *
 * Links
 * 	w is the longest string in state v.
 * 	suffix link of v is the state that contains the longest suffix of w
 * 	that is in different endpos class
 * 	Properties:
 * 		minlen(v) = len(link(v)) + 1
 * 		endpos(v) C (endpos(link(v))
 *
 *
 * Construction of Suffix Automaton:
 *	1: It is online, we construct by adding a single character to our 
 *	previous string
 *	2: Initial state: id = 0, len = 0, link = -1
 *	3: Add a single caracter c to the end of the current line
 *	4: Last is the state that corresponds to the entire line
 *	before adding the symbol (initially Last = 0)
 *	5: When adding a new caracter we will make state Cur
 *	adding a new character increase the number of  endpos classes by 
 *	at least 1 as no previous substring can end at the position of c
 *	len(Cur) = len(Last) + 1
 *   Finding suffix-link and modifing the tree, loop:
 *   Find suffix of Last with edge with label c, (it points to suffix of Cur).
 *    1: we are at node Last, we add edge between Last and Cur with label c
 *    and move to suffix link of Last, until we reach state 0 or if edge
 *    with label c already exists
 *    2: if at some state P, edge with label c already exists, we stop at P.
 *    Q is the state connected to P via c. Q needs to be suffix of Cur.
 *     - if len(P) + 1 == len(Q), link(Cur) = Q, break
 *     - otherwise we have to create a clone of state Q with everithing
 *     the same, except for len(Clone) = len(p) + 1 ans assing
 *     link(Cur) = Clone, assigin edge with label c, fora all
 *     P in suffix tree to Clone, break
 *    3: if 2 never happened, we are at dummy state -1, assing link(Cur) = 0
 * */

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef long long ll;
const int INF = 0x3f3f3f3f;

const int N = 1e4 + 5;

struct SuffixAutomaton {
	struct state {
		int len;	// Length of Longest Suffix
		int link;	// Suffix Link of the state
		int fpos;	// First element in endpos of this state, endpos.begin()
		map <char, int> next;
	};

	state st[2*N];
	int sz, last;

	SuffixAutomaton () {}

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
};

/* Longest commom prefix of k substrings
 *
 * b will be the base string, other k-1 will be processed
 *
 * Find longest suffix of each other string that apears as
 * a prefix [0 ... i] of b, for each i, using suffix links
 * Take the mininum of each processed string at each step, 
 * (it is the maximum commom suffix for each prefix i), 
 * answer is the maximum in all steaps
 * */
namespace Longest_k_commom_substring {
	const int K = 10;
	SuffixAutomaton sa[K];
	int at[K], len[K];

	void main () {
		int k;	cin >> k;	k--;
		memset (at, 0, sizeof at);
		memset (len, 0, sizeof len);
		for (int i = 0; i < k; i++)
			sa[i].sa_build();

		string b;	cin >> b;
		if (!k) {
			cout << b.size() << endl;
			return;
		}

		int res = 0;
		for (auto c : b) {
			int r = INF;
			for (int j = 0; j < k; j++) {
				while (at[j] and !sa[j].st[at[j]].next.count(c)) {
					at[j] = sa[j].st[at[j]].link;
					len[j] = sa[j].st[at[j]].len;
					// in this case len will always decrease because
					// len[link[p]] + 1 = minimal string length in class p
					// so len[link[p]] < length we got at this time increasing,
					// so this is the length of some string in at[j] class
				}

				// found some suffix with edge with label c
				// otherwise we just got empty suffix
				if (sa[j].st[at[j]].next.count(c)) {
					at[j] = sa[j].st[at[j]].next[c];
					len[j]++;
				}
				r = min (r, len[j]);
			}
			res = max (res, r);
		}

		cout << res << endl;
	}
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
