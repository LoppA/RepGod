#include <bits/stdc++.h>

using namespace std;

template<typename T>
void mult(T *a, T *b, const int n, T *res) {
	if(n <= 64) {
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				res[i+j] += a[i]*b[j];
		return;
	}

	int mid = n/2;
	mult(a, b, mid, res);						// r0 = a0*b0, r0*x^0
	mult(a+mid, b+mid, mid, res+n);	// r2 = a1+b1, r2*x^2mid

	T _a[mid], _b[mid];	//shhhh
	T E[n] = {0};
	for(int i = 0; i < mid; i++) {
		_a[i] = a[i] + a[i+mid];
		_b[i] = b[i] + b[i+mid];
	}
	mult(_a, _b, mid, E);

	for(int i = 0; i < mid; i++) {
		const T tmp = res[i+mid];
		res[i+mid] += E[i] - res[i] - res[i+n];
		res[i+2*mid] += E[i+mid] - tmp - res[i+n+mid];
	}
}

template<typename T>
void mult(T *a, int na, T *b, int nb, T* res) {
	int n = 1;
	while(n < max(na, nb))	n <<= 1;
	mult<T>(a, b, n, res);
}

const int N = 1e5 + 5, RN = 4*N;
long long a[N], b[N], res[RN];

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;	cin >> T;
	while(T--) {
		memset(a, 0, sizeof a);
		memset(b, 0, sizeof b);
		memset(res, 0, sizeof res);

		int n;	cin >> n;
		n++;
		for(int i = 0; i < n; i++)
			cin >> a[i];
		for(int i = 0; i < n; i++)
			cin >> b[i];
		
		mult<long long>(a, n, b, n, res);

		for(int i = 0; i < 2*n-1; i++)
			cout << res[i] << " \n"[i==2*n-2];
	}

	return 0;
}
