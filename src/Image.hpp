#ifndef Image_hpp
#define Image_hpp

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include "Pixel.hpp"
#include "Util.hpp"

//TODO: passer sur des pixels en float
//TODO: retirer le maintient de l'histogramme

using namespace DGtal::Z2i;

class Image{
	uchar mP;
	int width;
	int height;

	uchar choixSeuilPbm();
	void construct(std::istream& in);
	void inputBitmap(std::istream& in);

    std::string path;
	
	
public:
    double hu_moments[7];
    std::vector<double> sift;
	std::vector<Pixel> bitMap;
	const Pixel& getPixel(int i, int j) const;
	Pixel& getPixel(int i, int j);
	uchar maxv;
	
	Image();
	Image(std::istream& in);
	Image(const std::string& file);
	Image(const Image& i);
	Image(uchar p, int width, int height, uchar mv=255);
	
	void setBitMap(const std::vector<Pixel>& bm);
	
	void topbm();
	void topbm(uchar seuil);
	
	void inverse();
	
	void applyConv(std::vector<int>& kernel1, std::vector<int>& kernel2);
	void applyConv(std::vector<int>& kernel, int n, int m);
	void gaussianSmooth(int size = 3);
	
	void dilate(int size = 3);
	void erode(int size = 3);
	void close(int size = 3);
	void open(int size = 3);

	uint32_t area(bool white);
	double perimeter(const Domain& d, const DigitalSet& forme);
	double area_perimeter_feature();

    uint32_t raw_moment(uint32_t p, uint32_t q);
    void compute_moments();
    void sift_detector();
	
	void print(const std::string& s, bool binary);
	void print(std::ostream& out, bool binary);
	
	void extractForme(DigitalSet& out);

    std::string getPath();
};

#endif /* Image_hpp */
