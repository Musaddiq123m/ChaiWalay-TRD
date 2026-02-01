#include<bits/stdc++.h>
using namespace std;

vi topoSort(const vector<vi>& gr) {
    vi indeg(gr.size()), q;
    for (auto& li : gr)
        for (int x : li)
            indeg[x]++;

    forn(i,0,gr.size())
        if (indeg[i] == 0)
            q.push_back(i);

    forn(j,0,q.size())
        for (int x : gr[q[j]])
            if (--indeg[x] == 0)
                q.push_back(x);

    return q; 
}