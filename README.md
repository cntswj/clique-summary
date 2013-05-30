##### Purpose
This software implements ideas in kdd'13 paper [Redundancy-Aware Maximal Cliques](http://www.cse.cuhk.edu.hk/~jwang/publication/kdd13.pdf ).

Recent research efforts have made notable progress in improving
the performance of (exhaustive) _maximal clique enumeration_ (MCE).
However, existing algorithms still suffer from exploring the huge
search space of MCE. Furthermore, their results are often undesirable
as many of the returned maximal cliques have large overlapping parts.
This redundancy leads to problems in both computational efﬁciency and
usefulness of MCE.

We aim at providing a concise and complete summary of the set of
maximal cliques, which is useful to many applications. We propose
the notion of *t-visible MCE* to achieve
this goal and design algorithms to realize the notion. We may use
the reﬁned output space in efficient computations of, for example,
_top-k results with diversity_ and _interactive clique exploration_.


##### Program output
+  # cliques in summary
+  top-10 cliques scored by coverage
+  a summary


##### Program parameters
1.  input file
2.  tau
3.  R | D // R for randomized algorithm, D for deterministic
4.  G | L  // G to switch on global filter, L to switch off
5.  output file  // for saving summary
  

##### Input file format
+  ascii file, adjacency lists
+  1st line:	n m	// # of vertices/edges
+  ith line:	vertex i	// id, deg, list of neighbors


##### Reference
> J. Wang, J. Cheng, A. Fu.  
> Redundancy-Aware Maximal Cliques.  
> *19th ACM SIGKDD Conference On Knowledge Discovery and Data Mining* (KDD'13), Chicago, USA
