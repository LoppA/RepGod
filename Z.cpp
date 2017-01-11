#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int z[N];

void Z (string &s) {
	int L = 0, R = 0;
	
	int n = s.size();
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n and s[R-L] == s[R])	R++;
			R--;
			z[i] = R - L + 1;
		} else {
			int k = i - L;
			if (z[k] < R - i + 1)	z[i] = z[k];
			else {
				L = i;
				while (R < n and s[R-L] == s[R])	R++;
				R--;
				z[i] = R - L + 1;
			}
		}
	}
	
}

int main (void) {

	return 0;
}
