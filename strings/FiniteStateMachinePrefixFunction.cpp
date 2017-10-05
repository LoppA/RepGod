/* Finite State Machine with prefix function for regular strings 

	A[i][j]: i-> current state
			 j-> new character to be appended
			 contains the next state
	
	F[i][j]: i-> current state
			 j-> new sequence of the string to be appended
			 contains the next state

	K[i][j]: i-> current state
			 j-> new sequence of the string to be appended
			 contains the occurences of the pattern
Problem:
	how many times the pattern p (containing only 'a' or 'b')
appears at some fibonnaci string fk

	Fibbonaci string: f0 = ''
					  f1 = 'a'
					  f2 = 'b'
					  fi = fi-2 + fi-1
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

const int N = 1e3 + 5;
int pi[N], k;
ll mod = 1e9 + 9;
vector <int> p;

void pre () {
	p.pb(-1);

	for (int i = 2; i <= (int)p.size(); i++) {
		pi[i] = pi[i-1];
		while (pi[i] > 0 and p[pi[i]] != p[i-1])
			pi[i] = pi[pi[i]];

		if (p[pi[i]] == p[i-1])
			pi[i]++;
	}
}

const int M = 1e4 + 4;
ll A[N][2];
ll F[N][M], K[N][M];

int main (void) {
	string str;
	cin >> str >> k;

	for (int i = 0; i < (int)str.length(); i++)
		p.pb(str[i] - 'a');
	pre ();

	for (int i = 0; i <= 1; i++) 
		A[0][i] = (p[0] == i);
	
	int n = p.size();
	for (int i = 1; i < n; i++) 
		for (int j = 0; j <= 1; j++) 
			if (j == p[i])
				A[i][j] = i + 1;
			else
				A[i][j] = A[pi[i]][j];

	for (int i = 0; i < n; i++) {
		F[i][0] = i;
		F[i][1] = A[i][0];
		F[i][2] = A[i][1];

		K[i][0] = 0;
		K[i][1] = (F[i][1] == (int)str.size());
		K[i][2] = (F[i][2] == (int)str.size());
	}

	for (int j = 3; j <= k; j++) {
		for (int i = 0; i < n; i++) {
			int x = F[i][j-2];
			F[i][j] = F[x][j-1];

			K[i][j] = K[i][j-2] + K[x][j-1];
			K[i][j] %= mod;
		}
	}

	cout << K[0][k] << endl;

	return 0;
}
