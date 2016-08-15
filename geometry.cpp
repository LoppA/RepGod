#include <bits/stdc++.h>

using namespace std;

#define mk make_pair
#define pb push_back
#define fi first
#define se second

typedef pair<int, int> ii;
typedef long long ll;
const double EPS = 1e-6;
const double PI = acos(-1.0);

ll gcd (ll a, ll b) {
	if (!b)
		return a;
	else
		return gcd(b, a%b);
}

class Point {
	static const double EPS = 1e-6;
public:
	double x, y;

	Point () { }

	Point (double x, double y) {
		this->x = x;
		this->y = y;
	}

	bool operator == (const Point &b) const {
		return (abs (x - b.x) < EPS and abs (y - b.y) < EPS);
	}

	bool operator < (const Point &b) const {
		return ((x < b.x) or ((x == b.x) and y < b.y));
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
	
	Point operator + (const Point &b) const {
		return Point (x + b.x, y + b.y);
	}

	Point operator - (const Point &b) const {
		return Point (x - b.x, y - b.y);
	}

	double len () {
		return sqrt (x*x + y*y);
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

	/*area de um poligono concavo ou convexo
	dado vetor de vertices ordenados clockwise ou
	counter clockwise*/
	static double area (vector <Point> v) {
		double area = 0.0;
		for (int i = 0; i < (int)v.size(); i++) 
			area += v[i] ^ v[(i+1)%v.size()];
		return abs(area/2.0);
	}

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
	
	/*Angulo em forma de fracao reduzida entre o vetor Op (p é o ponto)
	 e o eixo x, se paralelo ao eixo x retorna (1,0) ou (-1,0)
	 se paralelo ao eixo y retorna (0,1) ou (0,-1)
	 SÓ FUNCIONA PARA PONTOS INTEIROS*/ 
	static ii ang (Point p) {
		int a = p.x, b = p.y;
		if (a == 0) return mk(0, b/abs(b));
		else if (b == 0) return mk(a/abs(a), 0);
		return mk(a/gcd(a,b), b/gcd(a,b));
	}
};

ostream &operator<<(ostream &os, Point const &p) {
	return os << p.x << " " << p.y;
}

class Triangle {
public:
	Point p[3];
	double side[3];
	double per, area;

	Triangle () {}

	Triangle (double a, double b, double c) {
		side[0] = a;	side[1] = b;	side[2] = c;
		per = a + b + c;
		area = sqrt((per/2.0) * (per/2.0 - a) * (per/2.0 - b) * (per/2.0 - c));
	}

	double raioInCircle () {
		return area/(per/2.0);
	}

	double raioCircumCircle () {
		return side[0] * side[1] * side[2] / (4.0 * area);
	}

};

int main (void) {

	return 0;
}
