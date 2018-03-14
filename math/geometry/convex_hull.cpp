#include <bits/stdc++.h>

using namespace std;

#define mk make_pair
#define pb push_back
#define fi first
#define se second

typedef pair<int, int> ii;
typedef long long ll;
const double EPS = 1e-9;
const double PI = acos(-1.0);

template <class T>
class Point {
public:
	T x, y;

	Point () { }

	Point (T x, T y) : x(x), y(y) {}

	bool operator == (const Point &b) const {
		return (abs (x - b.x) < EPS and abs (y - b.y) < EPS);
	}

	bool operator < (const Point &b) const {
		return ((x < b.x) or ((x == b.x) and y < b.y));
	}

	T operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x); 
	}

	T operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	Point operator * (T k) const {
		return Point (x*k, y*k);
	}

	Point operator / (T k) const {
		return Point (x/k, y/k);
	}
	
	Point operator + (const Point &b) const {
		return Point (x + b.x, y + b.y);
	}

	Point operator - (const Point &b) const {
		return Point (x - b.x, y - b.y);
	}

	T len2 () const {
		return x*x + y*y;
	}

	T len () const {
		return sqrt (x*x + y*y);
	}

	T dpp2 (const Point &b) const {
		return ((*this)-b)*((*this)-b);
	}

	T dpp (const Point &b) const {
		return ((*this)-b).len();
	}

	/* return counter clock points of convex hull
	 * WITHOUT COLINEAR POINTS*/
	static vector <Point> convex_hull (vector <Point> p) {
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
