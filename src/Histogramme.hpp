#ifndef Histogramme_hpp
#define Histogramme_hpp

#include <vector>
#include "Image.hpp"

class Histogramme{
public:
	std::vector<uint64_t> tab;
	
	Histogramme();
	Histogramme(const Image& im);
	Histogramme(const Histogramme& h);
	
	void gamma_correction(float gamma=2.2);
	void apply_trans(const std::vector<int>& conv);
	void inverse();
	
	friend std::ostream& operator<<(std::ostream& out, const Histogramme& h);
};

#endif /* Histogramme_hpp */
