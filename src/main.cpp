//
//  main.cpp
//  CGDI
//
//  Created by Loïs Paulin on 18/02/2017.
//  Copyright © 2017 Loïs Paulin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "Histogramme.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
	/* We test the arguments */
	if (argc != 3)
	{
		printf("\nUsage : main fileIn fileOutBaseName \n\n");
		exit(0);
	}
	
	//Image i("/Users/lois/Documents/M1ENS/CGDI/CGDI/testComp.pgm");
	Image i(argv[1]);
	
	//string base("test-smooth");
	string base(argv[2]);
	
	Image i2;
	
	i.comp_connexe(i2);
	
	i2.print(base+"test_comp.pgm", false);
	
	return 0;

}
