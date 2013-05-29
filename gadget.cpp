#include "gadget.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

typedef vector<int> VI;
using namespace std;

void *alloc(int n) {
    return malloc(sizeof(int)*(n+1));
}

VI operator+(VI &v1, VI &v2) {
    VI res(v1.size()+v2.size());
    int sz=set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin()) - res.begin();
    res.resize(sz);
    return res;
};

VI operator-(VI &v1, VI &v2) {
    VI res(v1.size());
    int sz=set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin()) - res.begin();
    res.resize(sz);
    return res;

};

VI operator*(VI &v1, VI &v2) {
    VI res(v1.size());
    int sz=set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin()) - res.begin();
    res.resize(sz);
    return res;
};

void vprint(VI v, FILE *fout) {
    int col=8;
    for (int i=0; i<v.size(); ++i) {
        fprintf(fout, "%-8d", v[i]);
        if ((i+1)%col==0)
            fprintf(fout, "\n");
    }
    if (v.size()%col!=0)
    	fprintf(fout, "\n");
}

void list2adj(char *ifname, char *ofname) {

    vector< VI > g;
    FILE *fi = fopen(ifname, "r");
    FILE *fo = fopen(ofname, "w");
    int n,m;
    fscanf(fi, "%d%d", &n, &m);
    g.resize(n);
    for (int i=0; i<m; ++i) {
        int v1, v2;
        fscanf(fi, "%d%d", &v1, &v2);
        assert(v1>=0 && v1<n);
        assert(v2>=0 && v2<n);
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    for (int i=0; i<n; ++i) {
        sort(g[i].begin(), g[i].end());
        g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
        int deg=g[i].size();
        //copy(vec.begin(), vec.end(), ostream_iterator<int> (cout, " "));
        fprintf(fo, "%d %d", i, deg);
        for(int j=0; j<deg; ++j)
            fprintf(fo, " %d", g[i][j]);
        fprintf(fo, "\n");
    }

    fclose(fi);
    fclose(fo);
}
