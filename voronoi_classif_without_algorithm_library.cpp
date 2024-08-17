#include "voronoi_classif.hpp"
using namespace std;

// Implementation of the constructors :

Voronoi_classifier::Voronoi_classifier(const vector<Point2D> & initial_centers) : clusters(initial_centers.size()), nb_points(0) {
			for(int i = 0; i < initial_centers.size(); i++){
				clusters[i].center = initial_centers[i];
			}
		}

Voronoi_classifier::Voronoi_classifier(std::istream & input_centers): clusters(), nb_points(0) {
	int nb_centers;
	input_centers >> nb_centers;
	clusters.resize(nb_centers);
	for( Cluster & c : clusters ) {
		input_centers >> c.center.x >> c.center.y; 
	}
}

/*
Add a new data point to the corresponding set according to the following algorithm:
— Determine which center the point p is closest to;
— Insert the point p into the associated set.
*/

void Voronoi_classifier::add_point(Point2D p){
	int min_index = 0;
	double dist = clusters[0].center.dist_2(p);
	for(int i = 0; i < clusters.size(); i++){
		if(clusters[i].center.dist_2(p) < dist){
			dist = clusters[i].center.dist_2(p);
			min_index = i;
		}
	}
	clusters[min_index].points.insert(p);
	nb_points++;
    return;
}

ostream & operator << (ostream & out,const Voronoi_classifier & vc){
    if(vc.nb_of_data_points() == 0){
        out << "\tEmpty" << endl;
    }
    for(int i = 0; i < vc.clusters.size(); i++){
        out << "Center : ( " << vc.clusters[i].center.x << "," << vc.clusters[i].center.y << " ) \n";
        for(const Point2D & p : vc.clusters[i].points){
            out << "\t( " << p.x << " , " << p.y << " ) \n";
        }
    }
    return out;
}
vector<int> Voronoi_classifier::cluster_sizes() const{
    vector<int> result(nb_of_clusters());
    for(int i = 0; i < nb_of_clusters(); i++){
        result[i] = this->clusters[i].points.size();
    }
    return result;
}

void Voronoi_classifier::clear_clusters() {
    this->nb_points = 0;
    for(Cluster & c : clusters){
        c.points.clear();
    }
    return;
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
vector<double> Voronoi_classifier::mean_distance_square() const{
    vector<double> result;
    double sum_distance = 0.;
    for(const Cluster & c : clusters){
        for(const Point2D & p : c.points){
            sum_distance += p.dist_2(c.center);
        }
        sum_distance /= double(c.points.size());
        result.push_back(sum_distance);
        sum_distance = 0.;
    }
    return result;
}

int Voronoi_classifier::add_center(Point2D new_center){
    set<Point2D> new_points_in_cluster;
    for(Cluster & c : clusters){
        set<Point2D> remaining_points;
        for(const Point2D & p : c.points){
            if(p.dist_2(new_center) < p.dist_2(c.center)){
                new_points_in_cluster.insert(p);
            }
            else{
                remaining_points.insert(p);
            }
        }
        c.points.clear();
        c.points.insert(remaining_points.begin(),remaining_points.end());
    }
    Cluster new_cluster;
    new_cluster.center = new_center;
    new_cluster.points = move(new_points_in_cluster);
    clusters.push_back(new_cluster);
    int new_size = clusters.back().points.size();
    return new_size;
}

void Voronoi_classifier::print_color(std::ostream & output) const{
    int index = 0;
    for(const Cluster & c : clusters){
        output << c.center.x << " " << c.center.y << " " << "-1" << "\n";
        for(const Point2D & p : c.points){
            output << p.x << " " << p.y << " " << index << "\n";
        }
        index++;
    }
}

void Voronoi_classifier::operator += (Point2D data_point_to_add) {
    int index = 0;
    double min_d = clusters[0].center.dist_2(data_point_to_add);
    for(int i = 0; i < clusters.size(); i++) {
        if(min_d < clusters[i].center.dist_2(data_point_to_add)) {
            min_d = clusters[i].center.dist_2(data_point_to_add);
            index = i;
        } 
    }
    clusters[index].points.insert(data_point_to_add);
    nb_points++;
}