# Descreption, first methods, first tests :
Consider points $(c_k)_{0 \leq k < K}$ in $\mathbb{R}^2$, called centers, and a distance function $d$ on $\mathbb{R}^2$. These points allow us to partition the entire space into $K$ regions $(R_k)_{0 \leq k < K}$ such that $x \in R_k$ if and only if, for all $l \neq k$, $d(x, c_k) \leq d(x, c_l)$; in other words, $x \in R_k$ if and only if $x$ is closer to $c_k$ than to any other center.

Given a finite set of points $P$ in $\mathbb{R}^2$, the goal of this exercise is to construct an algorithm that partitions $P$ into $K$ subsets $(P_k)_{0 \leq k < K}$ with $P_k \subset R_k$. This involves, for each $k$, grouping the points in $P$ that are closest to $c_k$ into a set $P_k$. This process is known as clustering.

# More advanced methods :

The `classify` method reads `nb` data points from an input stream and inserts them into the appropriate cluster $P_k$. We assume that the file behind the input stream is formatted as follows:

$x_{1}$  $y_{1}$

$x_{2}$  $y_{2}$

$x_{3}$  $y_{3}$

....

where the $x_i$ and $y_i$ are real numbers corresponding to the coordinates of a point in $\mathbb{R}^2$.

The `mean_distance_square` method returns a vector containing, for each cluster, the mean squared distance of the points to the center of the cluster. For each $0 \leq k < K$, the result vector contains:

$$
v_k = \frac{1}{|P_k|} \sum_{x \in P_k} d(c_k, x)^2
$$

where $d(c_k, x)$ represents the distance between the center $c_k$ and point $x$ in the cluster $P_k$.

### Adding a New Center

Suppose we have already classified a set $P$ of $N$ points around $K$ centers $(c_k)_{0 \leq k < K}$ by constructing the $K$ clusters $(P_k)_{0 \leq k < K}$. We then decide to insert a new center $c'$ and move from $K$ centers to $K + 1$ centers, with $c_K = c'$. It is not necessary to recompute everything; we can simply traverse each existing cluster and move the relevant points to the new cluster according to the following algorithm:

- Introduce an empty set $S$ (the future cluster associated with $c'$).
- For each integer $0 \leq k < K$:
  - Introduce an empty set $P'_k$.
  - Traverse all elements of $P_k$ and, for each point $p$, add it to $S$ if $d(c', p) < d(c_k, p)$, otherwise add it to $P'_k$.
  - Replace $P_k$ with $P'_k$.
- Finally, the cluster $P_K$ associated with the new point $c_K = c'$ is given by the set $S$.

The method `int Voronoi_classifier::add_center(Point2D new_center);` adds a new cluster at the end of the list of clusters, with the center $c'$ given by `new_center`, and updates the clusters according to the above algorithm.