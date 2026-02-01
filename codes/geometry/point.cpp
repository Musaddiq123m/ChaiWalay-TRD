class Point {
public:
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
 
    Point& operator+=(const Point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    Point& operator-=(const Point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    Point& operator*=(int t) {
        x *= t;
        y *= t;
        return *this;
    }
    Point& operator/=(int t) {
        x /= t;
        y /= t;
        return *this;
    }
 
    Point operator+(const Point &t) const {
        return Point(*this) += t;
    }
    Point operator-(const Point &t) const {
        return Point(*this) -= t;
    }
    Point operator*(int t) const {
        return Point(*this) *= t;
    }
    Point operator/(int t) const {
        return Point(*this) /= t;
    }

    int cross(const Point &other) const {
        return x * other.y - y * other.x;
    }

    int orient(const Point& b, const Point& c) const {
        // this point acts as origin
        // returns cross product of vectors (b-a) and (c-a)
        return (b - *this).cross(c - *this);
    }
    friend Point operator*(int a, Point b) {
        return b * a;
    }
 
    friend istream& operator>>(istream &in, Point &p) {
        in >> p.x >> p.y;
        return in;
    }
 
    friend ostream& operator<<(ostream &out, const Point &p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};