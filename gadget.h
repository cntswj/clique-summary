#ifndef GADGET_H
#define GADGET_H

#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

#include "graph.h"

void *alloc(int n);
void list2adj(char *ifname, char *ofname);
void vprint(VI v, FILE *fout=stdout);
vector<int> operator+(vector<int> &v1, vector<int> &v2);
vector<int> operator-(vector<int> &v1, vector<int> &v2);
vector<int> operator*(vector<int> &v1, vector<int> &v2);

#endif // GADGET_H
