/* emaxx implementation */
/* Multiplication with arbitrary modulos
 *    use ntt if mod is prime and can be written as 2**k * c + 1
 *    if not, use Chinese Reminder Theorem
 *    or transform A(x) = A1(x) + A2(x)*c decompose into A(x)/c and A(x)%c
 *                 B(x) = B1(x) + B2(x)*c
 *        where c ~= sqrt(mod)
 *        A * B = A1*B1 + c*(A1*B2 + A2*B1) * c**2(A2*B2)
 *        with all values < sqrt(mod) subpolynomials have coefficientes < mod * N after fft multiply decreasing changes of rounding error
 * */

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const double PI=acos(-1);

typedef complex<double> base;

void fft (vector<base> & a, bool invert) {
	int n=(int) a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit=n>>1;
		for (;j>=bit;bit>>=1)
			j-=bit;
		j+=bit;
		if(i<j)
			swap(a[i],a[j]);
	}
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w(1);
			for (int j=0; j<len/2; ++j) {
				base u=a[i+j], v=a[i+j+len/2]*w;
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w*=wlen;
			}
		}
	}
	if (invert)
		for(int i=0;i<n;++i)
			a[i]/=n;
}

// a, b => coefs to multiply,  res => resulting coefs
// a[0], b[0], res[0] = coef x^0
// Doesnt work with negative coefs
void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n=1;
	while (n<max(a.size(),b.size())) n<<=1;
	n<<=1;
	fa.resize(n),fb.resize(n);
	fft (fa,false);  fft(fb,false);
	for (size_t i=0; i<n; ++i)
		fa[i]*=fb[i];
	fft (fa, true);
	res.resize (n);
	// avoid precision errors, mess up with negative values of coefs
	for(size_t i=0; i<n; ++i)
		res[i]=int(fa[i].real() + 0.5);
}
