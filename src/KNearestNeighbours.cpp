//
// Created by remi on 02/05/17.
//

#include <algorithm>
#include <unordered_map>
#include "KNearestNeighbours.h"

#define NB_FEATURES 7

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

    std::unordered_map<std::string, uint32_t> map;

    for(ImageClass& cl : neighbours) map[cl.getClass()] = 0;

    for(uint32_t i = 0; i < k && i < neighbours.size(); ++i) {
        ++map[neighbours[i].getClass()];
    }

    std::vector<std::pair<std::string, uint32_t> > values;

	uint32_t maxi = 0;
	std::string res;
    std::vector<std::pair<std::string, uint32_t >> v;

	for(const std::pair<std::string, uint32_t >& p : map) {
    if(p.second > 0) std::cout << p.first << " " << p.second << std::endl;
		if (maxi < p.second) {
            v.clear();
            v.push_back(p);
			maxi = p.second;
			res = (p.first);
		}
        else if(maxi == p.second) {
            v.push_back(p);
        }
	}

#define SEED time(NULL)
    srand(SEED);

    unsigned long idx = rand() % v.size();

    c.setClass(v[idx].first);

}
