/* Build Suffix Automata of string S
 * aciclic graph where nodes are called states and edges
 * between states have char labels, a path in the automata
 * listing all edge labels defines a substring, all substrings
 * are defined exactly once in the automata
 *
 * build time and space: O(N = length(S))
 *
 * Endpos(T): set of all positions where T ends in S
 * 	if u is suffix of w -> Endpos(w) C Endpos(u), 
 * 	Endpos(w) is contained inside Endpos(u)
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
 *
 *
 * Summary:
 *  Contains_substring
 *  Number_of_different_substrings
 *  Kth_smallest_distinct_substring
 *  Smallest_cyclic_shift
 *  Shortest_not_included_string
 *  Longest_2_commom_substring
 *  Number_of_occurrences
 *  Position_first_occurrence 
 *  Position_of_all_occurrences
 *  in_a_not_in_b
 * */

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

/* Just walk through the automata */
namespace Contains_substring {
	bool go (string &p) {
		int at = 0;

		for (auto c : p) 
			if (!st[at].next.count(c))
				return false;
			else
				at = st[at].next[c];

		return true;
	}

	void main () {
		sa_build();

		int q;	cin >> q;
		while (q--) {
			string p;	cin >> p;

			if (go(p))
				cout << 'Y' << endl;
			else
				cout << 'N' << endl;
		}
	}
}

/* Find the number of diffrent paths with is equal to the number
 * of different substrings	*/
namespace Number_of_different_substrings {
	ll dp[2*N];

	ll go (int at) {
		ll &r = dp[at];
		if (r != -1)	return r;

		r = 1;
		for (auto it : st[at].next) 
			r += go (it.se);

		return r;
	}

	void main () {
		sa_build();
		memset (dp, -1, sizeof dp);
		// decrease 1 to disconsider empty substring
		cout << go (0) - 1LL << endl;
	}
}

/* Pick smallest possible edge that we can 
 * go to next state	*/
namespace Kth_smallest_distinct_substring {
	void go (int at, int k) {
		if (k <= 0)	return;

		for (auto it : st[at].next) {
			ll dp = Number_of_different_substrings::dp[it.se];

			if (dp >= k) {
				cout << it.fi;
				go (it.se, k - 1);
				return;
			} else {
				k -= dp;
			}
		}
	}

	void main () {
		sa_build();
		memset (Number_of_different_substrings::dp, -1, 
				sizeof Number_of_different_substrings::dp);
		Number_of_different_substrings::go(0);

		int T;	cin >> T;
		while (T--) {
			int k;	cin >> k;
			// Print kth smallest substring
			go (0, k);
			cout << endl;
		}
	}
}

/* Suffix automaton over s + s, find smallest substring with len = len(s) */
namespace Smallest_cyclic_shift {
	int slen;
	void sa_build() {
		sa_init();
		string s;	cin >> s;
		slen = s.size();
		s += s;
		for (int i = 0; i < (int)s.size(); i++)
			sa_extend(s[i]);
	}

	// Find maximun length we can get starting by state "at"
	int dp[2*N];
	int go (int at) {
		int &r = dp[at];
		if (r != -1)	return r;

		r = 1;
		for (auto it : st[at].next)
			r = max (r, go (it.se) + 1);
		return r;
	}

	void solve (int at, int len) {
		if (!len) {
			// one based
			cout << (st[at].fpos - slen + 1) + 1 << endl;
			return;
		}

		// pass though edges in label order
		for (auto it : st[at].next) 
			if (dp[it.se] >= len - 1) {
				solve (it.se, len - 1);
				return;
			}
	}

	void main () {
		sa_build();
		memset (dp, -1, sizeof dp);
		go (0);
		solve (0, slen);
	}
}

/* Shorstest string (in length), then if multople has same length
 * get the lexicographicaly smallest
 * */
namespace Shortest_not_included_string {
	// find minimun not included string we can find
	// from this state
	int dp[2*N];
	int go (int at) {
		int &r = dp[at];
		if (r != INF)	return r;

		if (st[at].next.size() < 'Z' - 'A' + 1)
			return r = 1;

		for (auto it : st[at].next) 
			r = min (r, go(it.se) + 1);

		return r;
	}

	// find small lexicographically
	// print answer
	void solve (int at) {
		for (char c = 'A'; c <= 'Z'; c++) {
			if (!st[at].next.count(c)) {
				cout << c;
				return;
			}
		}

		for (char c = 'A'; c <= 'Z'; c++) {
			int nx = st[at].next[c];
			if (dp[at] == dp[nx] + 1) {
				cout << c;
				solve (nx);
				return;
			}
		}
	}

	void main () {
		sa_build();
		memset (dp, INF, sizeof dp);
		go (0);
		solve (0);
		cout << endl;
	}
}

/* Longest commom prefix of two substrings
 *
 * b will be the base string, other string will be processed
 *
 * Find longest suffix of processed string that apears as
 * a prefix [0 ... i] of b, for each i, using suffix links
 * answer is the maximum in all steaps
 * */
namespace Longest_2_commom_substring {

	void main () {
		sa_build();
		string b;	cin >> b;

		int res = 0;
		int at = 0, len = 0;

		for (auto c : b) {
			while (at and !st[at].next.count(c)) {
				at = st[at].link;
				len = st[at].len;
				// in this case len will always decrease because
				// len[link[p]] + 1 = minimal string length in class p
				// so len[link[p]] < length we got at this time increasing,
				// so this is the length of some string in at[j] class
			}

			// found some suffix with edge with label c
			// otherwise we just got empty suffix
			if (st[at].next.count(c)) {
				at = st[at].next[c];
				len++;
			}
			res = max (res, len);
		}

		cout << res << endl;
	}
}

/* Find substrings number of occurrences
 *
 * Same class have the same number of occurrences
 *
 * Algorithm: count number of times a state is prefix
 * of a suffix, (all suffixes are terminal states, terminal
 * state is the last state and his link path, suffixes of it)
 * */
namespace Number_of_occurrences {
	int dp[2*N];
	int terminal[2*N];

	// mark terminal states
	void mark () {
		memset (terminal, 0, sizeof terminal);
		int at = last;

		while (at != -1) {
			terminal[at] = true;
			at = st[at].link;
		}
	}

	// calculate
	int go (int at) {
		int &r = dp[at];
		if (r != -1)	return r;

		r = terminal[at];

		for (auto it : st[at].next) 
			r += go (it.se);

		return r;
	}

	// get answer for a pattern p
	int get (string &p) {
		int at = 0;

		for (auto c : p) {
			if (!st[at].next.count(c)) {
				// pattern not found
				return 0;
			} else {
				at = st[at].next[c];
			}
		}

		return dp[at];
	}

	void main () {
		sa_build();
		mark();
		memset (dp, -1, sizeof dp);
		go (0);

		int q;	cin >> q;
		while (q--) {
			string p;	cin >> p;
			cout << get (p) << endl;
		}
	}
}

/* Note: Another way of doing it is: getting the state, then calculate
 * using dynamic programming the biggest length to the last node, answer
 * is text.length() - dp[at] + 1
 *
 * Find the state of the substring,
 * answer is the first element of endpos (fpos) - length of substring + 1
 * */
namespace Position_first_occurrence {

	int get (string &p) {
		int at = 0;

		for (auto c : p) {
			if (!st[at].next.count(c)) {
				return -1;
			} else {
				at = st[at].next[c];
			}
		}

		return st[at].fpos - p.size() + 1;
	}

	void main() {
		sa_build();

		int q;	cin >> q;
		while (q--) {
			string p;	cin >> p;
			cout << get(p) << endl;
		}
	}
}

/* OBS: Total number of occurrences can be calculated this way too
 *
 * Position of all occurrences of a pathen p in a text,
 * O(sizeof(text) + number of occurrences of the patterns), 
 *
 * Build the tree of edges from link[node] to node, find state
 * corresponding to the pattern, go through the tree (go from at to
 * next means, at is suffix of next, endpos(next) is countained in endpos(at)
 * and size(endpos(at)) = size(endpos(next)) + 1), them set of first occurrence of
 * all states are the position of all occurrences of the pattern
 * */
namespace Position_all_occurrences {
	vector <int> res;
	vector <int> g[2*N];
	string p;

	/* Build suffix link tree */
	void build_tree () {
		for (int i = 1; i <= last; i++)
			g[st[i].link].pb(i);
	}

	/* Use bfs to avoid memory limit */
	void go (int beg) {
		queue <int> q;
		q.push(beg);

		while (q.size()) {
			int at = q.front();
			q.pop();
			// index of pattern p as suffix of the first occurrence
			// of state next
			res.pb(st[at].fpos - p.size() + 1);

			for (auto next : g[at])
				q.push(next);
		}
	}

	/* get the state, to go throgh tree next*/
	void get () {
		int at = 0;

		for (auto c : p) 
			if (!st[at].next.count(c)) 
				return;
			else 
				at = st[at].next[c];

		go (at);
	}

	void main () {
		sa_build();
		build_tree();

		int q;	cin >> q;
		while (q--) {
			res.clear();
			cin >> p;
			get();

			cout << res.size() << endl;
			for (auto it : res)
				cout << it << " ";
			cout << endl;
		}
	}
}

/*number of differente substrings in a that are not
 * in b*/
namespace in_a_not_in_b {
	void sa_build() {
		sa_init();
		string a, b;	cin >> a >> b;
		string s = a + '#' + b + '$';
		for (int i = 0; i < (int)s.size(); i++)
			sa_extend(s[i]);
	}

	int a[2*N], b[2*N];

	// a[at] marks if state at belongs to string a
	int finda(int at) {
		int &r = a[at];
		if (r != -1)	return r;
		r = 0;

		for (auto next : st[at].next) {
			if (next.fi == '#')	r = 1;
			if (finda(next.se))	r = 1;
		}

		return r;
	}

	// a[at] marks if state at belongs to string b
	int findb(int at) {
		int &r = b[at];
		if (r != -1)	return r;
		r = 0;

		for (auto next : st[at].next) {
			if (next.fi == '#')	continue;
			if (next.fi == '$')	r = 1;
			if (findb(next.se))	r = 1;
		}

		return r;
	}

	// just count how many strings are in a but no in b
	ll dp[2*N];
	ll go(int at) {
		ll &r = dp[at];
		if (r != -1)	return r;

		r = a[at] and !b[at];
		for (auto next : st[at].next) 
			r += go(next.se);

		return r;
	}

	void main() {
		sa_build();
		memset(a, -1, sizeof a);
		finda(0);
		memset(b, -1, sizeof b);
		findb(0);
		memset(dp, -1, sizeof dp);
		cout << go(0) << endl;
	}
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
