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
 
struct Trie {
	int cnt, word;
	map <char, Trie> m;
 
	Trie () {
		word = cnt = 0;
		m.clear();
	}
 
	void add (const string &s, int i) {
		cnt++;
		if (i == (int)s.size()) {
			word++;
			return;
		}
 
		if (!m.count(s[i])) 
			m[s[i]] = Trie();
 
		m[s[i]].add(s, i + 1);
	}

	bool remove (const string &s, int i) {
		if (i == (int)s.size()) {
			if (word) {
				word--;
				return true;
			}
			return false;
		}
 
		if (!m.count(s[i]))
			return false;
 
		if (m[s[i]].remove(s, i + 1) == true) {
			cnt--;
			return true;
		}
 
		return false;
	}
 
	bool count (const string &s, int i) {
		if (i == (int)s.size())
			return word;
 
		if (!m.count(s[i]))
			return false;
 
		return m[s[i]].count(s, i + 1);
	}
 
	bool count_prefix (const string &s, int i) {
		if (word)	return true;
 
		if (i == (int)s.size())
			return false;
 
		if (!m.count(s[i]))
			return false;
 
		return m[s[i]].count_prefix(s, i + 1);
	}
 
	bool is_prefix (const string &s, int i) {
		if (i == (int)s.size())
			return cnt;
 
		if (!m.count(s[i]))
			return false;
 
		return m[s[i]].is_prefix(s, i + 1);
	}
 
	void add (const string &s) {
		add (s, 0);
	}
 
	bool remove (const string &s) {
		return remove(s, 0);
	}
 
	bool count (const string &s) {
		return count(s, 0);
	}
 
	// return if trie countains a string that is prefix os s
	// trie has 123, query 12345	returns true
	// trie has 12345, query 123 	returns false
	bool count_prefix (const string &s) {
		return count_prefix(s, 0);
	}
 
	// return if s is prefix of some string countained in trie
	// trie has 12345, query 123 	returns true
	// trie has 123, query 12345	returns false
	bool is_prefix (const string &s) {
		return is_prefix(s, 0);
	}
 
} T;
