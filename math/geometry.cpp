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

ll gcd (ll a, ll b) {
	if (!b)
		return a;
	else
		return gcd(b, a%b);
}

class Point {
public:
	double x, y;

	Point () { }

	Point (double x, double y) {
		this->x = x;
		this->y = y;
	}

	/**/
	bool operator == (const Point &b) const {
		return (abs (x - b.x) < EPS and abs (y - b.y) < EPS);
	}

	/**/
	bool operator < (const Point &b) const {
		return ((x < b.x) or ((x == b.x) and y < b.y));
	}

	//Produto vetorial
	// p^q = |p|*|q|*sin(ang)	ang: directed ang from p to q(-PI < ang <= PI)
	// p^q = 0 => ang = 0 or PI, p and q are colinear
	// p^q > 0 => 0 < ang < PI / p^q < 0 => -PI < ang < 0
	// p^q = directed area of paralelogram formed by vectors p and q
	// list point p to line ab = ||ab^p|| / ||ab||
	double operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x); 
	}

	//Produto escalar
	// p*q = |p|*|q|*cos(ang)	ang: inner ang (0 <= ang < PI)
	// p*q = 0 => ang = 90 / p*q > 0 => ang < 90 / p*q < 0 => ang > 90
	// p*p = |p|^2  => |p| = sqrt(p*p)
	// p*q is the directed length of projection of p on q
	double operator * (const Point &b) const {
		return (this->x * b.x) + (this->y * b.y);
	}

	/**/
	Point operator * (double k) const {
		return Point (x*k, y*k);
	}

	Point operator / (double k) const {
		if (k == 0.0) cout << "Class Point (operador /): divisao por zero" << endl;
		return Point (x/k, y/k);
	}
	
	/**/
	Point operator + (const Point &b) const {
		return Point (x + b.x, y + b.y);
	}

	/**/
	Point operator - (const Point &b) const {
		return Point (x - b.x, y - b.y);
	}

	/**/
	double len () const {
		return sqrt (x*x + y*y);
	}

	double dpp2 (const Point &b) const {
		return ((*this)-b)*((*this)-b);
	}

	/*Distancia ponto a ponto*/
	double dpp (const Point &b) const {
		return ((*this)-b).len();
	}

	/*Oriented relative length of projection of this over b*/
	double relative_proj (Point &b) const {
		return ((*this)*b)/(b.len()*b.len());
	}

	Point norm () const {
		return Point (x/this->len(), y/this->len());
	}

	/*Retorna o vetor perpendicular ao vetor (0,0) -> (Point)
	Sentido clockwise*/
	Point perp () const {
		return Point (this->y, -1.0 * this->x);
	}

	// Distancia do ponto p ao segmento ab, tambem retorna por 
	// referencia o ponto (c) do segmento mais perto de p
	double distToSegment (const Point a, const Point b, Point &c) const {
		// formula: c = a + u * ab
		Point p = *this;
		if (a == b) return p.dpp(a);
		Point ap = Point(p - a), ab = Point(b - a);
		double u = ap.relative_proj(ab);
		if (u < 0.0) u = 0.0;
		if (u > 1.0) u = 1.0;
		c = a + ab * u;
		return p.dpp(c);
	}

	// Projection of this over v
	Point proj (const Point &v) const {
		return v*((*this)*v);
	}

	/**/
	Point rotaciona (double ang) const {
		double c = cos(ang), s = sin(ang);
		double X = x*c - y*s;
		double Y = x*s + y*c;
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

	/* return counter clock points of convex hull*/
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
		ll a = p.x, b = p.y;
		if (a == 0) return mk(0, b/abs(b));
		else if (b == 0) return mk(a/abs(a), 0);
		return mk(a/gcd(a,b), b/gcd(a,b));
	}

	/*Interseccao de dois vetores somandos a pontos*/
	static double inter (Point p1, Point v1, Point p2, Point v2) {
		if (abs(v2 ^ v1) >= EPS) {
			Point c = p1 - p2;
			return (c ^ v2)/(v2 ^v1);
		} else {
			cout << "Class Point (funcao inter): retas paralelas" << endl;
			cout << "Talvez deva ajustar o EPS" << endl;
		}
		return 0.0;
	}

	/*Retorna o retangulo (pontos em anti clockwise) que tem a menor valor
	min(Xmax -Xmin, Ymax - Ymin)*/
	static vector <Point> minRetangulo (vector <Point> v) {
		vector <Point> at;
		at.pb(Point(-1e18, -1e18));
		at.pb(Point(1e18, -1e18));
		at.pb(Point(1e18, 1e18));
		at.pb(Point(-1e18, 1e18));
		v = convex_hull(v);
		int n = v.size();
		for (int i = 0; i < n; i++) {
			int j = (i+1)%n;
			Point vec = v[j] - v[i];
			double ang = atan2(vec.y, vec.x);
			vector <Point> ve;
			for (int j = 0; j < n; j++) {
				ve.pb(v[j].rotaciona(ang));
			}
			double minx = DBL_MAX, miny = DBL_MAX, maxx = -DBL_MAX, maxy = -DBL_MAX;
			for (int j = 0; j < n; j++) {
				if (ve[j].x < minx) minx = ve[j].x;
				if (ve[j].x > maxx) maxx = ve[j].x;
				if (ve[j].y < miny) miny = ve[j].y;
				if (ve[j].y > maxy) maxy = ve[j].y;
			}
			double mini = min(maxx - minx, maxy - miny);
			if (mini < min(at[2].x - at[0].x, at[2].y - at[0].y)) {
				at.clear();
				at.pb(Point(minx, miny));
				at.pb(Point(maxx, miny));
				at.pb(Point(maxx, maxy));
				at.pb(Point(minx, maxy));
			}
		}

		return at;
	}

	// distance of 2 farthest points. O(n) + O(convex_hull)
	// Rotating Calipers
	static double max_dist (vector <Point> p) {
		double ret = 0;
		p = Point::convex_hull(p);

		int n = p.size();
		if (n <= 1)
			return 0;
		if (n == 2)
			return p[0].dpp(p[1]);

		int at = 1;
		for (int i = 0; i < n; i++) {
			int j = (i + 1)%n;

			Point v = p[j] - p[i];
			int nxt = (at + 1)%n;
			while (nxt != i and (v^(p[nxt]-p[i])) >= (v^(p[at]-p[i]))) {
				at = nxt;
				nxt = (at + 1)%n;
			}

			ret = max (ret, max (p[i].dpp(p[at]), p[j].dpp(p[at])));
		}

		return ret;
	}

//	** MIN DIST BEGIN	O(N*LOG2(N))	N = number of points
	static bool compy (const Point &a, const Point &b) {
		if (a.y != b.y)	return a.y < b.y;
		return a.x < b.x;
	}

	static void min_dist (const Point &p, const vector <Point> &v, int i, double &d) {
		while (i < (int)v.size() and v[i].y - p.y < d) {
			d = min (d, p.dpp(v[i]));
			i++;
		}
	}

	static vector <Point> min_dist (const vector <Point> &p, int l, int r, double &d) {
		vector <Point> ret;
		if (l == r)	{
			ret.pb(p[l]);
			return ret;
		}
		int mid = (l + r)>>1;

		vector <Point> L = min_dist (p, l, mid, d);
		vector <Point> R = min_dist (p, mid + 1, r, d);

		vector <Point> vl, vr;
		for (auto it : L) 
			if (p[mid].x - it.x < d)
				vl.pb(it);

		for (auto it : R) 
			if (it.x - p[mid + 1].x < d)
				vr.pb(it);

		int i = 0, j = 0;

		while (i < (int)vl.size() and j < (int)vr.size()) {
			if (vl[i].y < vr[j].y) {
				min_dist (vl[i], vr, j, d);
				i++;
			} else {
				min_dist (vr[j], vl, i, d);
				j++;
			}
		}

		ret.resize(r - l + 1);
		merge (L.begin(), L.end(), R.begin(), R.end(),
				ret.begin(), compy);
		return ret;
	}

	// PUBLIC
	static double min_dist (vector <Point> p) {
		if (p.size() <= 1)	return 0.0;
		sort (p.begin(), p.end());

		double dist = p[0].dpp(p[1]);
		min_dist (p, 0, p.size() - 1, dist);
		return dist;
	}
//	** MIN DIST END
};

ostream &operator<<(ostream &os, Point const &p) {
	return os << p.x << " " << p.y;
}

class Circle {
public:
	Point c;
	double r;

	Circle () {}

	Circle (Point c, double r) : c(c), r(r) {}

	/*Interseccao de dois circulos
	OBS: se ha infinitas interseccoes retorna o vetor vazio
	OBS: se existe só um ponto retorna 2 pontos iguais*/
	vector <Point> intersect (Circle b) {
		vector <Point> ret;
		Point c1 = this->c, c2 = b.c;
		double r1 = this->r, r2 = b.r;

		if (c1 == c2) return ret;

		double d = c1.dpp(c2);
		
		if (d > r1 + r2 + EPS) return ret;
		if (d + EPS < abs(r1 - r2)) return ret;

		double a = (r1*r1 - r2*r2 + d*d)/(2.0*d);
		double h = sqrt(max(0.0, r1*r1 - a*a));

		Point pc = c1 + ((c2 - c1)*a)/d;

		/*X EH MENOS E Y EH MAIS*/
		double x = pc.x - ((h*(c2.y - c1.y))/d);
		double y = pc.y + ((h*(c2.x - c1.x))/d);
		ret.pb(Point(x,y));

		x = pc.x + ((h*(c2.y - c1.y))/d);
		y = pc.y - ((h*(c2.x - c1.x))/d);
		ret.pb(Point(x,y));

		return ret;
	}
};

/* Get area of a nondegenerate triangle, with sides a, b, c */
double getAreaTriangle (double a, double b, double c) {
	double p = (a + b + c)/2.0;
	return sqrt (p * (p - a) * (p - b) * (p - c));
}

int main (void) {
	ios_base::sync_with_stdio(false);

	return 0;
}
