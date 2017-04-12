//
//  Pixel.cpp
//  CGDI
//
//  Created by Loïs Paulin on 18/02/2017.
//  Copyright © 2017 Loïs Paulin. All rights reserved.
//

#include "Pixel.hpp"
#include "Util.hpp"

using namespace std;

Pixel::Pixel(uchar r, uchar g, uchar b){
	mr=r;
	mg=g;
	mb=b;
}

Pixel::Pixel(uchar v){
	mr=mb=mg=v;
}

Pixel::Pixel(const Pixel& p){
	mr=p.mr;
	mg=p.mg;
	mb=p.mb;
}

Pixel::Pixel(){
	mr=mg=mb=0;
}

void Pixel::toColor(const Pixel& p, uchar maxv, uchar maxGray){
	float H, L;
	float r, g, b;
	r = (float)p.mr / (float)maxv;
	g = (float)p.mg / (float)maxv;
	b = (float)p.mb / (float)maxv;
	
	float M=max(max(r, g), b);
	float m=min(min(r, g), b);
	float C=M-m;
	
	if(C == 0){
		H=0;
	}else if (M==r){
		H = (g-b)/C;
		H = fmod(H + 6, 6);
	}else if (M==g){
		H = (b-r)/C;
		H += 2;
	}else{
		H = (r-g)/C;
		H += 4;
	}
	
	L = (float)mr / (float)maxGray;
	
	float X = C * (1 - abs(fmod(H, 2)-1));
	
	if (H <= 1){
		r = C;
		g = X;
		b = 0;
	} else if (H <= 2){
		r = X;
		g = C;
		b = 0;
	} else if (H <= 3){
		r = 0;
		g = C;
		b = X;
	} else if (H <= 4){
		r = 0;
		g = X;
		b = C;
	} else if (H <= 5){
		r = X;
		g = 0;
		b = C;
	} else {
		r = C;
		g = 0;
		b = X;
	}
	m = L - 0.5*C;
	
	mr = maxGray * clampf(r+m, 0, 1);
	mg = maxGray * clampf(g+m, 0, 1);
	mb = maxGray * clampf(b+m, 0, 1);
}

bool Pixel::operator== (const Pixel& p2) const{
	return (mr == p2.mr && mg == p2.mg && mb == p2.mb);
}
	
	
	
	
	




