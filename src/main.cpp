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
	
	//Image i("/Users/lois/Documents/M1ENS/CGDI/lectureDG-master/assignments/ShapeIndexing/database/cup-1.pgm");
	Image i(argv[1]);
	
	//string base("test-");
	string base(argv[2]);
	
	i.print(base+"-pure.pgm", false);
	
	i.close(7);
	
	i.sobelNorm();
	
	i.print(base+"-sobel.pgm", false);
	
	return 0;

}
