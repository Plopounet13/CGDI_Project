//
//  Histogramme.cpp
//  CGDI
//
//  Created by Loïs Paulin on 03/03/2017.
//  Copyright © 2017 Loïs Paulin. All rights reserved.
//

#include "Histogramme.hpp"

using namespace std;

Histogramme::Histogramme(){}

Histogramme::Histogramme(const Image& im):tab(im.maxv+1){
	for (auto& p : im.bitMap){
		++tab[p.mr];
	}
}

Histogramme::Histogramme(const Histogramme& h){
	tab=h.tab;
}

void Histogramme::inverse(){
	for (int i=0; i<tab.size()/2; ++i){
		swap(tab[i], tab[tab.size()-1-i]);
	}
}

void Histogramme::gamma_correction(float gamma){
	vector<uint64_t> newTab(tab.size());
	float gamma_1 = 1 / gamma;
	for (int i = 0; i < tab.size(); ++i){
		newTab[(size_t)(tab.size() - 1) * pow((float)i / (tab.size() - 1), gamma_1)] += tab[i];
	}
	
	tab.swap(newTab);
}

void Histogramme::apply_trans(const std::vector<int>& conv){
	vector<uint64_t> newTab(tab.size());
	
	for (int i=0; i<conv.size(); ++i){
		newTab[conv[i]]+=tab[i];
	}
	
	tab.swap(newTab);
}

ostream& operator<<(ostream& out, const Histogramme& h){
	out << endl << 0 << "\t" << h.tab[0];
	for (int i = 1; i < h.tab.size(); ++i){
		out << endl << i << "\t" << h.tab[i];
	}
	
	return out;
}













