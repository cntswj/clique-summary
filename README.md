##### Purpose
This software implements ideas in paper
[Redundancy-Aware Maximal Cliques](http://www.cse.cuhk.edu.hk/~jwang/publication/kdd13.pdf ) (see reference below).

Recent research efforts have made notable progress in improving
the performance of (exhaustive) _maximal clique enumeration_ (MCE).
However, existing algorithms still suffer from exploring the huge
search space of MCE. Furthermore, their results are often undesirable
as many of the returned maximal cliques have large overlapping parts.
This redundancy leads to problems in both computational efﬁciency and
usefulness of MCE.

We aim at providing a concise and complete summary of the set of
maximal cliques, which is useful to many applications. We propose
the notion of *t\-visible MCE* to achieve
this goal and design algorithms to realize the notion. The algorithm
_samples_ the set of original maxmal cliques, using a recursive
search with part of the search branches pruned. The algorithn is accompanied
with an optional _global filtering_ stage.

Two versions of the algorithm are available -- randomized and deterministic.
The former ensures summary quality under the notion of _visibility_
probabilistically, while the latter does definitely. Check the reference
paper for details.

One may use the reﬁned output space in efficient computations of, for example,
_top-k results with diversity_ and _interactive clique exploration_.


##### Program output
+  the summary
+  # of cliques in summary
+  top-10 cliques scored by coverage



##### Program parameters
1.  \[input file\]
2.  \[$\tau\]
3.  \[R|D\] \( _R_ for randomized algorithm, _D_ for deterministic\)
4.  \[G|L\] \( _G_ to switch on global filter, _L_ to switch off\)
5.  \[output_file\]  \(summary, one clique per line\)
  

##### Input file format
+  ascii file, adjacency lists
+  1st line:	_n_, _m_	for # of vertices/edges
+  ith line:	vertex _i_ described by	 _id_, _deg_, _list of neighbors_


##### Reference
> J. Wang, J. Cheng, A. Fu.  
> Redundancy-Aware Maximal Cliques.  
> *19th ACM SIGKDD Conference On Knowledge Discovery and Data Mining* (KDD'13), Chicago, USA
