//
// Created by remi on 02/05/17.
//

#include "ImageClass.h"

ImageClass::ImageClass() : curr_distance(0) {}

ImageClass::ImageClass(std::string s) : curr_distance(0) {
    name = s;
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
    return curr_distance < a.curr_distance
}

void ImageClass::setFeatures(std::vector<double> v) {
    features = v;
}

void ImageClass::setClass(std::string s) {
    name = s;
}

double ImageClass::distance(const ImageClass &a) const {
    // TODO
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