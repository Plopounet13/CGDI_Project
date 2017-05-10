//
// Created by remi on 02/05/17.
//

#include "ImageClass.h"

ImageClass::ImageClass() : curr_distance(0) {}

/**
 * Principal constructor for ImageClass, it stores the features
 * and the name of the class
 * @param path Pathname of the image
 * @param n The name of the class
 */
ImageClass::ImageClass(std::string path, std::string n) : name(n) {

    Image img(path);

    img.topbm();

    img.compute_moments();

    for(uint32_t j = 0; j < 7; ++j) features.push_back(img.hu_moments[j]);

    img.inverse();

    features.push_back(img.area_perimeter_feature());

    normalize();
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

/**
 *
 * The function used for the distance. Here we use the Euclidian distance
 *
 * @param a The class to compute the distance to
 *
 * @return The distance
 */
double ImageClass::distance(const ImageClass &a) const {
    double ans(0);

    for(uint32_t i = 0; i < features.size(); ++i) {
        double x = features[i] - a.features[i];
        ans += x * x;
    }

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

/**
 * This function is not used currently, it is used to standardize the
 * vector of features by applying x = (x - mean) / std for each x in the
 * feature vector
 */
void ImageClass::standardize() {
    double sum(0);
    uint32_t sz = features.size();

    for(double d : features) {
        sum += d;
    }

    double mean = sum / sz;
    double std(0);

    for(double d : features) {
        std += ((d - mean) * (d - mean));
    }

    std /= features.size();

    for(uint32_t i = 0; i < sz; ++i) {
        features[i] = (features[i] - mean) / std;
    }
}

/**
 * A simple vector normalization function
 */
void ImageClass::normalize() {
    double sz(0);

    for(double d : features) {
        sz += (d * d);
    }

    sz = sqrt(sz);

    for(uint32_t i = 0; i < features.size(); ++i) {
        features[i] /= sz;
    }
}
