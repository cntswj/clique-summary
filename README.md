##### Purpose
implements ideas in kdd'13 paper [Redundancy-Aware Maximal Cliques][1]:
+  computes a summary of all maximal cliques in a graph
+  free of  redundancy from overlapping cliques


##### Program output
+  # cliques in summary
+  top-10 cliques scored by coverage
+  a summary
+  

##### Program parameters
1.  input file
2.  tau
3.  R | D // R for randomized algorithm, D for deterministic
4.  G | L  // G to switch on global filter, L to switch off
5.  output file  // for saving summary
6.  

##### Input file format
+  ascii file, adjacency lists
+  1st line:	n m	// # of vertices/edges
+  ith line:	vertex i	// id, deg, list of neighbors


##### Reference
[1]: http://www.cse.cuhk.edu.hk/~jwang/publication/kdd13.pdf 
"Redundancy-Aware Maximal Cliques (ACM SIGKDD'13)" J. Wang, J. Cheng, A. Fu.
