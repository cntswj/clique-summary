#ifndef CLIQUEHOLDER_H
#define CLIQUEHOLDER_H

#include <set>
#include <map>
#include "gadget.h"
#include "graph.h"

class CliqueHolder
{
    public:
        CliqueHolder();
        bool insert(VI &C);
        int topk(int k);
        void init(double _ltau, bool _filter, FILE *_fout);
        int count() { return cliques.size();}
        VI largest() { return maxcli; }
        int average() { return sumsize/cliques.size(); }
        inline VI last() { return L; }
        inline double getTau() { return tau; }

    private:
        FILE *fout;
        bool filter;
        long long cnt, sumsize;
        int ls;
        double tau;
        VVI cliques;
        VI maxcli, L, D;
        VI scores;
        multimap<int,int> lv;

        int updateScore(int i, VI &D);
        bool passFilter(VI &C);
        bool exactFilter(VI &C1, VI &C2, int t);
};

#endif // CLIQUEHOLDER_H
