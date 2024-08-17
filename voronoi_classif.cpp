#include "voronoi_classif.hpp"
#include <algorithm>
#include <numeric>
using namespace std;

Voronoi_classifier::Voronoi_classifier(const vector<Point2D> & initial_centers) : clusters(initial_centers.size()), nb_points(0) {
			for(int i = 0; i < initial_centers.size(); i++){
				clusters[i].center = initial_centers[i];
			}
		}
/*
Add a new data point to the corresponding set according to the following algorithm:
— Determine which center the point p is closest to;
— Insert the point p into the associated set.
*/

void Voronoi_classifier::add_point(Point2D p){
	auto closest_point = min_element(clusters.begin(),clusters.end(),
		[p](const Cluster & c1, const Cluster & c2) {return p.dist_2(c1.center) < p.dist_2(c2.center);});
	closest_point->points.insert(p);
	nb_points++;
    return;
}

ostream & operator << (ostream & out,const Voronoi_classifier & vc){
    if(vc.nb_of_data_points() == 0){
        out << "Empty" << endl;
    }
    for(int i = 0; i < vc.clusters.size(); i++){
        out << "( " << vc.clusters[i].center.x << "," << vc.clusters[i].center.y << " ) \n";
        for(const Point2D & p : vc.clusters[i].points){
            out << "( " << p.x << " , " << p.y << " ) \n";
        }
    }
    return out;
}

vector<int> Voronoi_classifier::cluster_sizes() const{
    vector<int> result(clusters.size());
    transform(clusters.begin(),clusters.end(),result.begin(),[](const Cluster & c) {return c.points.size();});
    return result;
}

void Voronoi_classifier::clear_clusters(){
    for_each(clusters.begin(), clusters.end(), [](Cluster & c) { c.points.clear(); });
}

void Voronoi_classifier::classify(std::istream & data_points, int nb_of_points){
    Point2D current_point;
    int i = 0;
    while(i < nb_of_points){
        data_points >> current_point.x >> current_point.y;
        add_point(current_point);
        i++;
    }
}

vector<double> Voronoi_classifier::mean_distance_square() const {
    vector<double> result(clusters.size());
    transform(clusters.begin(),clusters.end(),result.begin(),
        [](const Cluster & c) {return accumulate(c.points.begin(),c.points.end(),0.,
        [c](double s,const Point2D & p) {return s + c.center.dist_2(p);}) / c.points.size()  ;});
    return result;
}