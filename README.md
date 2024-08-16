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