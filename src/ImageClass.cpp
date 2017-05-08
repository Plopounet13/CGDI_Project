//
// Created by remi on 02/05/17.
//

#include "ImageClass.h"

ImageClass::ImageClass() : curr_distance(0) {}

ImageClass::ImageClass(std::string path, std::string n) : name(n) {

    Image img(path);

    img.topbm();

    //img.close(10);

    img.compute_moments();

    for(uint32_t j = 0; j < 7; ++j) features.push_back(img.hu_moments[j]);

    features.push_back(img.area_perimeter_feature());
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
        double x = features[i] - a.features[i];
        ans += (x > 0 ? x : -x);
    }

    return ans;
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

void ImageClass::normalize() {
    double sum(0);

    for(double d : features) {
        sum += d;
    }

    double mean = sum / features.size();
    double std(0);

    for(double d : features) {
        std += ((d - mean) * (d - mean));
    }

    std /= features.size();

    for(uint32_t i = 0; i < features.size(); ++i) {
        features[i] = (features[i] - mean) / std;
    }
}