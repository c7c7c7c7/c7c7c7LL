#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;

//   arrowsさん　mm(__) 借りてます

const double EPS = 1e-10;
const double INF = 1LL << 55;
const double PI = acos(-1);
#define equals(a, b) (fabs(a - b) < EPS)
#define lt(a, b) (a - b < -EPS)
#define le(a, b) (lt(a, b) || equals(a, b))

struct Point3D {
    double x, y, z;
    Point3D(){}
    Point3D(double x, double y, double z) : x{x}, y{y}, z{z} {}
  
    Point3D operator + (const Point3D& p) const
    {
        return Point3D(x + p.x, y + p.y, z + p.z);
    }
    
    Point3D operator - (const Point3D& p) const
    {
        return Point3D(x - p.x, y - p.y, z - p.z);
    }
    
    Point3D operator * (double k) const
    {
        return Point3D(x * k, y * k, z * k);
    }
    
    Point3D operator / (double k) const
    {
        return Point3D(x / k, y / k, z / k);
    }
};

double dot(const Point3D& a, const Point3D& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double norm(const Point3D& p)
{
    return dot(p, p);
}

double norm(const Point3D& a, const Point3D& b)
{
    return (a.x - b.x) * (a.x - b.x) +
           (a.y - b.y) * (a.y - b.y) +
           (a.z - b.z) * (a.z - b.z);
}

double abs(const Point3D& p)
{
    return sqrt(norm(p));
}

double dist(const Point3D& a, const Point3D& b)
{
    return abs(a - b);
}

double cross(const Point3D& a, const Point3D& b)
{
    return abs(Point3D(a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x));
}

Point3D cross_vec(const Point3D& a, const Point3D& b)
{
    return Point3D(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

double distance_PP(const Point3D& a, const Point3D& b)
{
    return abs(a - b);
}

istream& operator >> (istream& is, Point3D& p)
{
    return is >> p.x >> p.y >> p.z;
}

struct Segment {
    Point3D s, t;
    Segment() {}
    Segment(Point3D s, Point3D t) : s{s}, t{t} {}
};

using Line =  Segment;

Point3D proj(const Line &l, const Point3D &p)
{
    Point3D b = l.t - l.s;
    double t = dot(p - l.s, b) / norm(b);
    return l.s + b * t;
}

Point3D refl(const Line& l, const Point3D& p)
{    
    return p + (proj(l, p) - p) * 2.0;
}

double distance_LP(const Line& l, const Point3D& p)
{
    return abs(p - proj(l, p));
}

double distance_LL(const Line& a, const Line& b)
{
    Point3D v = cross_vec(a.t - a.s, b.t - b.s);
    Point3D p = a.s - b.s;
    if (abs(v) < EPS) return distance_LP(a, b.s);
    return abs(dot(v, p)) / abs(v);
}

/*
  線分と点の距離
 */
double distance_SP(const Segment& s, const Point3D& p)
{
    double a = dot(s.t - s.s, s.t - s.s);
    double b = dot(s.t - s.s, s.s - p);
    double c = dot(s.s - p, s.s - p);
    double t = -b / a;
    if (t < 0) return abs(s.s - p);
    if (t > 1) return abs(s.t - p);
    return a * t * t + 2 * b * t + c;
}

double distance_SS(const Segment& s1, const Segment& s2)
{
    // a*s + b*t = e
    // c*s + d*t = f
    Point3D v1 = s1.t - s1.s, v2 = s2.t - s2.s, v3 = s1.s - s2.s;
    double a = +dot(v1, v1);
    double b = -dot(v1, v2);
    double c = -dot(v1, v2);
    double d = +dot(v2, v2);
    double e = -dot(v1, v3);
    double f = +dot(v2, v3);
   
    double ans = INF;
    ans = min(ans, distance_SP(s1, s2.s));
    ans = min(ans, distance_SP(s1, s2.t));
    ans = min(ans, distance_SP(s2, s1.s));
    ans = min(ans, distance_SP(s2, s1.t));
 
    double det = a * d - b * c;
    if (det != 0) {
    double s = (d * e - b * f) / det;
    double t = (-c * e + a * f) / det;
    if (0 <= s && s <= 1 && 0 <= t && t <= 1) {
        ans = min(ans, distance_PP(s1.s + v1 * s, s2.s + v2 * t));
    }
    }
    return ans;
}

/*
  極座標（半径,緯度,経度）から直交座標（x,y,z）を求める
  ラジアン注意
  未確認,wikipediaより引用
 */
Point3D get_P3(double r, double ido, double keido)
{
    Point3D res;
    res.x = r * sin(ido) * cos(keido);
    res.y = r * sin(ido) * sin(keido);
    res.z = r * cos(ido);
    return res;
}

/*
  球面上にある二点間の球面距離
  ラジアン注意
*/
double gcdist(double r, double ido1, double keido1, double ido2, double keido2)
{
    double s = sin((ido1 - ido2) / 2.0), t = sin((keido1 - keido2) / 2.0);
    return 2.0 * r * asin(sqrt(max(0.0, s * s + cos(ido1) * cos(ido2) * t * t)));
}

/*
  球面上にある二点間の直線距離
  ラジアン注意
 */
double gcchord(double r, double ido1, double keido1, double ido2, double keido2)
{
    double c11 = cos(ido1), c12 = cos(keido1), c21 = cos(ido2), c22 = cos(keido2);
    double s11 = sin(ido1), s12 = sin(keido1), s21 = sin(ido2), s22 = sin(keido2);
    double dx = c11 * c12 - c21 * c22, dy = c11 * s12 - c21 * s22, dz = s11 - s21;
    return r * sqrt(dx * dx + dy * dy + dz * dz);
}

/*
  四面体の体積
  U : 辺AB の長さ
  V : 辺BC の長さ
  W : 辺CA の長さ
  u : 辺CD の長さ
  v : 辺AD の長さ
  w : 辺BD の長さ
  与えられた辺長から四面体が作れないときは, sqrt の引数が負になるかもしれない.
*/
double volume(double U, double V, double W, double u, double v, double w)
{
    double X = (w - U + v) * (U + v + w);
    double x = (U - v + w) * (v - w + U);
    double Y = (u - V + w) * (V + w + u);
    double y = (V - w + u) * (w - u + V);
    double Z = (v - W + u) * (W + u + v);
    double z = (W - u + v) * (u - v + W);
    double a = sqrt(x * Y * Z);
    double b = sqrt(y * Z * X);
    double c = sqrt(z * X * Y);
    double d = sqrt(x * y * z);
    
    return sqrt((-a + b + c + d) *
                (a - b + c + d) *
                (a + b - c + d) *
                (a + b + c - d)) / (192 * u * v * w);
}

struct Sphere {
    Point3D p;
    double r;
    Sphere() {}
    Sphere(Point3D p, double r) : p{p}, r{r} {}

    double surfaceArea()
    {
    return PI * r * r * 4.0;
    }

    double volume()
    {
    return PI * r * r * r * 4.0 / 3.0;
    }
};

istream& operator >> (istream& is, Sphere& sp)
{
    return is >> sp.p >> sp.r;
}

bool cover(const Sphere& s, const Point3D& p)
{
    return (abs(s.p - p) < s.r + EPS);
}

const int COUNTER_CLOCKWISE = +1;
const int CLOCKWISE         = -1;
const int ONLINE_BACK       = +2;
const int ONLINE_FRONT      = -2;
const int ON_SEGMENT        = +0;
using Vector3D = Point3D;

// ccw ( Line (p0,p1) ,p2 )
 
int ccw(const Point3D& p0, const Point3D& p1, const Point3D& p2)
{
    Vector3D a = p1 - p0;
    Vector3D b = p2 - p0;
    if (abs(cross(a, b)) > EPS)  return COUNTER_CLOCKWISE;
    if (abs(cross(a, b)) < -EPS) return CLOCKWISE;
    if (dot(a, b) < -EPS)        return ONLINE_BACK;
    if (norm(a) < norm(b))       return ONLINE_FRONT;
    return ON_SEGMENT;
}

/*
  球と直線の交差判定
*/
bool intersect_SL(const Sphere& s, const Line& l)
{
    return distance_LP(l, s.p) <= s.r + EPS;
}

/*
  球と直線の交点
*/


vector<Point3D> crosspoint_SL(const Sphere& s, const Line& l)
{
    /* 交差しない -> 交点なし */
    if (!intersect_SL(s, l)) {
        return {};
    }
    
    Point3D x = proj(l, s.p);
    Vector3D vp = x - s.p;
    Vector3D uv = (l.t - l.s) / abs(l.t - l.s);
    double t = sqrt(s.r * s.r - norm(vp));
    return {x - uv * t, x + uv * t};
}

Point3D crosspoint_SL1(const Sphere& s, const Line& l)
{
    /* 交差しない -> 交点なし */
    if (!intersect_SL(s, l)) {
        return {};
    }
    
    Point3D x = proj(l, s.p);
    Vector3D vp = x - s.p;
    Vector3D uv = (l.t - l.s) / abs(l.t - l.s);
    double t = sqrt(s.r * s.r - norm(vp));
    return x - uv * t;
}

int main(){
    int n;
    while(cin>>n,n){
        Point3D x,ans;
        Sphere s[n];
        cin>>x;
        rep(i,n)cin>>s[i];
        Line A(Point3D(0,0,0),x);
        while(1){
            double MIN=1e9;
            int idx=-1;
            rep(i,n)if(intersect_SL(s[i],A)){
                Point3D y=crosspoint_SL1(s[i],A);
                if(ccw(A.s,A.t,y)==ON_SEGMENT||ccw(A.s,A.t,y)==ONLINE_FRONT){
                    double dist=sqrt(norm(y,A.s));
                    if(dist<MIN){
                        MIN=dist;
                        idx=i;
                    }
                }
            }
            if(idx==-1)break;
            ans=crosspoint_SL1(s[idx],A);
            A=Line( ans ,refl( Line( s[idx].p , ans ) ,A.s )  );
        }
        printf("%.9f %.9f %.9f\n",ans.x,ans.y,ans.z);
    }
}