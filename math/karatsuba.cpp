/*O(n^log2(3)) or O(n1.58)
https://codeforces.com/blog/entry/74209 is faster

Queremos calcular a multiplicacao de polinomio A*B

n = maximo entre tamanho do polinomio a e b. Fazer n ser uma potencia de 2 para ficar mais simples
mid = n/2

Dividir o polinomio P em 2 partes, p1 e p0. p0 eh a metade com os coeficientes das potencias de 0 ateh mid-1 e p1 eh a metade com os coeficientes das potencias de mid ateh n-1.

A = a1*x^mid + a0
B = b1*x^mid + b0

assim A*B = (a1*x^mid + a0) * (b1*x^mid + b0) = a0*b0 + (a1*b0 + a0*b1)*x^mid + a1*b1*x^n (**formula1**)

podemos calcular a0*b0 e a1*b1. Note que esses polinomios tem a metade do tamanho dos originais(mid).
Vamos chamar f0 = a0*b0 e f1 = a1*b1

E agora calculamos E = (a0+a1)*(b0+b1). (a0+a1) e (b0+b1) possuem tamanho mid tambem.

A resposta para A*B pode ser escrita da forma:

f0 + f1*x^n + (E - f0 - f1)*x^mid

Por que isso esta certo?
f0 + f1*x^n + (E - f0 - f1)*x^mid,  substituindo f0 e f1
(a0*b0) + (a1*b1)*x^n + (E - (a0*b0) - (a1*b1))*x^mid,  substituindo E
(a0*b0) + (a1*b1)*x^n + ((a0+a1)*(b0+b1) - (a0*b0) - (a1*b1))*x^mid,  abrindo as multiplicacoes
(a0*b0) + (a1*b1)*x^n + (a0*b0 + a0*b1 + a1*b0 + a1*b1 - (a0*b0) - (a1*b1))*x^mid,     simplificando
(a0*b0) + (a1*b1)*x^n + (a0*b1 + a1*b0)*x^mid, e isso eh igual a A*B escrito em **formula1** acima

Complexidade:
Para o problema de tamanho n, fazemos 3 chamadas para um problema menor de tamanho mid=n/2, (a0*b0, a1*b1 e (a0+a1)*(b0+b1)):
T(n) = 3*T(N/2) + O(N)
pelo teorema do mestre a complexidade eh O(n^log2(3))
*/

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

  mult<T>(a, b, mid, res);           // f0 = a0*b0

  for(int i = 0; i < mid; i++) {  // a1, b1
    _a[i] = a[i+mid];
    _b[i] = b[i+mid];
  }
  mult<T>(_a, _b, mid, E);           // f1 = a1*b1
  for(int i = 0; i < n; i++)
    res[i+n] = E[i];              // *= x^n

  for(int i = 0; i < mid; i++) {  // (a0+a1), (b0+b1)
    _a[i] = a[i] + a[i+mid];
    _b[i] = b[i] + b[i+mid];
  }
  fill(E.begin(), E.end(), 0);
  mult<T>(_a, _b, mid, E);           // E = (a0+a1)*(b0+b1)

  for(int i = 0; i < mid; i++) {  // (E-f0-f1)*x^mid
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
