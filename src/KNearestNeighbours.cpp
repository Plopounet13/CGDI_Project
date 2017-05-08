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


bool compare(const std::pair<std::string, uint32_t>& p1, const std::pair<std::string, uint32_t>& p2) {
    return p1.second < p2.second;
}

void KNearestNeighbours::set_k(uint32_t new_k) {
    k = new_k;
}

void KNearestNeighbours::fit(std::vector<ImageClass>& imgs) {
    neighbours = imgs;
}

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

void KNearestNeighbours::predict(ImageClass& c) {

    c.normalize();

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