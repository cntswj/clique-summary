#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "graph.h"
#include "gadget.h"
#include "cliqueholder.h"

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

Graph g;
double tau;
bool randomized, filter, dotopk;
char est;

CliqueHolder holder;
VVI gv;
VI tmp, unit(1);
int *lookup;
int ntofilter;
VI L, D, E, X, hg;
FILE *fcliques;

void degeneracyOrdering() {

    int n=g.V();
    int *bin = (int*)alloc(n);
    int *pv = (int*)alloc(n);
    int *pos = (int*)alloc(n);
    int *tdeg = (int*)alloc(n);
    memset(bin, 0, sizeof(int)*n);
    memset(tdeg, 0, sizeof(int)*n);

    for (int i=0; i<n; ++i) tdeg[i] = g.deg(i);
    for (int i=0; i<n; ++i) ++bin[tdeg[i]];

    int c=0;
    for (int i=0; i<n; ++i) {
        int d=bin[i];
        bin[i] = c;
        c += d;
    }
    for (int i=0; i<n; ++i) {
        pos[i]=bin[tdeg[i]];
        pv[pos[i]]=i;
        ++bin[tdeg[i]];
    }
    for (int i=n-1; i>0; --i)
        bin[i]=bin[i-1];
    bin[0]=0;

    for (int i=0; i<n; ++i) {
        int v=pv[i], dv=tdeg[v];
        lookup[v]=i;
        for (int j=0; j<gv[v].size(); ++j) {
            int w=gv[v][j], dw=tdeg[w];
            if (dw>dv) {
                int pw=pos[w];
                int pt=bin[dw];
                int t=pv[pt];
                if (t!=w) {
                    pos[w]=pt, pos[t]=pw;
                    pv[pw]=t, pv[pt]=w;
                }
                ++bin[dw];
                --tdeg[w];
            }
        }
    }

    free(bin);
    free(pos);
    free(pv);
    free(tdeg);
}

inline double probSample(double r) {
    return r<tau? (tau-r)/(1-r) : 0;
}

inline double probKeep(double r, double pprod, int d) {
    return pow(probSample(r)/pprod, 1.0/d);
}

inline bool keepBranch(double pr) {
    return double(rand())/RAND_MAX < pr;
}

void cliSearch(VI &C, VI &cand, VI &prev, double pprod) {

    // maximal clique detected
    if (cand.empty() && prev.empty()) {
        ++ntofilter;
        holder.insert(C);
        return;
    }

    // upper-bound height
    int nc=cand.size();
    int maxdep=nc;

    // lower-bound ratio
    L=holder.last();
    X=C*L;
    E= cand-L;
    int cx=X.size(), ce=E.size(), cc=C.size();
    double minr=1.0;
    for (int t=1; t<=maxdep; ++t) {
        double tr= double(max(t-ce,0)+cx)/(cc+t);
        minr = min(tr, minr);
    }

    double pr=1.0;
    if (!randomized) {
        if (minr>holder.getTau())
            return;
    }
    else {
        pr = probKeep(minr, pprod, maxdep);
        if (!keepBranch(pr))
            return;
    }

    // find pivot
    int maxdeg=-1, pivot=-1;
    tmp=cand+prev;
    for (int i=0; i<tmp.size(); ++i) {
        int v=tmp[i];
        int dv=(gv[v]*cand).size();
        if (dv>maxdeg)
            maxdeg=dv, pivot = v;
    }

    // grow from each vertex in doing
    VI doing(cand-gv[pivot]);
    for (int i=0; i<doing.size(); ++i) {
        int v = doing[i];
        unit[0]=v;
        C= C+unit;
        cand= cand-unit;
        VI candt(cand*gv[v]), prevt(prev*gv[v]);
        cliSearch(C, candt, prevt, pprod*pr);
        unit[0]=v;
        C= C-unit;
        prev= prev+unit;
    }
}

int main(int argc, char **argv)
{
    srand( time(NULL) );

    if (argc<6) {
        printf("Usage: \t   1) graph_file\n\t
                            2) tau\n\t
                            3) R(andomized/D(eterministic)\n\t
                            4) G(lobal)/L(ocal)\n\t
                            5) output_file\n");
        exit(1);
    }

    g.build(argv[1]);
    tau = atof(argv[2]);
    randomized = (argv[3][0]=='R');
    filter = (argv[4][0]=='G');
    fcliques = fopen(argv[5], "w");


    gv.resize(g.V());
    VI vg;
    for (int i=0; i<g.V(); ++i) {
        vg.push_back(i);
        for (int j=0; j<g.deg(i); ++j)
            gv[i].push_back(g.dest(i,j));
    }

    lookup = (int*)alloc(g.V());
    degeneracyOrdering();

    // "oding" doing array in outer loo
    VI oc, odoing, ocand, oprev;
    int opvt=0;
    for (int i=0; i<g.V(); ++i) {
        odoing.push_back(i);
        if (g.deg(i)>g.deg(opvt))
            opvt=i;
    }
    odoing=odoing-gv[opvt];

    // search outer loop
    holder.init(tau, filter, fcliques);
    int nod=odoing.size();
    int percentile = nod/100+1;
    for (int ci=0; ci<nod; ++ci) {
        // show progress
        if (percentile==0 || (ci+1)%percentile==0) {
           int percent=(ci+1)*100/nod;
           printf("%d%%\n", percent);
        }
        int i=odoing[ci];

        ocand.clear();
        oprev.clear();
        for (int j=0; j<g.deg(i); ++j) {
            int v= g.dest(i,j);
            if (lookup[i]<lookup[v])
                ocand.push_back(v);
            else
                oprev.push_back(v);
        }

        oc.clear();
        oc.push_back(i);
        cliSearch(oc, ocand, oprev, 1.0);
    }

    // reporting
    printf("# of samples (w. local filter)\n%d\n", ntofilter);
    printf("\n");
    if (filter)
        printf("# of samples (w. global filter)\n%d\n", holder.count());
    holder.topk(10);

    fclose(fcliques);
    free(lookup);
    return 0;
}
