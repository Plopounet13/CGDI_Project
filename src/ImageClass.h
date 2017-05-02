//
// Created by remi on 02/05/17.
//

#ifndef CGDI_PROJECT_IMAGECLASS_H
#define CGDI_PROJECT_IMAGECLASS_H

#include <string>
#include <vector>


class ImageClass {

private:
    std::string name;
    std::vector<double> features;
    double curr_distance;

public:
    ImageClass();
    ImageClass(std::string, std::vector<double>);
    ImageClass(std::string);
    ~ImageClass();

    bool operator ==(const ImageClass &a) const;
    bool operator <(const ImageClass &a) const;
    void setFeatures(std::vector<double>);
    void setClass(std::string s);
    double distance(const ImageClass &a) const;
    void setDistance(double d);
    double getDistance();
    std::string getClass();
};


#endif
