#include "graph.h"
#include "gadget.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

Graph::Graph() {
    n=m=0;
    degree=start=elist=NULL;
}

Graph::Graph(char *fname) {
    if (n>0) {
        fprintf(stderr, "graph already loaded\n");
        exit(1);
    }
    build(fname);
}

Graph::~Graph() {
    if (start != NULL) {
        free(start);
        free(degree);
        free(elist);
    }
}

int Graph::V() {
    return n;
}

int Graph::E() {
    return m;
}

void Graph::build(char *fname) {

    FILE *fg = fopen(fname, "r");

    fscanf(fg, "%d%d", &n, &m);
    start = (int*)alloc(n);
    degree = (int*)alloc(n);
    elist = (int*)alloc(m);

    gvec.clear();
    gvec.resize(n);

    int ecur=0;
    for (int i=0; i<n; ++i) {
        int u, d, newd=0;
        fscanf(fg, "%d%d", &u, &d);
        assert(u<n && u>=0);
        start[u] = ecur;
        for (int j=0; j<d; ++j) {
            int v;
            fscanf(fg, "%d", &v);
            if (v==u) continue;
            assert(v<n && v>=0);
            elist[ecur++] = v;
            gvec[u].push_back(v);
            ++newd;
        }
        degree[u] = newd;
        sort(elist+start[u], elist+start[u]+newd);
    }
    fclose(fg);
}

int Graph::dest(int v, int k) {
    return elist[start[v]+k];
}

int Graph::deg(int v) {
    return degree[v];
}

void Graph::print() {

    for (int i=0; i<n; ++i) {
        printf("%d:", i+1);
        for (int j=0; j<deg(i); ++j) {
            int v = dest(i,j)+1;
            printf(" %d", v);
        }
        printf("\n");
    }
}
