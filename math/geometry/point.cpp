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

	//Produto vetorial
	// p^q = |p|*|q|*sin(ang)	ang: directed ang from p to q(-PI < ang <= PI)
	// p^q = 0 => ang = 0 or PI, p and q are colinear
	// p^q > 0 => 0 < ang < PI / p^q < 0 => -PI < ang < 0
	// p^q = directed area of paralelogram formed by vectors p and q
	// dist point p to line ab = ||ab^p|| / ||ab||
	T operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x); 
	}

	//Produto escalar
	// p*q = |p|*|q|*cos(ang)	ang: inner ang (0 <= ang < PI)
	// p*q = 0 => ang = 90 / p*q > 0 => ang < 90 / p*q < 0 => ang > 90
	// p*p = |p|^2  => |p| = sqrt(p*p)
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

	Point rotaciona (T ang) const {
		T c = cos(ang), s = sin(ang);
		T X = x*c - y*s;
		T Y = x*s + y*c;
		return Point(X,Y);
	}
};

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
