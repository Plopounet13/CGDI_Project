#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.hpp"
#include "Histogramme.hpp"
#include "ImageClass.h"
#include "KNearestNeighbours.h"

#define NB_FEATURES 8

std::string classes[] =
		{
				{"apple"},
				{"bat"},
				{"beetle"},
				{"bell"},
				{"bird"},
				{"Bone"},
				{"bottle"},
				{"brick"},
				{"butterfly"},
				{"camel"},
				{"car"},
				{"carriage"},
				{"cattle"},
				{"cellular_phone"},
				{"chicken"},
				{"children"},
				{"chopper"},
				{"classic"},
				{"Comma"},
				{"crown"},
				{"cup"},
				{"deer"},
				{"device0"},
				{"device1"},
				{"device2"},
				{"device3"},
				{"device4"},
				{"device5"},
				{"device6"},
				{"device7"},
				{"device8"},
				{"device9"},
				{"dog"},
				{"elephant"},
				{"face"},
				{"fish"},
				{"flatfish"},
				{"fly"},
				{"fork"},
				{"fountain"},
				{"frog"},
				{"Glas"},
				{"guitar"},
				{"hammer"},
				{"hat"},
				{"HCircle"},
				{"Heart"},
				{"horse"},
				{"horseshoe"},
				{"jar"},
				{"key"},
				{"lizzard"},
				{"lmfish"},
				{"Misk"},
				{"octopus"},
				{"pencil"},
				{"personal_car"},
				{"pocket"},
				{"rat"},
				{"ray"},
				{"sea_snake"},
				{"shoe"},
				{"spoon"},
				{"spring"},
				{"stef"},
				{"teddy"},
				{"tree"},
				{"truck"},
				{"turtle"},
				{"watch"}
		};

using namespace std;

void print_moments(Image& img) {
	cout << "moments : " << endl;
	for(uint32_t i = 0; i < 7; ++i) cout << img.hu_moments[i] << " ";
	cout << endl;
}

void write_classes() {
	std::vector<ImageClass> imgs;

	for(std::string name : classes) {
		for(uint32_t i = 1; i <= 20; ++i) {
			if(i <= 10 || i >= 16) {
				cout << "database/"+name+"-"+std::to_string(i)+".pgm" << std::endl;
				imgs.push_back(ImageClass("database/" + name + "-" + std::to_string(i) + ".pgm", name));
			}
		}
	}

	ofstream out("classes.csv");

	for(ImageClass img : imgs) {
        img.normalize();
        out << img << endl;
    }

	out.close();
}

int main(int argc, const char * argv[]) {

    // get input file
    string path(argv[1]);
    uint32_t k = 3;

    KNearestNeighbours knn;

    knn.set_k(k);

    //get learned data
    knn.fit_from_file("classes.csv");

    ImageClass c(path, "");

    std::unordered_map<string, uint32_t > m;

    // find all neighbours
    knn.kNeighbours(c, m);

    // print confidence
    for(auto& p : m) {
        cout << p.second / (double)k << " ";
    }

    cout << endl;

	return 0;
}
