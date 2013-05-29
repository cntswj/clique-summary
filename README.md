Function
------------
summarize cliques in a graph -- removing redundancy from overlapping cliques

Output
------------
+  # cliques in summary
+  top-10 cliques scored by coverage
+  a summary

Program parameters
------------
1.  input file
2.  tau
3.  R|D	// R for randomized algorithm, D for deterministic
4.  G|L	// G to switch on global filter, L to switch off
5.  output file	// for saving summary

Input format
------------
+  ascii file, adjacency lists
+  1st line:	n m	// # of vertices/edges
+  ith line:	vertex i	// id, deg, list of neighbors

Refrence
------------
[1] J. Wang, J. Cheng, A. Fu
"Redundancy-Aware Maximal Cliques" (SIGKDD'13)
