#include "voronoi_classif.hpp"
#include "voronoi_classif.cpp"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main() {
    std::vector<Point2D> centers{ Point2D{0.2,0.2}, Point2D{0.8,0.8}, Point2D{0.3,0.7} };
    Voronoi_classifier VC(centers);
    VC.add_point(Point2D{0.5,0.});
    VC.add_point(Point2D{0.75,0.6});
    VC.add_point(Point2D{1.,0.2});
    cout << "--- VC contains " << VC.nb_of_clusters() << " clusters and "
         << VC.nb_of_data_points() << " points.\n";
    std::vector<int> nbs = VC.cluster_sizes();
    cout << "--- The sizes of the three clusters are:\n";
        for(int n : nbs) { cout << n << "\n"; }
    cout << "--- The clusters are given by:\n" << VC;
    VC.clear_clusters();
    cout << "--- After clearing, there are " << VC.nb_of_clusters() << " centers and "
         << VC.nb_of_data_points() << " points.\n";
    return 0;
}
