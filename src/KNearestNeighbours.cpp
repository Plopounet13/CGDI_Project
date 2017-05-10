//
// Created by remi on 02/05/17.
//

#include <algorithm>
#include <unordered_map>
#include "KNearestNeighbours.h"

#define NB_FEATURES 8


KNearestNeighbours::KNearestNeighbours(int mk){
	k = mk;
}

KNearestNeighbours::~KNearestNeighbours() {}

/**
 * Comparison function used for knn
 */
bool compare(const std::pair<std::string, uint32_t>& p1, const std::pair<std::string, uint32_t>& p2) {
    return p1.second < p2.second;
}

/**
 * @param new_k the k value for knn
 */
void KNearestNeighbours::set_k(uint32_t new_k) {
    k = new_k;
}

/**
 * This function fits the learned data stored at the given path
 * @param path The path of the .csv file containing the classes
 */
void KNearestNeighbours::fit_from_file(const std::string& path) {

    std::ifstream in(path);
    char delim = ',';

    while(!in.eof()) {
        std::string name;
        std::vector<double> features;
        std::getline(in, name, delim);

        if(name == "") return;

        for (uint32_t i = 0; i < NB_FEATURES; ++i) {
            std::string feature;
            std::getline(in, feature, delim);
            features.push_back(stod(feature));
        }

        neighbours.push_back(ImageClass(name, features));

        in.ignore();
    }
}

/**
 * Function used to predict the class of the given image
 * It is a simple KNN algorithm
 * @param c The ImageClass to predict
 */
void KNearestNeighbours::predict(ImageClass& c) {

    for(ImageClass& cl : neighbours) cl.setDistance(c.distance(cl));

    std::sort(neighbours.begin(), neighbours.end());

    std::unordered_map<std::string, std::vector<ImageClass>> map;

    for(ImageClass& cl : neighbours) map[cl.getClass()] = std::vector<ImageClass>();

    for(uint32_t i = 0; i < k && i < neighbours.size(); ++i) {
        map[neighbours[i].getClass()].push_back(neighbours[i]);
    }

	uint32_t maxi = 0;
    ImageClass res = ImageClass();
    res.setDistance(DBL_MAX);

	for(const std::pair<std::string, std::vector<ImageClass> >& p : map) {

        if(p.second.size() > 0) std::cout << p.first << " " << p.second.size() << std::endl;

		if (maxi <= p.second.size()) {
            for(auto& x : p.second) {
                if(x < res) res = x;
            }

			maxi = (uint32_t)p.second.size();
		}
	}


    c.setClass(res.getClass());

}

/**
 * This function returns the confidence of image ranking in the database,
 * it stores in the given the classes and the number of time they appear in
 * the k nearest neighbours
 * @param c The class to predict
 * @param m The map to fill
 */
void KNearestNeighbours::kNeighbours(ImageClass& c, std::unordered_map<std::string, uint32_t>& m) {

    for(ImageClass& cl : neighbours) cl.setDistance(c.distance(cl));

    std::sort(neighbours.begin(), neighbours.end());

    for(ImageClass& cl : neighbours) m[cl.getClass()] = 0;

    for(uint32_t i = 0; i < k && i < neighbours.size(); ++i) {
        ++m[neighbours[i].getClass()];
    }

}