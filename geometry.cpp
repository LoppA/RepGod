#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mk make_pair
#define fi first
#define se second

typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double E = exp(1);

class Point {
	static const int EPS = 1e-7;
public:
	double x, y;

	Point () { }

	Point (double x, double y) {
		this->x = x;
		this->y = y;
	}

	//Produto vetorial
	double operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x); 
	}

	//Produto escalar
	double operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	Point operator * (double k) {
		return Point (x*k, y*k);
	}

	double len () {
		return sqrt (x*x + y*y);
	}

	Point operator + (const Point &b) const {
		return Point (x + b.x, y + b.y);
	}

	Point operator - (const Point &b) const {
		return Point (x - b.x, y - b.y);
	}

	double dpp (const Point &b) {
		return ((*this)-b).len();
	}

	double proj (Point &b) {
		return ((*this)*b)/b.len();
	}
	Point norm () {
		return Point (x/this->len(), y/this->len());
	}

	bool operator == (const Point &b) const {
		return (abs (x - b.x) < EPS and abs (y - b.y) < EPS);
	}

	bool operator < (const Point &b) const {
		return ((x < b.x) or ((x == b.x) and y < b.y));
	}

	Point rotaciona (double ang) {
		double c = cos(ang), s = sin(ang);
		double X = x*c + y*s;
		double Y = x*(-1*s) + y*c;
		return Point(X,Y);
	}

	vector <Point> convex_hull (vector <Point> p) {
		if (p.size() <= 2) return p;

		int n = p.size(), k = 0;
		vector <Point> H(2*n);

		sort(p.begin(), p.end());

		for (int i = 0; i < n; i++) {
			while (k >= 2 and ((H[k-1]-H[k-2])^(p[i]-H[k-2])) <= 0.0) k--;
			H[k++] = p[i];
		}

		for (int i = n-2, t = k+1; i >= 0; i--) {
			while (k >= t and ((H[k-1]-H[k-2])^(p[i]-H[k-2])) <= 0.0) k--;
			H[k++] = p[i];
		}

		H.resize(k-1);

		return H;
	}
};

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
