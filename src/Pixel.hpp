#ifndef Pixel_hpp
#define Pixel_hpp

#include <stdio.h>
#include <iostream>
#include "Util.hpp"



typedef unsigned char uchar;

// TODO: On gère les input avec des read

class Pixel{
	
public:
	
	uchar mr;
	uchar mg;
	uchar mb;
	
	Pixel();
	Pixel(const Pixel& p);
	Pixel(uchar r, uchar g, uchar b);
	Pixel(uchar v);
	void toColor(const Pixel& p, uchar maxv, uchar maxGray);
	bool isBlack();
	
	bool operator== (const Pixel& p2) const;
	
};

#endif /* Pixel_hpp */
