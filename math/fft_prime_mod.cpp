const int md = 1004535809;
const int gen = 3;

int pw(int a, int b) {
  int x = 1, step = 1 << 30;
  while (step > 0) {
    x = (long long)x * x % md;
    if (step & b) x = (long long)x * a % md;
    step >>= 1;
  }
  return x;
}

void fft(vector <int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int j = 0;
    int x = i, y = n - 1;
    while (y > 0) {
      j = (j << 1) + (x & 1);
      x >>= 1;
      y >>= 1;
    }
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 1; len < n; len *= 2) {
    int root = pw(gen, (md - 1) / (2 * len));
    for (int i = 0; i < n; i += 2 * len) {
      int w = 1;
      for (int j = 0; j < len; j++) {
        int u = a[i + j];
        int v = (long long)a[i + j + len] * w % md;
        a[i + j] = u + v;
        if (a[i + j] >= md) a[i + j] -= md;
        a[i + j + len] = u - v;
        if (a[i + j + len] < 0) a[i + j + len] += md;
        w = (long long)w * root % md;
      }
    }
  }
}

void multiply(vector <int> a, vector <int> b, vector <int> &r) {
  int an = a.size();
  int bn = b.size();
  int nn = 1;
  while (nn < 2 * an || nn < 2 * bn) nn <<= 1;
  a.resize(nn);
  b.resize(nn);
  fft(a);
  fft(b);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * b[i] % md;
  reverse(++a.begin(), a.end());
  fft(a);
  int inv = pw(nn, md - 2);
  for (int i = 0; i < nn; i++) a[i] = (long long)a[i] * inv % md;
  r = a;
}
