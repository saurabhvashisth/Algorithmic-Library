#include "bits/stdc++.h"
using namespace std;

#if !ONLINE_JUDGE
#include "debug.h"
#else
#endif

#define INF 1500000000000000000LL
#define MOD 1000000007
#define F first
#define S second
#define PB push_back
#define MK make_pair
#define LEN(vale) strlen(vale)
#define SZ(vale) (int)vale.size()
#define SQ(A) ((A)*(A))
#define FI(i,fa,fb) for(int i=fa;i<fb;++i)
#define FD(i,fa,fb) for(int i=fa;i>fb;--i)
#define FT(it,S) for(__typeof((S).begin()) it=(S).begin();it!=(S).end();++it)
#define bits(vale) __builtin_popcount(vale)
#define VT vector
#define ALL(a) a.begin(),a.end()
#define LB (lower_bound)
#define UB (upper_bound)

#define SI(vale) scanf("%d",&vale)
#define PI(vale) printf("%d\n",vale)
#define PIS(vale) printf("%d ",vale)
#define SL(vale) scanf("%lld",&vale)
#define PL(vale) printf("%lld\n",vale)
#define PLS(vale) printf("%lld ",vale)
#define SS(vale) scanf("%s",vale)
#define PS(vale) printf("%s\n",vale)
#define NL printf("\n")
#define PLD(vale) cout << fixed; cout.precision(12); cout << vale <<"\n"
#define TCS() int testcase; SI(testcase);while(testcase--) 

typedef long long int LL;
typedef unsigned long long LLU;
typedef long double LD;
typedef pair<int,int> PI;
typedef pair<int,pair<int,int> > PII;
const int N = 100011;
int n;
const double EPS = 1e-9;
#define CT double
long double PIE = 3.141592653589793238;

struct Point {
    CT x, y;
    int id;
    Point() {}
    Point(CT x, CT y) : x(x), y(y) ,id(id) {}
    Point(const Point &p) : x(p.x), y(p.y) ,id(p.id)   {}
    Point operator + (const Point &p)  const { return Point(x+p.x, y+p.y); }
    Point operator - (const Point &p)  const { return Point(x-p.x, y-p.y); }
    Point operator * (double c)        const { return Point(x*c,   y*c  ); }
    Point operator / (double c)        const { return Point(x/c,   y/c  ); }
};
Point pivot;
Point a[N],cen,b[N];
struct Line {
    CT a,b,c;
};


CT dot(const Point &p,const Point &q)         { return p.x * q.x + p.y * q.y; }
double dist2(const Point &p,const Point &q)   { return dot(p - q,p - q); }
double dist(const Point &p,const Point &q) { return sqrt(SQ(p.x - q.x) + SQ(p.y - q.y));}
CT cross(const Point &p,const Point &q)   { return p.x * q.y - p.y*q.x;}
ostream &operator<<(ostream &os, const Point &p) {
    os << "(" << p.x << "," << p.y << ")";
}

bool operator < (const Point& a, const Point& b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}

bool operator == (const Point& a, const Point& b) {
    //change accordingly
    return abs(a.x-b.x) < EPS && abs(a.y-b.y) < EPS;
    //return make_pair(a.y, a.x) == make_pair(b.y, b.x);
}

Line make(Point a,Point b) {
    Line ret;
    if(a.y == b.y) ret.a = 0,ret.b = 1,ret.c = -a.y;
    else if(a.x == b.x) ret.a = 1,ret.b = 0 ,ret.c = -a.x;
    else {
        ret.a = (b.y - a.y);
        ret.b = (a.x - b.x);
        ret.c = b.x * a.y - a.x * b.y;
    }
    return ret;
}

bool isPointlie(Line l,Point p) {
    return (l.a*p.x + l.b*p.y + l.c == 0);
}

// rotate a Point CCW or CW around the origin
Point RotateCCW90(Point p)   { return Point(-p.y,p.x); }
Point RotateCW90(Point p)    { return Point(p.y,-p.x); }
// angle in radian
Point RotateCCW(Point p, double t) {
    return Point(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}

// project Point c onto line through a and b
// assuming a != b
Point ProjectPointLine(Point a, Point b, Point c) {
    return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project Point c onto line segment through a and b
Point ProjectPointSegment(Point a, Point b, Point c) {
    double r = dot(b-a,b-a);
    if (fabs(r) < EPS) return a;
    r = dot(c-a, b-a)/r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b-a)*r;
}
//return line perpendicular through line passing through a and b and passing through c
pair<Point,Point> Perpendicularline(Point a,Point b,Point c){
    c = ProjectPointLine(a,b,c);
    //  printf("%lf %lf %lf %lf %d\n",a.x,a.y,c.x,c.y,a==c);
    if(a == c) a = b;
    return make_pair(c,c+RotateCW90(a-c));
}

// compute distance from c to segment between a and b
double DistancePointSegment(Point a, Point b, Point c) {
    return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between Point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
        double a, double b, double c, double d) {
    return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(Point a, Point b, Point c, Point d) {
    return fabs(cross(b-a, c-d)) < EPS;
}

bool LinesCollinear(Point a, Point b, Point c, Point d) {
    return LinesParallel(a, b, c, d)
        && fabs(cross(a-b, a-c)) < EPS
        && fabs(cross(c-d, c-a)) < EPS;
}

// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(Point a, Point b, Point c, Point d) {
    if (LinesCollinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
                dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
        if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
            return false;
        return true;
    }
    if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
    if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
    return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
Point ComputeLineIntersection(Point a, Point b, Point c, Point d) {
    b = b - a; d = c - d; c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b * cross(c, d)/cross(b, d);
}

// compute center of circle given three Points
Point ComputeCircleCenter(Point a, Point b, Point c) {
    b = (a + b)/2;
    c = (a + c)/2;
    return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if Point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior Points, 0 for
// strictly exterior Points, and 0 or 1 for the remaining Points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking Point on polygon boundary
bool PointInPolygon(const vector<Point> &p, Point q) {
    bool c = 0;
    for (int i = 0; i < p.size(); i++){
        int j = (i+1)%p.size();
        if ((p[i].y <= q.y && q.y < p[j].y ||
                    p[j].y <= q.y && q.y < p[i].y) &&
                q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}

// determine if Point is on the boundary of a polygon
bool PointOnPolygon(const vector<Point> &p, Point q) {
    for (int i = 0; i < p.size(); i++)
        if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
            return true;
    return false;
}

// compute intersection of line through Points a and b with
// circle centered at c with radius r > 0
vector<Point> CircleLineIntersection(Point a, Point b, Point c, double r) {
    vector<Point> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r * r;
    double D = B * B - A * C;
    if (D < -EPS) return ret;
    ret.push_back(c + a + b*(-B + sqrt(D+EPS))/A);
    if (D > EPS)
        ret.push_back(c + a + b*(-B-sqrt(D))/A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<Point> CircleCircleIntersection(Point a, Point b, double r, double R) {
    vector<Point> ret;
    double d = sqrt(dist2(a, b));
    if (d > r + R || d + min(r, R) < max(r, R)) return ret;
    double x = (d * d - R * R + r * r)/(2 * d);
    double y = sqrt(r * r - x * x);
    Point v = (b - a)/d;
    ret.push_back(a + v * x + RotateCCW90(v) * y);
    if (y > 0)
        ret.push_back(a + v * x - RotateCCW90(v) * y);
    return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<Point> &p) {
    double area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

double ComputeArea(const vector<Point> &p) {
    return fabs(ComputeSignedArea(p));
}

Point ComputeCentroid(const vector<Point> &p) {
    Point c(0,0);
    double scale = 6.0 * ComputeSignedArea(p);
    for (int i = 0; i < p.size(); i++){
        int j = (i + 1) % p.size();
        c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
    }
    return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<Point> &p) {
    for (int i = 0; i < p.size(); i++) {
        for (int k = i + 1; k < p.size(); k++) {
            int j = (i + 1) % p.size();
            int l = (k + 1) % p.size();
            if (i == l || j == k) continue;
            if (SegmentsIntersect(p[i], p[j], p[k], p[l]))
                return false;
        }
    }
    return true;
}
typedef vector< Point > Polygon;
//#define REMOVE_REDUNDANT
CT area2(Point a, Point b, Point c) { return cross(b-a,c-a); }   // 2 times area
#ifdef REMOVE_REDUNDANT
bool between(const Point &a, const Point &b, const Point &c) {            // b is between a & c
    return abs(area2(a, b, c)) <EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0;
}
#endif

void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);

#ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
#endif
}

#define Det(a,b,c) ((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)) //returns (B-A)X(C-A)
bool in_convex(vector<Point>& l, Point p){
    int a = 1, b = l.size()-1, c;
    if (Det(l[0], l[a], l[b]) > 0) swap(a,b);         // orientation of area, a is above 0 and b below 0
    // Allow on edge --> if (Det... > 0 || Det ... < 0)
    if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
    while(abs(a-b) > 1) {
        c = (a+b)/2;
        if (Det(l[0], l[c], p) > 0) b = c; else a = c;
    }
    // Alow on edge --> return Det... <= 0
    return Det(l[a], l[b], p) < 0;
}

// +1 counter-clock | -1 clock | 0 collinear
int ccw(Point a,Point b,Point c) {
    int val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return (val > 0) ? -1 : 1 ;
    return 0;
}

bool polar_ord(Point a, Point b) {
    int ord = ccw(pivot,a,b);
    if(ord == 0)
        return dist(pivot,a) < dist(pivot,b);
    return (ord == -1);
}

/*
   int ih = 0;
   Point hull[N];
   VT<Point>cp;
   void graham() {
   int n = cp.size();
   if(n < 3) return ;
   int ly = 0; ih = 0;
   for(int i = 1;i < n;++i) {
   if(p[i].y == p[ly].y) {
   if(p[i].x < p[ly].x) ly = i;
   }
   else if(p[i].y < p[ly].y) ly = i;
   }
   swap(p[ly],p[0]);
   pivot = p[0];
   sort(p+1,p+n,polar_ord);
   for(int i = 0;i < 3; ++i) hull[ih++] = p[i]; 
   for(int i = 3;i < n; ++i) {
   Point top = hull[--ih];
   while(ih > 0 && ccw(hull[ih-1] , top,p[i]) != -1)
   top = hull[--ih];
   hull[ih++] = top; hull[ih++] = p[i];
   }
   }
   */



int main() {
    //clock_t tStart = clock();
    TCS() {
        cin>>n;
        vector<pair<LD,LD> >vec;
        vec.clear();
        cin>>cen.x>>cen.y;
        FI(i,0,n) {
            int x,y,u,v;
            cin>>x>>y;
            cin>>u>>v;
            a[i].x = x;  a[i].y = y;
            b[i].x = u;  b[i].y = v;
            Point p,q;
            p = ComputeLineIntersection(cen,a[i],Point(0,0),Point(1,0));
            q = ComputeLineIntersection(cen,b[i],Point(0,0),Point(1,0));
            if(p.x > q.x) swap(p,q);
            vec.PB(MK(p.x,q.x));
        }
        if(n == 0) {
            PI(1);
            continue;
        }
        sort(ALL(vec));
        int ans = 1;
        LD p = vec[0].S;
        for(int i = 1;i < SZ(vec);i++) {
            LD cl = vec[i].F;
            if(cl > p)
                ans++;
            p = max(p , vec[i].S);
        }
        PI(ans+1);
    }   
    //exectime();
    return 0; 
}


