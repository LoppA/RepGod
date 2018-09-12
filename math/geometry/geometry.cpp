/*** Sumario
 * Lei dos Cossenos, Lei dos Senos
 * gcd
 * norm
 * sig_mul
 **Point
 *  operators
 *  len
 *  ddp, ddp2
 *  relative_proj
 *  norm
 *  perp
 *  distToSegment
 *  proj
 *  rotaciona
 *  area
 *  convex_hull
 *  ang
 *  inter
 *  intersect
 *  inside
 *  minRetangulo
 *  max_dist
 *  min_dist
 *  max_ab
 *  pick_theorem
 **Circle
 *  intersect
 *  circumcicle
 *  cover
 * getAreaTriangle
 * */
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

/* 
 *     /|
 *    /A|
 *  c/  |b  
 *  /   |
 * /B__C|
 *   a
 * Lei dos Cossenos: a**2 = b**2 + c**2 - 2*b*c*cos(A)
 * Lei dos Senos: a/sin(A) = b/sin(B) = c/sin(C)
 *
 * */

ll gcd (ll a, ll b) {
	if (!b)
		return a;
	else
		return gcd(b, a%b);
}

double norm(double x) {
    if(x > 0)   return 1;
    if(x < 0)   return -1;
    return 0;
}

double sig_mul(double a, double b) {
    a = norm(a);
    b = norm(b);
    return a*b;
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
	// dist point p to line ab = ||ab^p|| / ||ab||
	double operator ^ (const Point &b) const {
		return (this->x * b.y) - (this->y * b.x); 
	}

	//Produto escalar
	// p*q = |p|*|q|*cos(ang)	ang: inner ang (0 <= ang < PI)
	// p*q = 0 => ang = 90 / p*q > 0 => ang < 90 / p*q < 0 => ang > 90
	// p*p = |p|^2  => |p| = sqrt(p*p)
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

    // Check if segment ab intersects with cd, considera endpoints como dentro
	static bool inter (const Point &a, const Point &b, const Point &c, const Point &d) {
        Point ab = b-a;
        Point ac = c-a;
        Point ad = d-a;

        Point cd = d-c;
        Point ca = a-c;
        Point cb = b-c;

        // a, b, c, d -> Colineares
        // Se estiver desconsiderando endpoints nao precisa, essa parte +- testada
        if(abs(ab^ac) < EPS and abs(ab^ad) < EPS) {
            Point bc = c-b;
            Point bd = d-b;
            Point da = a-d;
            Point db = b-d;
            if((ac*ad) <= 0.0)  // < para descosiderar endpoints(soh igual a zero quando c=d)
                return true;
            if((bc*bd) <= 0.0)  // < para descosiderar endpoints(soh igual a zero quando c=d)
                return true;
            if((ca*cb) <= 0.0)  // < para descosiderar endpoints(soh igual a zero quando c=d)
                return true;
            if((da*db) <= 0.0)  // < para descosiderar endpoints(soh igual a zero quando c=d)
                return true;
            return false;
        }

        // >= para desconsiderar endpoints
        if(sig_mul(ab^ac, ab^ad) > 0.0)
            return false;

        // >= para desconsiderar endpoints
        if(sig_mul(cd^ca, cd^cb) > 0.0)
            return false;

        return true;
    }

	/*Interseccao de dois vetores somandos a pontos, returns t that p1 + v1*t = P_inter*/
	static double intersect (Point p1, Point v1, Point p2, Point v2) {
		if (abs(v2 ^ v1) >= EPS) {
			Point c = p1 - p2;
			return (c ^ v2)/(v2 ^v1);
		} else {
			cout << "Class Point (funcao inter): retas paralelas" << endl;
			cout << "Talvez deva ajustar o EPS" << endl;
		}
		return 0.0;
	}

	/* Retorna se point p esta dentro do poligono convexo v, pontos de v estao
	 * em counter clockwise
	 * Considera borda como fora
	 * O(log2(v.size()))*/
	static bool inside(const vector<Point> &v, const Point &p) {
		// V DEVE ESTAR EM COUNTER CLOCKWISE
		int n = v.size();

		if(n < 3)
			return false;
	
		// Considerar borda como dentro: mudar para <
		if(((v[1]-v[0])^(p-v[0])) <= 0)
			return false;

		int bot = 2, top = n-1;
		int ans = -1;
		while(bot <= top) {
			int mid = (bot+top)>>1;

			// Considerar borda como dentro: mudar para <=
			if(((v[mid]-v[0])^(p-v[0])) < 0) {
				ans = mid;
				top = mid-1;
			} else {
				bot = mid+1;
			}
		}

		if(ans == -1)
			return false;

		// Considerar borda como dentro: mudar para <
		if(((v[ans]-v[ans-1])^(p-v[ans-1])) <= 0)
			return false;

		return true;
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

	// divide and conquer
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

//	** MAX A*X + B*Y	BEGIN
	// ternary search
	static double max_ab (const vector <Point> &p, int bot, int top, const Point &ab) {
		if (bot > top)	return -1e18;
		double ret = max (ab*p[bot], ab*p[top]);
		top--;

		while (bot <= top) {
			int mid = (bot + top)>>1;

			ret = max (ret, max(p[mid]*ab, p[mid+1]*ab));

			if (p[mid]*ab > p[mid+1]*ab) {
				top = mid - 1;
			} else {
				bot = mid + 1;
			}
		}

		return ret;
	}

	static double max_ab (const vector <Point> &p, const Point &ab) {
		int n = p.size();

		if (n < 10) {
			double ret = ab*p[0];
			for (int i = 1; i <= n; i++)
				ret = max(ret, ab*p[i]);
			return ret;
		}

		Point perp = ab.perp();

		int split = 0;
		int bot = 0, top = n - 1;

		double dir = perp^(p[1]-p[0]);
		if (!dir) {
			bot = 1;
			dir = perp^(p[2]-p[0]);
		}

		if (dir > 0)
			dir = 1;
		else 
			dir = -1;

		// normal divides the convex hull, to get 2 ranges where ternary search is possible
		while (bot <= top) {
			int mid = (bot + top)>>1;

			if ((perp^(p[mid]-p[0])) * dir > 0) {
				bot = mid + 1;
				split = mid;
			} else {
				top = mid - 1;
			}
		}

		return max (max_ab(p, 0, split, ab), max_ab(p, split + 1, n, ab));
	}

	// PUBLIC
	// O(convex_hull(p)) + ab.size()*log2(p.size())
	static vector <double> max_ab (vector <Point> p, const vector <Point> &ab) {
		// convex_hull WITHOUT COLINEAR POINTS
		p = Point::convex_hull(p);
		vector <double> ans(ab.size());

		int n = ab.size();
		for (int i = 0; i < n; i++) 
			ans[i] = max_ab(p, ab[i]);

		return ans;
	}
//	** MAX A*X + B*Y	END

    /*
    Teorema de Pick:
    Um polígono construído sobre uma grade de pontos equidistantes.
    Dado um polígono simples construído sobre uma grade de pontos equidistantes (i.e., pontos com coordenadas inteiras) 
    de tal forma que todos os vértices do polígono sejam pontos da grade, o teorema de Pick fornece uma fórmula simples 
    para o cálculo da área A desse polígono em termos do número i de pontos interiores localizados no polígono, 
    e o número b de pontos fronteiriços localizados no perímetro do polígono:
        A = i + b/2 - 1

        i = A - b/2 + 1
    Os pontos devem ser inteiros
    */
	static ll pick_theorem(const vector<Point> &p) {
        int n = p.size();
        ll A = 0, b = 0;

        for(int i = 0; i < n; i++) {
            int j = (i+1)%n;
            A += p[i]^p[j];

			ll xx = abs(p[j].x - p[i].x);
			ll yy = abs(p[j].y - p[i].y);

            b += gcd(xx, yy);
        }

        if(A < 0)   A *= -1;
        A>>=1;

        ll ans = A - (b>>1) + 1;
        return ans;
	}
};

ostream &operator<<(ostream &os, Point const &p) {
	return os << p.x << " " << p.y;
}

class Circle {
public:
	Point c;
	double r;

	Circle () {}

	Circle (const Point &c, double r) : c(c), r(r) {}

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

	// Circumcircle of a triangle, TAKE CARE WITH 3 COLINEAR POINTS
	static Circle circumcircle (const Point &a, const Point &b, const Point &c) {
		Point ab = b - a, bc = c - b;
		Point mab = a + ab * 0.5;
		Point mbc = b + bc * 0.5;

		double a1 = ab.x, b1 = ab.y;
		double c1 = -a1 * mab.x - b1 * mab.y;
		
		double a2 = bc.x, b2 = bc.y;
		double c2 = -a2 * mbc.x - b2 * mbc.y;
		
		double den = a1 * b2 - a2 * b1;

		double x = (-c1 * b2 + b1 * c2)/den;
		double y = (-c2 * a1 + a2 * c1)/den;
		
		Point center(x, y);
		return Circle(center, (a-center).len());
	}

	// Randomize O(p.size())
	// Return circle that covers all point in p with minimum radius
	// Idea: if some point pt is outside of current circle, make new circle with previous points
	// in circle, this circle will have point pt on the border
	// With 3 points on the border its easy to get the circle (Circumcicle)
	static Circle cover (vector <Point> p, vector <Point> border = vector <Point>()) {
		random_shuffle(p.begin(), p.end());

		Circle res;
		if (border.size() == 0) 
			res = Circle(p[0], 0.0);
		else if (border.size() == 1) 
			res = Circle(border[0], 0.0);
		else if (border.size() == 2)
			res = Circle((border[0] + border[1])*0.5, (border[0].dpp(border[1]))/2.0);
		else 
			return circumcircle (border[0], border[1], border[2]);

		vector <Point> p2;
		for (auto pt : p) {
			if (res.c.dpp(pt) > res.r) {
				border.pb(pt);
				res = cover (p2, border);
				border.pop_back();
			}
			p2.pb(pt);
		}

		return res;
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
