#include "DSS.hpp"

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
//32bit integers

void getCircle(const Point& p, float r, const Domain& d, DigitalSet& res){
	for (auto& point : d){
		Point dist = point - p;
		if (dist[0]*dist[0] + dist[1]*dist[1] < r*r){
			res.insert(point);
		}
	}
}

int mod(int v, int m){
	return ((v%m) + m)%m;
}

template <bool b> Point dir(int d);

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

template <bool b>
void detectContours(const Domain& d, const DigitalSet& formes, vector<Point>& out){
	int nbDir = (2 - b)*4, nbDir_2 = nbDir/2;
	
	out.clear();
	if (formes.begin() == formes.end())
		return;
	
	auto pi = d.rbegin();
	
	while (pi != d.rend() && !formes(*pi))
		++pi;
	
	Point p = *pi;
	
	out.push_back(p);
	
	int dirIni = -1;
	
	for (int i = nbDir - 1; i > 0 ; --i){
		int v = mod(i, nbDir);
		
		//if pixel in direction v is in pattern
		if (formes(p + dir<b>(v))){
			//We take opposite direction
			dirIni = mod(v + nbDir_2, nbDir);
			break;
		}
	}
	
	if (dirIni == -1)
		return;
	
	Point pAct = p;
	int dirAct = dirIni;
	
	do{
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
	}while(pAct != p || dirAct != dirIni);
	
}

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


template <int c>
void DSScover(const vector<Point>& input, vector<ArithmeticalDSSComputer< MyCirculator, Integer, c> >& output){
	output.clear();
	
	MyCirculator it(input.begin(), input.begin(), input.end());
	
	ArithmeticalDSSComputer< MyCirculator, Integer, c> tmp;
	tmp.init(it);
	while (tmp.extendFront());
	while (tmp.extendBack());
	MyCirculator posFin = tmp.end();
	output.push_back(tmp);
	
	do{
		while  (!tmp.isExtendableFront() && tmp.retractBack());
		
		while (tmp.extendFront());
		
		output.push_back(tmp);
	}while(tmp.end() != posFin);
	
}


double DSSperimeter(const Domain& d, const DigitalSet& forme){
	vector<ArithmeticalDSSComputer< MyCirculator, Integer, 8> > dssCover;
	vector<Point> contour;
	
	detectContours<0>(d, forme, contour);
	
	DSScover<8>(contour, dssCover);
	
	double perimeter = 0;
	
	for (auto& dss : dssCover){
		perimeter += l2Metric(dss.front(), dss.back());
	}
	
	return perimeter;
}













