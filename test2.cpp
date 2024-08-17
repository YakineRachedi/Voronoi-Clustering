#include "voronoi_classif.hpp"
//#include "voronoi_classif.cpp"
#include "voronoi_classif_without_algorithm_library.cpp"
#include <fstream>

using namespace std;

int main(){
    const int N = 500;
    vector<Point2D> centers{ Point2D{0,0}, Point2D{5,3}, Point2D{-2,4}, Point2D{-1,-4}};
    Voronoi_classifier Data(centers);
    ifstream input("./cloud.dat");
    Data.classify(input,N);
    input.close();

    cout << "Number of data points : " << Data.nb_of_data_points() << "\n";
    cout << "Number of clusters : " << Data.nb_of_clusters() << "\n";
    cout << "Number of points in each cluster : ";
    for(auto & nb_pts : Data.cluster_sizes()){
        cout << nb_pts << " ";
    }
    cout << "\n";
    cout << "Values of v_k : ";
    for(auto & MeanDistSquare : Data.mean_distance_square()){
        cout << MeanDistSquare << " ";
    }
    cout << "\n";

    Data.add_center(Point2D{0,-1});
    cout << "Clusters size after adding new center : ";
    for(auto & nb_pts : Data.cluster_sizes()) {
        cout << nb_pts << " ";
    }
    cout << "\n";

    ofstream output("clusters_rep.dat");
    Data.print_color(output);
    output.close();

    Point2D new_point = {-7,7};
    Data += new_point;
    cout << "After adding point with += " << Data << "\n";
    return 0;
}