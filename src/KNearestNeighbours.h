#ifndef CGDI_PROJECT_KNEARESTNEIGHBOURS_H
#define CGDI_PROJECT_KNEARESTNEIGHBOURS_H


#include <cstdint>
#include <vector>
#include "ImageClass.h"

class KNearestNeighbours {

private:
    uint32_t k;
    std::vector<ImageClass> neighbours;

public:
    KNearestNeighbours(int k = 3);
    ~KNearestNeighbours();

    void set_k(uint32_t new_k);
    void fit(std::vector<ImageClass>&);
    void fit_from_file(const std::string&);
    void predict(ImageClass& c);
    void kNeighbours(ImageClass& c, std::unordered_map<std::string, uint32_t>&);

};


#endif
