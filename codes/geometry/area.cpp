int area = 0;
forn(i,0,n){
    area += p[i].cross(p[(i + 1) % n]);
}
cout<< abs(area) << nl;