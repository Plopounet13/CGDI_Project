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

class Histogramme;

//TODO: passer sur des pixels en float
//TODO: retirer le maintient de l'histogramme

using namespace DGtal::Z2i;

class Image{
	uchar mP;
	int width;
	int height;
	Histogramme *hist;

	uchar choixSeuilPbm();
	void construct(std::istream& in);
	void inputBitmap(std::istream& in);

    std::string path;
	
	
public:
    double hu_moments[7];
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
	void topgm();
	void toppm();
	
	Histogramme* getHisto();
	void inverse();
	void gamma_correction(float gamma=2.2);
	void linear_interpolation();
	void linear_interpolation(int a, int b);
	void equalization();
	
	void threshold(int thresh);
	void threshold();
	void thresholdMinVar();
	
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

	std::vector<Pixel> fourier_transform();

    uint32_t raw_moment(uint32_t p, uint32_t q);
    double normalize(double moment);
    void compute_moments();
	
	void sobelNorm();
	
	void print(const std::string& s, bool binary);
	void print(std::ostream& out, bool binary);
	
	void printHist(const std::string& s);
	void printHist(std::ostream& out);
	
	void comp_connexe(Image& i) const;
	
	void extractForme(DigitalSet& out);

    std::string getPath();
};

#endif /* Image_hpp */
