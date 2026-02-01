// 0 = OUTSIDE, 1 = INSIDE, 2 = BOUNDARY
int pointInPolygon(const vector<Point>& poly, const Point& p) {
    int n = poly.size();
    Point out = {p.x + 1, 3000000001LL};
    int intersections = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (poly[i].orient(poly[j], p) == 0) {
            int mnx = min(poly[i].x, poly[j].x);
            int mxx = max(poly[i].x, poly[j].x);
            int mny = min(poly[i].y, poly[j].y);
            int mxy = max(poly[i].y, poly[j].y);
            if (p.x >= mnx && p.x <= mxx &&
                p.y >= mny && p.y <= mxy) {
                return 2; // BOUNDARY
            }
        }
        intersections += intersect(p, out, poly[i], poly[j]);
    }

    if (intersections % 2 == 1)
        return 1; // INSIDE
    else
        return 0; // OUTSIDE
}
