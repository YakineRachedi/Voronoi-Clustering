#ifndef VORONOI_CLASSIFICATION_CLASS
#define VORONOI_CLASSIFICATION_CLASS

#include <iostream>
#include <set>
#include <vector>
#include <fstream>

// to describe the points in R^2
struct Point2D {
	double x;
	double y;
	double dist_2(Point2D u) const { return (x-u.x)*(x-u.x)+(y-u.y)*(y-u.y); } // usage: p1.dist_2(p2) gives the distance between p1 and p2.
	bool operator<(Point2D u) const { if( x < u.x) return true; else if (x>u.x) return false; else return y<u.y; } // necessary for std::set
};

/*
Each cluster of points will be described by a center 𝑐 (a point in 𝑅^2) and the points close to this center, 
			provided in the form of a set of points
*/
struct Cluster {
	Point2D center; // center of the cluster c
	std::set<Point2D> points; // set of points x_i close to the center c
};

class Voronoi_classifier {
	private:
		std::vector< Cluster > clusters; // vector (list) of clusters (c_k, P_k)
		int nb_points; // number of data points already classified.
		/* Class invariants:
		(1) All points in clusters[i].close_points are closer to clusters[i].center than to any other center
		(2) Each point appears only once in total
		(3) nb_points is the total number of points, i.e., the sum of the sizes of the clusters.
		*/
	public:
        Voronoi_classifier(const std::vector<Point2D> & initial_centers);
		int nb_of_clusters() const {return this->clusters.size();}
		int nb_of_data_points() const {return this-> nb_points;}			
		void add_point(Point2D);
		friend std::ostream & operator << (std::ostream &,const Voronoi_classifier &);
		std::vector<int> cluster_sizes() const;
		void clear_clusters();
		
};

#endif
