//
// Created by remi on 02/05/17.
//

#include <algorithm>
#include <map>
#include "KNearestNeighbours.h"

KNearestNeighbours::KNearestNeighbours() : k(0) {}

KNearestNeighbours::~KNearestNeighbours() {}

void KNearestNeighbours::set_k(uint32_t new_k) {
    k = new_k;
}

void KNearestNeighbours::fit(std::vector<ImageClass> imgs) {
    neighbours = imgs;
}

void KNearestNeighbours::predict(ImageClass c) {
    std::sort(neighbours.begin(), neighbours.end());

    std::map<std::string, uint32_t> map;

    for(uint32_t i = 0; i < k && i < neighbours.size(); ++i) {
        ++map[neighbours[i].getClass()];
    }

    std::sort(map.begin(), map.end(), map.value_comp());

    c.setClass(map.begin() -> first);
}
