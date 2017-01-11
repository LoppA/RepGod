#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 6;
int b[N];
int m, n;
string p, t;

void report (int at) {

}

void KMPPre () {
	int i = 0, j = -1;
	b[0] = -1;
	while (i < m) {
		while (j >= 0 and p[i] != p[j])	j = b[j];
		i++;	j++;
		b[i] = j;
	}
}

void KMP () {
	m = p.size();
	n = t.size();

	KMPPre();

	int i = 0, j = 0;
	while (i < n) {
		while (j >= 0 and t[i] != p[j])	j = b[j];
		i++;	j++;
		if (j == m) {
			report (i - j);
			j = b[j];
		}
	}
}

int main (void) {

	return 0;
}
