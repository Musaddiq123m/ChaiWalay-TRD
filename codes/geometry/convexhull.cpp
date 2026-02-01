vector<Point> convexhull(vector<Point> &p){
    sort(all(p), [](const Point &a, const Point &b){
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
 
    vector<Point> convex;
    forn(rep,0,2){
        int s = convex.size();
        for(Point c : p){
            while((int)convex.size() - s >= 2){
                Point a = convex.end()[-2];
                Point b = convex.end()[-1];
                if(a.orient(b,c) <= 0) break;
                convex.pop_back();
            }
            convex.push_back(c);
        }
        convex.pop_back();
        reverse(all(p));
    }
    return convex;
}