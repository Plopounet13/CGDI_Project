#include "DSS.hpp"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
//32bit integers


int mod(int v, int m){
	return ((v%m) + m)%m;
}

template <bool b> Point dir(int d);

//Returns the vector corresponding to the intput direction for 8-connexity
template <>
Point dir<0>(int d){
	switch (d) {
		case 0:
			return Point(1,0);
		case 1:
			return Point(1,-1);
		case 2:
			return Point(0,-1);
		case 3:
			return Point(-1,-1);
		case 4:
			return Point(-1,0);
		case 5:
			return Point(-1,1);
		case 6:
			return Point(0,1);
		case 7:
			return Point(1,1);
			
		default:
			return Point(0,0);
	}
}

//Returns the vector corresponding to the intput direction for 4-connexity
template <>
Point dir<1>(int d){
	switch (d) {
		case 0:
			return Point(1,0);
		case 1:
			return Point(0,-1);
		case 2:
			return Point(-1,0);
		case 3:
			return Point(0,1);
			
		default:
			return Point(0,0);
	}
}

template <bool b> void detectContours(const Domain& d, const DigitalSet& formes, vector<Point>& out);

//Extract contour from the shape described by formes
template <bool b>
void detectContours(const Domain& d, const DigitalSet& formes, vector<Point>& out){
	// 4 if b is 1, else 8
	int nbDir = (2 - b)*4, nbDir_2 = nbDir/2;
	
	out.clear();
	//If shape is empty there is no contour to get
	if (formes.begin() == formes.end())
		return;
	
	auto pi = d.rbegin();
	//Iterate from the bottom right corner until finding the shape
	while (pi != d.rend() && !formes(*pi))
		++pi;
	
	Point p = *pi;
	
	out.push_back(p);
	
	int dirIni = -1;
	
	//Chose initial direction, choice is made so we explore the contour clockwisely
	for (int i = nbDir - 1; i > 0 ; --i){
		int v = mod(i, nbDir);
		
		//if pixel in direction v is in pattern
		if (formes(p + dir<b>(v))){
			//We take opposite direction
			dirIni = mod(v + nbDir_2, nbDir);
			break;
		}
	}
	
	//If there is no white pixel around you then you are alone in the shape
	if (dirIni == -1)
		return;
	
	Point pAct = p;
	int dirAct = dirIni;
	
	do{
		//We choose the most outside pixe in our direction and add it to the contour
		for (int i = dirAct-(2-b); i < dirAct+(6 - 3*b); ++i){
			int v = mod(i, nbDir);
			Point ptmp = pAct + dir<b>(v);
			if (formes(ptmp)){
				pAct = ptmp;
				dirAct = v;
				out.push_back(pAct);
				break;
			}
		}
	//Until we are back at the beginning and going in the same direction (to avoid stopping too soon on 8 shapes)
	}while(pAct != p || dirAct != dirIni);
	
}

//Getting a Cover of the contour with non-overlapping DSSs
template <int c>
void maximalDSS(const vector<Point>& input, vector<ArithmeticalDSSComputer< Iterator, Integer, c> >& output){
	output.clear();
	
	output.emplace_back();
	output.back().init(input.begin());
	
	while(output.back().end() != input.end()){
		while ( (output.back().end() != input.end() ) && ( output.back().extendFront()));
		if (output.back().end() != input.end()){
			ArithmeticalDSSComputer<Iterator, Integer, c> tmp;
			tmp.init(output.back().end() - 1);
			
			output.push_back(tmp);
		}
	}
	
}


double DSSperimeter(const Domain& d, const DigitalSet& forme){
	vector<ArithmeticalDSSComputer< Iterator, Integer, 8> > dssCover;
	vector<Point> contour;
	
	detectContours<0>(d, forme, contour);
	
	maximalDSS<8>(contour, dssCover);
	
	double perimeter = 0;
	
	for (auto& dss : dssCover){
		perimeter += l2Metric(dss.front(), dss.back());
	}
	
	return perimeter;
}













