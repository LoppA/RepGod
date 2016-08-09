#include <bits/stdc++.h>

using namespace std;

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

	/*Distancia ponto a ponto*/
	double dpp (const Point &b) {
		return ((*this)-b).len();
	}

	/*Projecao*/
	double proj (Point &b) {
		return ((*this)*b)/(b.len()*b.len());
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

	// Distancia do ponto p ao segmento ab, tambem retorna por 
	// referencia o ponto (c) do segmento mais perto de p
	double distToLine (const Point a, const Point b, Point& c) {
		// formula: c = a + u * ab
		Point p = *this;
		if (a == b) return p.dpp(a);
		Point ap = Point(p - a), ab = Point(b - a);
		double u = ap.proj(ab);
		if (u < 0.0) u = 0.0;
		if (u > 1.0) u = 1.0;
		c = a + ab * u;
		return p.dpp(c);
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

ostream &operator<<(ostream &os, Point const &p) {
	return os << p.x << " " << p.y;
}

int main (void) {
	
	return 0;
}
