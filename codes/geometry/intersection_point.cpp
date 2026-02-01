Point lineInter(Point a, Point b, Point c, Point d) {
    return a + (b - a) * ((c - a).cross(d - c) / (b - a).cross(d - c));
}
