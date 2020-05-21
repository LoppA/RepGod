#include <bits/stdc++.h>

using namespace std;

template<typename T>
void mult(vector<T> &a, vector<T> &b, const int n, vector<T> &res) {
  if(n <= 64) {
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        res[i+j] += a[i]*b[j];
    return;
  }

  int mid = n/2;
  vector<T> _a(mid), _b(mid);
  vector<T> E(n);

  mult(a, b, mid, res);           // r0 = a0*b0, r0*x^0

  for(int i = 0; i < mid; i++) {  // a1, b1
    _a[i] = a[i+mid];
    _b[i] = b[i+mid];
  }
  mult(_a, _b, mid, E);           // r2 = a1+b1
  for(int i = 0; i < n; i++)
    res[i+n] = E[i];              // *= x^n

  for(int i = 0; i < mid; i++) {  // (a0+a1), (b0+b1)
    _a[i] = a[i] + a[i+mid];
    _b[i] = b[i] + b[i+mid];
  }
  fill(E.begin(), E.end(), 0);
  mult(_a, _b, mid, E);           // E = (a0+a1)*(b0+b1)

  for(int i = 0; i < mid; i++) {  // (E-r0-r2)*x^mid
    const T tmp = res[i+mid];
    res[i+mid]     += E[i]     - res[i] - res[i+n];
    res[i+mid+mid] += E[i+mid] - tmp    - res[i+n+mid];
  }
}

template<typename T>
void mult(const vector<T> &a, const vector<T> &b, vector<T> &res) {
  int n = 1;
  while(n < (int)max(a.size(), b.size()))  n <<= 1;
  vector<T> _a(a.begin(), a.end());
  vector<T> _b(b.begin(), b.end());
  _a.resize(n, 0); _b.resize(n, 0);

  res.resize(2*n);
  fill(res.begin(), res.end(), 0);
  mult<T>(_a, _b, n, res);
}


int main(void) {
  ios_base::sync_with_stdio(false);
  int T;  cin >> T;
  while(T--) {
    int n;  cin >> n;
    n++;
    vector<long long> a(n, 0), b(n, 0), res;
    for(int i = 0; i < n; i++)
      cin >> a[i];
    for(int i = 0; i < n; i++)
      cin >> b[i];
		
    mult<long long>(a, b, res);

    for(int i = 0; i < 2*n-1; i++)
      cout << res[i] << " \n"[i==2*n-2];
  }

  return 0;
}
