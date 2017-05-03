//
// Created by remi on 02/05/17.
//

#include "ImageClass.h"

ImageClass::ImageClass() : curr_distance(0) {}

ImageClass::ImageClass(std::string path, std::string n) : name(n) {

    Image img(path);

    img.compute_moments();

    for(uint32_t j = 0; j < 7; ++j) features.push_back(img.hu_moments[j]);
}

ImageClass::ImageClass(std::string s, std::vector<double> v) : curr_distance(0) {
    name = s;
    features = v;
}

ImageClass::~ImageClass() {}

bool ImageClass::operator==(const ImageClass &a) const {
    return a.name == name;
}

bool ImageClass::operator<(const ImageClass &a) const {
    return curr_distance < a.curr_distance;
}

void ImageClass::setFeatures(std::vector<double> v) {
    features = v;
}

void ImageClass::setClass(std::string s) {
    name = s;
}

double ImageClass::distance(const ImageClass &a) const {
    double ans(0);

    for(uint32_t i = 0; i < features.size(); ++i) {
        ans += (features[i] - a.features[i]) * (features[i] - a.features[i]);
    }

    std::cout << ans << std::endl;
    return sqrt(ans);
}

void ImageClass::setDistance(double d) {
    curr_distance = d;
}

double ImageClass::getDistance() {
    return curr_distance;
}

std::string ImageClass::getClass() {
    return name;
}

void ImageClass::printStream(std::ostream& out) const {
    out << name << ",";

    for(double feature : features) out << feature << ",";
}

std::ostream& operator<<(std::ostream& out, const ImageClass& i) {
    i.printStream(out);
    return out;
}