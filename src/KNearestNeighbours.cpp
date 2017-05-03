//
// Created by remi on 02/05/17.
//

#include <algorithm>
#include <map>
#include "KNearestNeighbours.h"

#define NB_FEATURES 7

KNearestNeighbours::KNearestNeighbours() : k(0) {}

KNearestNeighbours::~KNearestNeighbours() {}


bool compare(const std::pair<std::string, uint32_t>& p1, const std::pair<std::string, uint32_t>& p2) {
    return p1.second < p2.second;
}

void KNearestNeighbours::set_k(uint32_t new_k) {
    k = new_k;
}

void KNearestNeighbours::fit(std::vector<ImageClass> imgs) {
    neighbours = imgs;
}

void KNearestNeighbours::fit_from_file(std::string path) {

    std::ifstream in(path);
    char delim = ',';

    while(!in.eof()) {
        std::string name;
        std::vector<double> features;
        std::getline(in, name, delim);

        for (uint32_t i = 0; i < NB_FEATURES; ++i) {
            std::string feature;
            std::getline(in, feature, delim);
            features.push_back(stod(feature));
        }

        neighbours.push_back(ImageClass(name, features));

        in.ignore();
    }
}

void KNearestNeighbours::predict(ImageClass& c) {

    for(ImageClass cl : neighbours) cl.setDistance(c.distance(cl));

    std::sort(neighbours.begin(), neighbours.end());

    std::map<std::string, uint32_t> map;

    for(ImageClass cl : neighbours) map.insert(std::pair<std::string, uint32_t>(cl.getClass(), 0));

    for(uint32_t i = 0; i < k && i < neighbours.size(); ++i) {
        ++map[neighbours[i].getClass()];
    }

    std::vector<std::pair<std::string, uint32_t> > values;

    for(std::pair<std::string, uint32_t > p : map) values.push_back(p);

    std::sort(values.rbegin(), values.rend(), compare);

    for(std::pair<std::string, uint32_t> v: values) std::cout << v.first << " " << v.second << std::endl;

    c.setClass(values[0].first);

}
